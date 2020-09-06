#ifndef MU_TYPETRAITS_H_
#define MU_TYPETRAITS_H_

#include <cmath>
#include <cstdlib>
#include <limits>

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
  constexpr static bool equals(T lhs, T rhs) { return lhs == rhs; }
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
  constexpr static bool equals(T lhs, T rhs);
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

/* relativ equality check for floating point types according to their epsilon.
 * source
 * https://stackoverflow.com/questions/4915462/how-should-i-do-floating-point-comparison
 */
template <class T>
constexpr bool TypeTraitsFloatingPoint<T>::equals(const T lhs, const T rhs) {
  /* shortcut. also for inf. values */
  if (lhs == rhs) {
    return true;
  }
  const T kAbsLhs = std::abs(lhs);
  const T kAbsRhs = std::abs(rhs);
  const T kAbsDiff = std::abs(lhs - rhs);
  /* Either value is zero or extremely close to it, relative error is less
   * meaningful here */
  if (lhs == 0 || rhs == 0 || kAbsDiff < std::numeric_limits<T>::min()) {
    return kAbsDiff <
           (TypeTraits<T>::epsilon() * std::numeric_limits<T>::min());
  }
  /* relative error */
  return (kAbsDiff / (kAbsLhs + kAbsRhs)) < TypeTraits<T>::epsilon();
}

}  // namespace mu
#endif  // MU_TYPETRAITS_H_