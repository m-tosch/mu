#ifndef MU_MATRIX_H_
#define MU_MATRIX_H_

#include <array>

#include "mu/typetraits.h"
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
  static_assert(std::is_arithmetic_v<mu::unwrap_ref_t<T>>,
                "Matrix type T must be an arithmetic type or a "
                "std::reference_wrapper that holds an arithmetic type");

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
    for (std::size_t i = 0; i < arr.size(); i++) {
      for (std::size_t j = 0; j < arr[0].size(); j++) {
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
   * @brief access a row within the matrix
   *
   * does not throw an exception if \p idx is out of range
   *
   * @param idx
   * @return T&
   */
  Vector<M, T> &operator[](size_type idx) noexcept { return data_[idx]; }

  /**
   * @brief const access a row within the matrix
   *
   * does not throw an exception if \p idx is out of range
   *
   * @param idx
   * @return const T&
   */
  const Vector<M, T> &operator[](size_type idx) const noexcept {
    return data_[idx];
  }

  /**
   * @brief returns the matrix dimensions as an array of size 2
   *
   * [0] rows
   * [1] columns
   *
   * @return constexpr std::array<size_type, 2>
   */
  constexpr std::array<size_type, 2> size() const noexcept {
    return std::array<size_type, 2>{N, M};
  }

  /**
   * @brief returns the number of rows
   *
   * @return constexpr size_type
   */
  constexpr size_type rows() const noexcept { return N; }

  /**
   * @brief returns the number of columns
   *
   * @return constexpr size_type
   */
  constexpr size_type cols() const noexcept { return M; }

  /**
   * @brief returns an iterator starting at the first row
   *
   * @return iterator
   */
  iterator begin() noexcept { return data_.begin(); }

  /**
   * @brief returns a const iterator starting at the first row
   *
   * @return const_iterator
   */
  const_iterator begin() const noexcept { return data_.begin(); }

  /**
   * @brief returns a iterator starting at one after the last row
   *
   * @return iterator
   */
  iterator end() noexcept { return data_.end(); }

  /**
   * @brief returns a const iterator starting at one after the last row
   *
   * @return const_iterator
   */
  const_iterator end() const noexcept { return data_.end(); }

  /*************************** matrix <> matrix ****************************/

  /**
   * @brief equality operator
   *
   * check mu::Vector operator== for more information.
   *
   * @param rhs
   * @return bool true if equal, false if unequal
   */
  template <typename U = T>
  bool operator==(const Matrix<N, M, U> &rhs) const {
    for (std::size_t i = 0; i < N; i++) {
      /* forward comparison to Vector class */
      if (data_[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }

  /**
   * @brief unequality operator
   *
   * @param rhs
   * @return bool true if unequal, false if equal
   */
  template <typename U = T>
  bool operator!=(const Matrix<N, M, U> &rhs) const {
    return !operator==(rhs);
  }

 protected:
  std::array<Vector<M, T>, N> data_;
};
}  // namespace mu
#endif  // MU_MATRIX_H_