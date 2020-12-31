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
   * @par Example
   * @snippet example_vector2d.cpp vector2d different type constructor
   * @tparam Tt
   * @param other
   */
  template <class Tt = T>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Vector2D(const Vector<2, Tt>& other) : Vector<2, T>(other) {}

  /**
   * @brief x component
   *
   * @par Example
   * @snippet example_vector2d.cpp vector2d x function
   * @return T&
   */
  T& x() noexcept { return Vector<2, T>::data_[0]; }

  /**
   * @brief const x component
   *
   * @par Example
   * @snippet example_vector2d.cpp vector2d const x function
   * @return const T&
   */
  const T& x() const noexcept { return Vector<2, T>::data_[0]; }

  /**
   * @brief y component
   *
   * @par Example
   * @snippet example_vector2d.cpp vector2d y function
   * @return T&
   */
  T& y() noexcept { return Vector<2, T>::data_[1]; }

  /**
   * @brief const y component
   *
   * @par Example
   * @snippet example_vector2d.cpp vector2d const y function
   * @return const T&
   */
  const T& y() const noexcept { return Vector<2, T>::data_[1]; }

  /**
   * @brief rotates this Vector by an angle [rad]
   *
   * the euclidean vector length remains unchanged by rotation!
   *
   * @par Example
   * @snippet example_vector2d.cpp vector2d rotate function
   * @tparam T
   * @param angle
   * @return std::enable_if<std::is_floating_point<U>::value, void>::type
   */
  template <class TScalar = T>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value, void> rotate(
      TScalar angle) {
    const T kX = x();
    const T kY = y();
    Vector<2, T>::data_[0] = ((kX * mu::cos(angle)) - (kY * mu::sin(angle)));
    Vector<2, T>::data_[1] = ((kX * mu::sin(angle)) + (kY * mu::cos(angle)));
  }

  /**
   * @brief returns a Vector2D that is rotated by an angle [rad]
   *
   * @par Example
   * @snippet example_vector2d.cpp vector2d rotated function
   * @see @ref rotate()
   * @tparam T
   * @param angle
   * @return std::enable_if<std::is_floating_point<U>::value,
   * Vector2D<T>>::type
   */
  template <class TScalar = T>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector2D<T>>
  rotated(TScalar angle) {
    Vector2D<T> ret(*this);
    ret.rotate(angle);
    return ret;
  }
};

}  // namespace mu
#endif  // MU_VECTOR2D_H_