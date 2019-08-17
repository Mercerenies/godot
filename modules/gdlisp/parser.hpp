
#ifndef PARSER_HPP
#define PARSER_HPP

#include "sxp.hpp"

#include "core/script_language.h"
#include <utility>

struct ParseResult {
  Error error;
  const char* error_text;
  Ref<Sxp> result;
};

ParseResult parse_lisp(const String& code);

#endif // PARSER_HPP
