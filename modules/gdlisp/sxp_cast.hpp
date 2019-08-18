
#ifndef GDLISP_SXP_CAST_HPP
#define GDLISP_SXP_CAST_HPP

#include "sxp.hpp"

#include <type_traits>

template <typename T>
Ref<T> checked_cast(Ref<Sxp> ref);

// ------------------- //

template <typename T>
struct _SxpType;

template <>
struct _SxpType<Sxp> : std::integral_constant<SxpType, SxpType::UNKNOWN> {};

template <>
struct _SxpType<Cons> : std::integral_constant<SxpType, SxpType::CONS> {};

template <>
struct _SxpType<NilAtom> : std::integral_constant<SxpType, SxpType::NIL> {};

template <>
struct _SxpType<SymbolAtom> : std::integral_constant<SxpType, SxpType::SYMBOL> {};

template <typename T>
Ref<T> checked_cast(Ref<Sxp> ref) {
  if (ref->get_type() == _SxpType<T>::value) {
    return Ref<T>(SAFE_CAST<T*>(*ref));
  } else {
    return Ref<T>();
  }
}


#endif // GDLISP_SXP_CAST_HPP
