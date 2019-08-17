
#include "parser.hpp"

#include <cctype>
#include <cstring>

#include <iostream>

enum LispParseError {
  LISP_OK,
  LISP_UNEXPECTED_EOF,
  LISP_UNEXPECTED_CLOSE_PAREN,
  LISP_INCORRECT_CLOSE_PAREN
};

const char* error_text(LispParseError err) {
  switch (err) {
  case LISP_OK:
    return "No error";
  case LISP_UNEXPECTED_EOF:
    return "Unexpected EOF";
  case LISP_UNEXPECTED_CLOSE_PAREN:
    return "Unexpected closing bracket";
  case LISP_INCORRECT_CLOSE_PAREN:
    return "Incorrect closing bracket";
  }
  return "No error";
}

bool issymbolchar(char a) {
  if (std::isspace(a))
    return false;
  if (std::strchr("[()];", a))
    return false;

  return true; // TODO Refine meeeeeeeeeeee

}

class ParseEngine {
public:
  typedef std::pair<LispParseError, Ref<Sxp>> result_type;
private:
  const String& code;
  std::size_t pos;
  std::size_t line;
  std::size_t col;

  void _advance(int n) {
    std::size_t len = code.length();
    for (int i = 0; i < n; i++) {
      if (pos >= len)
        return;
      if (code[pos] == '\n') {
        line++;
        col = 0;
      } else {
        col++;
      }
      pos++;
    }
  }

  void _skip_to_end_of_line() {
    std::size_t len = code.length();
    while (pos < len) {
      if (code[pos] == '\n')
        break;
      _advance(1);
    }
    _advance(1);
  }

  void _skip_whitespace() {
    std::size_t len = code.length();
    while (pos < len) {
      if (!std::isspace(code[pos])) {
        // Is it a comment?
        if (code[pos] == ';')
          _skip_to_end_of_line();
        else
          break;
      } else {
        _advance(1);
      }
    }
  }

  result_type _parse_atom() {
    std::size_t len = code.length();
    if (pos >= len)
      return { LISP_UNEXPECTED_EOF, memnew(NilAtom) };

    String name = "";
    while (issymbolchar(code[pos])) {
      _advance(1);
      if (pos >= len)
        return { LISP_UNEXPECTED_EOF, memnew(NilAtom) };
      name += code[pos];
    }
    return { LISP_OK, memnew(SymbolAtom(name)) };
  }

  result_type _parse_list_inside(char close_paren) {
    std::size_t len = code.length();
    _skip_whitespace();
    if (pos >= len)
      return { close_paren == '\0' ? LISP_OK : LISP_UNEXPECTED_EOF, memnew(NilAtom) };

    if (code[pos] == ')' || code[pos] == ']') {
      _advance(1);
      if (code[pos - 1] == close_paren)
        return { LISP_OK, memnew(NilAtom) };
      else
        return { close_paren == '\0' ? LISP_UNEXPECTED_CLOSE_PAREN : LISP_INCORRECT_CLOSE_PAREN,
                 memnew(NilAtom) };
    }

    auto car = _parse();
    if (car.first != LISP_OK)
      return { car.first, memnew(NilAtom) };
    auto cdr = _parse_list_inside(close_paren);
    if (cdr.first != LISP_OK)
      return { cdr.first, memnew(Cons(car.second, memnew(NilAtom))) };

    return { LISP_OK, memnew(Cons(car.second, cdr.second)) };

  }

  result_type _parse() {
    std::size_t len = code.length();
    _skip_whitespace();
    if (pos >= len)
      return { LISP_UNEXPECTED_EOF, memnew(NilAtom) };

    if (code[pos] == '(' || code[pos] == '[') {
      _advance(1);
      return _parse_list_inside(code[pos - 1] == '(' ? ')' : ']');
    } else {
      return _parse_atom();
    }

  }

public:

  ParseEngine(const String& code) : code(code), pos(0), line(0), col(0) {}

  result_type parse() {
    return _parse_list_inside('\0');
  }

  std::pair<std::size_t, std::size_t> position_in_code() {
    return { line, col };
  }

};

ParseResult parse_lisp(const String& code) {
  ParseEngine parser { code };
  auto result = parser.parse();
  if (result.first == LISP_OK) {
    return { OK, {-1, -1}, "", result.second };
  } else {
    return { ERR_PARSE_ERROR, parser.position_in_code(), error_text(result.first), result.second };
  }
}
