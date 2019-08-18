
#include "function.hpp"
#include "sxp_iterator.hpp"
#include "sxp_cast.hpp"

#include <iostream>

bool read_as_function(Ref<Sxp> expr, GDLispFunction& out) {
  DottedList expr_dotted, args_dotted;

  out = GDLispFunction();

  sxp_to_dotted(expr, expr_dotted);
  if (expr_dotted.tail->get_type() != SxpType::NIL)
    return false;
  if (expr_dotted.list.size() < 3)
    return false;

  Ref<Sxp> defun_sxp = expr_dotted.list[0];
  Ref<Sxp> name_sxp = expr_dotted.list[1];
  Ref<Sxp> args_sxp = expr_dotted.list[2];
  for (int i = 3; i < expr_dotted.list.size(); i++) {
    out.body.push_back(expr_dotted.list[i]);
  }

  Ref<SymbolAtom> defun_atom = checked_cast<SymbolAtom>(defun_sxp);
  Ref<SymbolAtom> name_atom = checked_cast<SymbolAtom>(name_sxp);
  sxp_to_dotted(args_sxp, args_dotted);
  if (defun_atom == nullptr || name_atom == nullptr || args_dotted.tail->get_type() != SxpType::NIL)
    return false;
  if (defun_atom->name != "defun")
    return false;

  out.name = name_atom->name;
  PoolStringArray args;
  for (int i = 0; i < args_dotted.list.size(); i++) {
    Ref<SymbolAtom> arg = checked_cast<SymbolAtom>(args_dotted.list[i]);
    if (arg == nullptr)
      return false;
    out.args.push_back(arg->name);
  }

  return true;
}
