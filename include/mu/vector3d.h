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
  /**
   * @brief Construct a new Vector3D object default
   *
   */
  constexpr Vector3D() : Vector<3, T>() {}

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

  /**
   * @brief Construct a new Vector 3D object from an array
   *
   * @param data
   */
  explicit Vector3D(std::array<T, 3> data) : Vector<3, T>(data) {}

  /**
   * @brief Construct a new Vector3D object from a single value
   *
   * @param value
   */
  explicit Vector3D(T value) : Vector<3, T>(value) {}

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