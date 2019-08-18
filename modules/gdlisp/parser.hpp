
#ifndef GDLISP_PARSER_HPP
#define GDLISP_PARSER_HPP

#include "sxp.hpp"

#include "core/script_language.h"
#include <utility>

struct ParseResult {
  Error error;
  std::pair<std::size_t, std::size_t> error_pos;
  const char* error_text;
  Ref<Sxp> result;
};

ParseResult parse_lisp(const String& code);

#endif // GDLISP_PARSER_HPP
