
#ifndef SXP_HPP
#define SXP_HPP

#include "core/ustring.h"
#include "core/reference.h"

struct Sxp : Reference {
  GDCLASS(Sxp, Reference);

public:
  virtual ~Sxp() = default;
};

struct Cons : Sxp {
  Ref<Sxp> car;
  Ref<Sxp> cdr;
  Cons(Ref<Sxp> car, Ref<Sxp> cdr) : car(car), cdr(cdr) {}
  virtual ~Cons() = default;
};

struct NilAtom : Sxp {
  NilAtom() = default;
  virtual ~NilAtom() = default;
};

struct SymbolAtom : Sxp {
  // TODO For now, we're using strings here. Maybe StringName?
  String name;
  SymbolAtom(String name) : name(name) {}
  virtual ~SymbolAtom() = default;
};

#endif // SXP_HPP
