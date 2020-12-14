#ifndef MU_MATRIX_H_
#define MU_MATRIX_H_

#include <array>

#include "vector.h"

namespace mu {

/**
 * @brief A generic matrix
 *
 * @tparam N first matrix dimension (rows)
 * @tparam M second matrix dimension (columns)
 * @tparam T
 */
template <std::size_t N, std::size_t M, typename T>
class Matrix {
  static_assert(N != 0, "first matrix dimension cannot be zero");
  static_assert(M != 0, "second matrix dimension cannot be zero");

 public:
  /* value and size type from the underlying container */
  using value_type = typename std::array<Vector<M, T>, N>::value_type;
  using size_type = typename std::array<Vector<M, T>, N>::size_type;
  /* use iterators from the underlying container */
  using iterator = typename std::array<Vector<M, T>, N>::iterator;
  using const_iterator = typename std::array<Vector<M, T>, N>::const_iterator;

  /**
   * @brief Construct a new Matrix object
   *
   */
  constexpr Matrix() = default;

  /* TODO value init constructors */

  /**
   * @brief Construct a new Matrix object from an std::array of Vectors
   *
   * @param arr
   */
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Matrix(const std::array<Vector<M, T>, N> &arr) : data_(arr) {}

  /**
   * @brief Construct a new Matrix object from an std::array of std::arrays
   *
   * @param arr
   */
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Matrix(const std::array<std::array<T, M>, N> &arr) {
    for (size_type i = 0; i < arr.size(); i++) {
      for (size_type j = 0; j < arr[0].size(); j++) {
        data_[i][j] = arr[i][j];
      }
    }
  }

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

  /**
   * @brief matrix dimensions
   *
   * @return constexpr std::array<size_type, 2>
   */
  constexpr std::array<size_type, 2> size() const noexcept {
    return std::array<size_type, 2>{N, M};
  }

  /**
   * @brief
   *
   * @return iterator
   */
  iterator begin() noexcept { return data_.begin(); }

  /**
   * @brief
   *
   * @return const_iterator
   */
  const_iterator begin() const noexcept { return data_.begin(); }

  /**
   * @brief
   *
   * @return iterator
   */
  iterator end() noexcept { return data_.end(); }

  /**
   * @brief
   *
   * @return const_iterator
   */
  const_iterator end() const noexcept { return data_.end(); }

 protected:
  std::array<Vector<M, T>, N> data_;
};
}  // namespace mu
#endif  // MU_MATRIX_H_