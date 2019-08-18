
#include "sxp_iterator.hpp"
#include "sxp_cast.hpp"

SxpIterator::SxpIterator(Ref<Sxp> ref) : ref(ref) {}

Ref<Sxp> SxpIterator::operator*() const {
  auto cons = checked_cast<Cons>(ref);
  if (cons == nullptr)
    // Past end of iterator, UB
    return Ref<Sxp>();
  return cons->car;
}

Ref<Sxp> SxpIterator::operator->() const {
  auto cons = checked_cast<Cons>(ref);
  if (cons == nullptr)
    // Past end of iterator, UB
    return Ref<Sxp>();
  return cons->car;
}

SxpIterator& SxpIterator::operator++() {
  // If it's not a cons cell then we're already at end, so meh.
  auto cons = checked_cast<Cons>(ref);
  if (cons != nullptr) {
    ref = cons->cdr;
  }
  return *this;
}

SxpIterator SxpIterator::operator++(int) {
  auto tmp = *this;
  ++*this;
  return tmp;
}

Ref<Sxp> SxpIterator::get_remainder() const {
  return ref;
}

bool operator==(const SxpIterator& a, const SxpIterator& b) {
  auto cons_a = checked_cast<Cons>(a.ref);
  auto cons_b = checked_cast<Cons>(b.ref);
  if (cons_a == nullptr && cons_b == nullptr) {
    // Both are "end-of-line" iterators, so they're equal.
    return true;
  }
  // Otherwise, compare for pointer equality.
  return a.ref == b.ref;
}

bool operator!=(const SxpIterator& a, const SxpIterator& b) {
  return !(a == b);
}

const SxpIterator& begin(const SxpIterator& a) {
  return a;
}

SxpIterator end(const SxpIterator&) {
  return SxpIterator(Nil);
}

void sxp_to_dotted(Ref<Sxp> sxp, DottedList& out) {
  SxpIterator it = begin(SxpIterator(sxp));
  SxpIterator it1 = end(SxpIterator(sxp));
  out = DottedList();
  while (it != it1) {
    out.list.push_back(*it);
  }
  out.tail = it.get_remainder();
}
