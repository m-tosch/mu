#ifndef MU_TYPETRAITS_H_
#define MU_TYPETRAITS_H_

#include <cmath>
#include <cstdlib>

namespace mu {

template <class T>
struct TypeTraits {
  TypeTraits() = delete;
  constexpr static T epsilon() { return T(1); }
  static bool equals(T lhs, T rhs) { return lhs == rhs; }
};

template <>
struct TypeTraits<float> {
  constexpr static float epsilon() { return 1.0e-5F; }
  static bool equals(const float& lhs, const float& rhs) {
    if (lhs == rhs) {
      return true;
    }
    return std::fabs(lhs - rhs) < TypeTraits<float>::epsilon();
  }
};

/* ^TODO more generic solution. the equals check that is currently in the float
 * TypeTraits class should be available for all floating point types */
// template <class T>
// bool TypeTraits<T>::equals(const T lhs, const T rhs) {
//   if (lhs == rhs) {
//     return true;
//   }
//   return std::fabs(lhs - rhs) < TypeTraits<T>::epsilon();
// }

}  // namespace mu
#endif  // MU_TYPETRAITS_H_