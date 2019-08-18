
#include "sxp.hpp"

SxpType Sxp::get_type() const {
  return SxpType::UNKNOWN;
}

SxpType Cons::get_type() const {
  return SxpType::CONS;
}

SxpType NilAtom::get_type() const {
  return SxpType::NIL;
}

SxpType SymbolAtom::get_type() const {
  return SxpType::SYMBOL;
}

Ref<NilAtom> Nil;
