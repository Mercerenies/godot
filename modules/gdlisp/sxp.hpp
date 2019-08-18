
#ifndef GDLISP_SXP_HPP
#define GDLISP_SXP_HPP

#include "core/ustring.h"
#include "core/reference.h"

enum class SxpType {
  UNKNOWN, CONS, NIL, SYMBOL
};

struct Sxp : Reference {
  GDCLASS(Sxp, Reference);

public:
  virtual ~Sxp() = default;
  virtual SxpType get_type() const;
};

struct Cons : Sxp {
  Ref<Sxp> car;
  Ref<Sxp> cdr;
  Cons(Ref<Sxp> car, Ref<Sxp> cdr) : car(car), cdr(cdr) {}
  virtual ~Cons() = default;
  virtual SxpType get_type() const;
};

struct NilAtom : Sxp {
  NilAtom() = default;
  virtual ~NilAtom() = default;
  virtual SxpType get_type() const;
};

struct SymbolAtom : Sxp {
  // TODO For now, we're using strings here. Maybe StringName?
  String name;
  SymbolAtom(String name) : name(name) {}
  virtual ~SymbolAtom() = default;
  virtual SxpType get_type() const;
};

#endif // GDLISP_SXP_HPP
