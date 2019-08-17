
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
  if (std::strchr("[()]", a))
    return false;

  return true; // TODO Refine meeeeeeeeeeee

}

class ParseEngine {
public:
  typedef std::pair<LispParseError, Ref<Sxp>> result_type;
private:
  const String& code;
  std::size_t pos;

  result_type _parse_atom() {
    std::size_t len = code.length();
    if (pos >= len)
      return { LISP_UNEXPECTED_EOF, memnew(NilAtom) };

    String name = "";
    while (issymbolchar(code[pos])) {
      ++pos;
      if (pos >= len)
        return { LISP_UNEXPECTED_EOF, memnew(NilAtom) };
      name += code[pos];
    }
    return { LISP_OK, memnew(SymbolAtom(name)) };
  }

  result_type _parse_list_inside(char close_paren) {
    std::size_t len = code.length();
    if (pos >= len)
      return { close_paren == '\0' ? LISP_OK : LISP_UNEXPECTED_EOF, memnew(NilAtom) };

    while (std::isspace(code[pos])) {
      ++pos;
      if (pos >= len)
        return { close_paren == '\0' ? LISP_OK : LISP_UNEXPECTED_EOF, memnew(NilAtom) };
    }

    if (code[pos] == ')' || code[pos] == ']') {
      if (code[pos++] == close_paren)
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
    if (pos >= len)
      return { LISP_UNEXPECTED_EOF, memnew(NilAtom) };

    while (std::isspace(code[pos])) {
      ++pos;
      if (pos >= len)
        return { LISP_UNEXPECTED_EOF, memnew(NilAtom) };
    }

    if (code[pos] == '(' || code[pos] == '[') {
      return _parse_list_inside(code[pos++] == '(' ? ')' : ']');
    } else {
      return _parse_atom();
    }

  }

public:

  ParseEngine(const String& code) : code(code), pos(0) {}

  result_type parse() {
    return _parse_list_inside('\0');
  }

};

ParseResult parse_lisp(const String& code) {
  ParseEngine parser { code };
  auto result = parser.parse();
  if (result.first == LISP_OK) {
    return { OK, "", result.second };
  } else {
    return { ERR_PARSE_ERROR, error_text(result.first), result.second };
  }
}
