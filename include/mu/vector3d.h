#ifndef MU_VECTOR3D_H_
#define MU_VECTOR3D_H_

#include "mu/vector.h"

namespace mu {

/**
 * @brief A three dimensional vector
 *
 * @tparam T type
 */
template <typename T>
class Vector3D : public Vector<3, T> {
 public:
  /* inherit base class constructors. only constructors specific to Vector2D
   * are defined here. apply rule of zero */
  using Vector<3, T>::Vector;

  /**
   * @brief Construct a new Vector3D object from a Vector object
   *
   * also implicitly used for copy initialization. purposely not marked
   * "explicit" for exactly this usecase. suppress linting for this line.
   *
   * @tparam Tt
   * @param other
   */
  template <class Tt = T>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Vector3D(const Vector<3, T>& other) : Vector<3, T>(other) {}

  /**
   * @brief x component
   *
   * @return T&
   */
  T& x() noexcept { return Vector<3, T>::data_[0]; }

  /**
   * @brief const x component
   *
   * @return const T&
   */
  const T& x() const noexcept { return Vector<3, T>::data_[0]; }

  /**
   * @brief y component
   *
   * @return T&
   */
  T& y() noexcept { return Vector<3, T>::data_[1]; }

  /**
   * @brief const y component
   *
   * @return const T&
   */
  const T& y() const noexcept { return Vector<3, T>::data_[1]; }

  /**
   * @brief z component
   *
   * @return T&
   */
  T& z() noexcept { return Vector<3, T>::data_[2]; }

  /**
   * @brief const z component
   *
   * @return const T&
   */
  const T& z() const noexcept { return Vector<3, T>::data_[2]; }
};

}  // namespace mu
#endif  // MU_VECTOR3D_H_