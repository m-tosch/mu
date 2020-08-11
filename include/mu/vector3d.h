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
  Vector3D(T x, T y, T z) {
    this->data_[0] = x;
    this->data_[1] = y;
    this->data_[2] = z;
  }

  Vector3D(const Vector<3, T>& other) : Vector<3, T>(other) {}

  /**
   * @brief set the x value of this three dimensional vector
   *
   * @param value
   */
  void x(T value) { this->data_[0] = value; }

  /**
   * @brief set the y value of this three dimensional vector
   *
   * @param value
   */
  void y(T value) { this->data_[1] = value; }

  /**
   * @brief set the z value of this three dimensional vector
   *
   * @param value
   */
  void z(T value) { this->data_[2] = value; }

  /**
   * @brief get the x value of this three dimensional vector
   *
   * @return T&
   */
  T& x() { return this->data_[0]; }

  /**
   * @brief get the y value of this three dimensional vector
   *
   * @return T&
   */
  T& y() { return this->data_[1]; }

  /**
   * @brief get the z value of this three dimensional vector
   *
   * @return T&
   */
  T& z() { return this->data_[2]; }
};

}  // namespace mu
#endif  // MU_VECTOR3D_H_