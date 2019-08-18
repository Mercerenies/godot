
#ifndef GDLISP_SXP_ITERATOR_HPP
#define GDLISP_SXP_ITERATOR_HPP

#include "sxp.hpp"

#include <iterator>

class SxpIterator : public std::iterator<std::forward_iterator_tag, Ref<Sxp>> {
private:
  Ref<Sxp> ref;
public:
  SxpIterator(Ref<Sxp> ref);
  friend bool operator==(const SxpIterator& a, const SxpIterator& b);
  Ref<Sxp> operator*() const;
  Ref<Sxp> operator->() const;
  SxpIterator& operator++();
  SxpIterator operator++(int);
};

bool operator==(const SxpIterator& a, const SxpIterator& b);

bool operator!=(const SxpIterator& a, const SxpIterator& b);

const SxpIterator& begin(const SxpIterator& a);

SxpIterator end(const SxpIterator& a);

#endif // GDLISP_SXP_ITERATOR_HPP
