
#ifndef GDLISP_FUNCTION_HPP
#define GDLISP_FUNCTION_HPP

#include "sxp.hpp"

#include <optional>

struct GDLispFunction {
  String name;
  PoolStringArray args;
  Vector<Ref<Sxp>> body;
};

// Returns true if successful
bool read_as_function(Ref<Sxp> expr, GDLispFunction& out);

#endif // GDLISP_FUNCTION_HPP
