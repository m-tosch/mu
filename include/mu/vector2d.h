#ifndef MU_VECTOR2D_H_
#define MU_VECTOR2D_H_

#include <vector.h>

#include <array>

namespace mu {

template <typename T>
class Vector2D : Vector<2, T> {
 public:
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
};

}  // namespace mu
#endif  // MU_VECTOR2D_H_