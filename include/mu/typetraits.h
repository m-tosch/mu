#ifndef MU_TYPETRAITS_H_
#define MU_TYPETRAITS_H_

#include <cmath>
#include <cstdlib>

namespace mu {

/**
 * @brief Basic type trait class
 *
 * equality can be checked directly through ==. The basic type trait is used for
 * integral types (bool, char, int etc.). For floating point numbers there is a
 * margin of error (epsilon) in which two values are still considered equal.
 * Epsilon is different for float, double etc. The algorithm for the equality
 * check is the same for all floating point types.
 *
 * @tparam T type
 */
template <class T>
struct TypeTraits {
  TypeTraits() = delete;
  // constexpr static float epsilon() { return T(1); }
  static bool equals(T lhs, T rhs) { return lhs == rhs; }
};

/**
 * @brief Floating point type trait class
 *
 * enables it's derived classes to use different methods than the ones in
 * the TypeTraits class. This is better than overloading since it's all done at
 * compile time.
 *
 * @tparam T floating point type
 */
template <class T>
struct TypeTraitsFloatingPoint {
  TypeTraitsFloatingPoint() = delete;
  static bool equals(T lhs, T rhs);
};

/** explicit template instantiations of TypeTraits for floating point types.
 * TypeTraitsFloatingPoint enables us to use a different equals method. */

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

/* equality check for floating point types according to their epsilon */
template <class T>
bool TypeTraitsFloatingPoint<T>::equals(const T lhs, const T rhs) {
  /* short cut. also for inf. values */
  if (lhs == rhs) {
    return true;
  }
  return std::fabs(lhs - rhs) < TypeTraits<T>::epsilon();
}

}  // namespace mu
#endif  // MU_TYPETRAITS_H_