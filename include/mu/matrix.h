#ifndef MU_MATRIX_H_
#define MU_MATRIX_H_

#include <array>

#include "vector.h"

namespace mu {

/**
 * @brief A generic matrix
 *
 * @tparam N first matrix dimension
 * @tparam M second matrix dimension
 * @tparam T
 */
template <std::size_t N, std::size_t M, typename T>
class Matrix {
  static_assert(N != 0, "first matrix dimension cannot be zero");
  static_assert(M != 0, "second matrix dimension cannot be zero");

 public:
  /**
   * @brief Construct a new Matrix object
   *
   */
  constexpr Matrix() = default;

  /* TODO value init constructors */

  /**
   * @brief Destroy the Matrix object
   *
   */
  ~Matrix() = default;

  /**
   * @brief Copy construct a new Matrix object
   *
   * @param other
   */
  Matrix(const Matrix &other) = default;

  /**
   * @brief Move construct a new Matrix object
   *
   * @param other
   */
  Matrix(Matrix &&other) noexcept = default;

  /**
   * @brief Copy assignment operator
   *
   * @param other
   * @return Matrix&
   */
  Matrix &operator=(const Matrix &other) = default;

  /**
   * @brief Move assignment operator
   *
   * @param other
   * @return Matrix&
   */
  Matrix &operator=(Matrix &&other) noexcept = default;

 protected:
  std::array<Vector<N, T>, M> data_;
};
}  // namespace mu
#endif  // MU_MATRIX_H_