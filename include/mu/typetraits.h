#ifndef MU_TYPETRAITS_H_
#define MU_TYPETRAITS_H_

#include <cmath>
#include <cstdlib>

/* use compile time checks as much as possible :) */

namespace mu {

template <class T>
struct TypeTraits {
  TypeTraits() = delete;
  constexpr static float epsilon() { return T(1); }
  static bool equals(T lhs, T rhs) { return lhs == rhs; }
};

template <class T>
struct TypeTraitsFloatingPoint {
  TypeTraitsFloatingPoint() = delete;
  static bool equals(T lhs, T rhs);
};

template <>
struct TypeTraits<float> : TypeTraitsFloatingPoint<float> {
  constexpr static float epsilon() { return 1.0e-5F; }  // NOLINT
};

template <>
struct TypeTraits<double> : TypeTraitsFloatingPoint<double> {
  constexpr static double epsilon() { return 1.0e-14; }  // NOLINT
};

template <>
struct TypeTraits<long double> : TypeTraitsFloatingPoint<long double> {
  constexpr static long double epsilon() { return 1.0e-14L; }  // NOLINT
};

template <class T>
bool TypeTraitsFloatingPoint<T>::equals(const T lhs, const T rhs) {
  /* short cut. also for inf. values */
  if (lhs == rhs) {
    return true;
  }
  return std::fabs(lhs - rhs) < TypeTraits<T>::epsilon();
}

};      // namespace mu
#endif  // MU_TYPETRAITS_H_