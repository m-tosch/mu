#ifndef MU_VECTOR2D_H_
#define MU_VECTOR2D_H_

#include "mu/vector.h"

namespace mu {

/**
 * @brief A two dimensional vector
 *
 * @tparam T type
 */
template <typename T>
class Vector2D : public Vector<2, T> {
 public:
  /* inherit base class constructors. only constructors specific to Vector2D are
   * defined here. apply rule of zero */
  using Vector<2, T>::Vector;

  /**
   * @brief Construct a new Vector2D object from a Vector object
   *
   * also implicitly used for copy initialization. purposely not marked
   * "explicit" for exactly that usecase. suppress linting for this line.
   *
   * @param other
   */
  // NOLINTNEXTLINE(runtime/explicit) implicit conversion is intentional
  Vector2D(const Vector<2, T>& other) : Vector<2, T>(other) {}

  /**
   * @brief x component
   *
   * @return T&
   */
  T& x() noexcept { return Vector<2, T>::data_[0]; }

  /**
   * @brief const x component
   *
   * @return const T&
   */
  const T& x() const noexcept { return Vector<2, T>::data_[0]; }

  /**
   * @brief y component
   *
   * @return T&
   */
  T& y() noexcept { return Vector<2, T>::data_[1]; }

  /**
   * @brief const y component
   *
   * @return const T&
   */
  const T& y() const noexcept { return Vector<2, T>::data_[1]; }

  /**
   * @brief rotates this vector by an angle [rad]
   *
   * @tparam T
   * @param angle
   * @return std::enable_if<std::is_floating_point<U>::value, void>::type
   */
  template <class U = T>
  typename std::enable_if<std::is_floating_point<U>::value, void>::type rotate(
      T angle) {
    const T kX = x();
    const T kY = y();
    Vector<2, T>::data_[0] = ((kX * std::cos(angle)) - (kY * std::sin(angle)));
    Vector<2, T>::data_[1] = ((kX * std::sin(angle)) + (kY * std::cos(angle)));
  }
};

}  // namespace mu
#endif  // MU_VECTOR2D_H_