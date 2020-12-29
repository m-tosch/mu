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
  /* inherit base class constructors. only constructors specific to Vector2D
   * are defined here. apply rule of zero */
  using Vector<2, T>::Vector;

  /**
   * @brief Construct a new Vector2D object from a Vector object
   *
   * also implicitly used for copy initialization. purposely not marked
   * "explicit" for exactly this usecase.
   *
   * @tparam Tt
   * @param other
   */
  template <class Tt = T>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Vector2D(const Vector<2, Tt>& other) : Vector<2, T>(other) {}

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
   * @brief rotates this Vector by an angle [rad]
   *
   * @tparam T
   * @param angle
   * @return std::enable_if<std::is_floating_point<U>::value, void>::type
   */
  template <class TScalar = T>
  typename std::enable_if_t<std::is_arithmetic_v<TScalar>, void> rotate(
      TScalar angle) {
    const T kX = x();
    const T kY = y();
    Vector<2, T>::data_[0] = ((kX * mu::cos(angle)) - (kY * mu::sin(angle)));
    Vector<2, T>::data_[1] = ((kX * mu::sin(angle)) + (kY * mu::cos(angle)));
  }

  /**
   * @brief returns a Vector2D that is rotated by an angle [rad]
   *
   * @see @ref rotate()
   * @tparam T
   * @param angle
   * @return std::enable_if<std::is_floating_point<U>::value,
   * Vector2D<T>>::type
   */
  template <class TScalar = T>
  typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector2D<T>> rotated(
      TScalar angle) {
    Vector2D<T> ret(*this);
    ret.rotate(angle);
    return ret;
  }
};

}  // namespace mu
#endif  // MU_VECTOR2D_H_