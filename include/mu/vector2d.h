#ifndef MU_VECTOR2D_H_
#define MU_VECTOR2D_H_

#include <vector.h>

namespace mu {

/**
 * @brief A two dimensional vector
 *
 * @tparam T type
 */
template <typename T>
class Vector2D : public Vector<2, T> {
 public:
  /**
   * @brief Construct a new Vector2D object default
   *
   */
  constexpr Vector2D() = default;

  /**
   * @brief Construct a new Vector2D object from two values
   *
   * @param x
   * @param y
   */
  Vector2D(T x, T y) {
    this->data_[0] = x;
    this->data_[1] = y;
  }

  /**
   * @brief Construct a new Vector 2D object from an array
   *
   * @param data
   */
  explicit Vector2D(std::array<T, 2> data) : Vector<2, T>(data) {}

  /**
   * @brief Construct a new Vector2D object from a single value
   *
   * @param value
   */
  explicit Vector2D(T value) : Vector<2, T>(value) {}

  /**
   * @brief set the x value of this two dimensional vector
   *
   * @param value
   */
  void x(T value) { this->data_[0] = value; }

  /**
   * @brief set the y value of this two dimensional vector
   *
   * @param value
   */
  void y(T value) { this->data_[1] = value; }

  /**
   * @brief get the x value of this two dimensional vector
   *
   * @return T&
   */
  T& x() { return this->data_[0]; }

  /**
   * @brief get the y value of this two dimensional vector
   *
   * @return T&
   */
  T& y() { return this->data_[1]; }
};

}  // namespace mu
#endif  // MU_VECTOR2D_H_