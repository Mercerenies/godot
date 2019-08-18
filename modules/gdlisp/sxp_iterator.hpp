
#ifndef GDLISP_SXP_ITERATOR_HPP
#define GDLISP_SXP_ITERATOR_HPP

#include "sxp.hpp"

#include <iterator>

struct DottedList {
  Vector< Ref<Sxp> > list;
  Ref<Sxp> tail;
};

class SxpIterator : public std::iterator<std::forward_iterator_tag, Ref<Sxp>> {
private:
  Ref<Sxp> ref;
public:
  explicit SxpIterator(Ref<Sxp> ref);
  friend bool operator==(const SxpIterator& a, const SxpIterator& b);
  Ref<Sxp> operator*() const;
  Ref<Sxp> operator->() const;
  SxpIterator& operator++();
  SxpIterator operator++(int);
  Ref<Sxp> get_remainder() const;
};

bool operator==(const SxpIterator& a, const SxpIterator& b);

bool operator!=(const SxpIterator& a, const SxpIterator& b);

const SxpIterator& begin(const SxpIterator& a);

SxpIterator end(const SxpIterator& a);

void sxp_to_dotted(Ref<Sxp> sxp, DottedList& out);

#endif // GDLISP_SXP_ITERATOR_HPP
