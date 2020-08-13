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
  /* inherit base class constructors. only constructors specific to Vector2D are
   * defined here. apply rule of zero */
  using Vector<3, T>::Vector;

  /**
   * @brief Construct a new Vector3D object from three values
   *
   * @param x
   * @param y
   * @param z
   */
  Vector3D(T x, T y, T z) : x(x), y(y), z(z) {
    this->data_[0] = x;
    this->data_[1] = y;
    this->data_[2] = z;
  }

  /**
   * @brief Construct a new Vector3D object from a Vector object
   *
   * also implicitly used for copy initialization. purposely not marked
   * "explicit" for exactly that usecase. suppress linting for this line.
   *
   * @param other
   */
  // NOLINTNEXTLINE(runtime/explicit) implicit conversion intentional
  Vector3D(const Vector<3, T>& other) : Vector<3, T>(other) {}

  T x; /**< x value */
  T y; /**< y value */
  T z; /**< z value */
};

}  // namespace mu
#endif  // MU_VECTOR3D_H_