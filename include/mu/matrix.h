#ifndef MU_MATRIX_H_
#define MU_MATRIX_H_

#include <array>
#include <type_traits>

#include "mu/typetraits.h"
#include "mu/utility.h"
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
  static_assert(N != 0, "first matrix dimension (rows) cannot be zero");
  static_assert(M != 0, "second matrix dimension (columns) cannot be zero");
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

  /**
   * @brief Construct a new Matrix object from an amount of NxM values
   *
   * the amount of values in every dimension must match the static size of this
   * Matrix.
   *
   * @tparam TArgs
   * @param rows
   */
  template <typename... TArgs,
            std::enable_if_t<
                sizeof...(TArgs) == N &&
                    (std::is_same_v<T, std::remove_reference_t<TArgs>> && ...),
                int> = 0>
  // NOLINTNEXTLINE(runtime/explicit) impicit to make copy-init. work
  Matrix(TArgs const(&&... rows)[M]) : data_{mu::to_array(rows)...} {}

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
    for (std::size_t i = 0; i < N; i++) {
      for (std::size_t j = 0; j < M; j++) {
        data_[i][j] = arr[i][j];
      }
    }
  }

  /**
   * @brief Construct a new Matrix object from a single value
   *
   * @param value
   */
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Matrix(const T &value) {
    for (auto &item : data_) {
      item = {value};
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
   * @brief access a row within the matrix
   *
   * @exception out of range
   * @param idx
   * @return T&
   */
  Vector<M, T> &at(size_type idx) { return data_.at(idx); }

  /**
   * @brief const access a row within the matrix
   *
   * @exception out of range
   * @param idx
   * @return const T&
   */
  const Vector<M, T> &at(size_type idx) const { return data_.at(idx); }

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

  /**
   * @brief get the min value of the matrix
   *
   * @return T
   */
  T min() const {
    T ret(data_[0][0]);
    for (const auto &row : data_) {
      ret = mu::min(ret, mu::min(row));
    }
    return ret;
  }

  /**
   * @brief get the max value of the matrix
   *
   * @return T
   */
  T max() const {
    T ret(data_[0][0]);
    for (const auto &row : data_) {
      ret = mu::max(ret, mu::max(row));
    }
    return ret;
  }

  /**
   * @brief sum up all the elements of the matrix
   *
   * @return T
   */
  T sum() const {
    T ret{};
    for (const auto &row : data_) {
      ret += mu::sum(row);
    }
    return ret;
  }

  /**
   * @brief mean of all the elements of the matrix
   *
   * specifying the return type is optional.
   * It will be of the type of the Vector by default.
   *
   * @tparam U
   * @return U
   */
  template <typename U = T>
  U mean() const {
    return U(sum()) / (N * M);
  }

  /*************************** matrix <> matrix ****************************/

  /**
   * @brief equality operator
   *
   * see mu::Vector operator== for more information.
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

/************************* convenience functions ***************************/

template <std::size_t N, std::size_t M, class T>
inline T min(const Matrix<N, M, T> &other) {
  return other.min();
}

template <std::size_t N, std::size_t M, class T>
inline T max(const Matrix<N, M, T> &other) {
  return other.max();
}

template <std::size_t N, std::size_t M, class T>
inline T sum(const Matrix<N, M, T> &other) {
  return other.sum();
}

template <class U = void, std::size_t N, std::size_t M, typename T>
inline std::conditional_t<std::is_same_v<U, void>, T, U> mean(
    const Matrix<N, M, T> &m) {
  return m.template mean<std::conditional_t<std::is_same_v<U, void>, T, U>>();
}

}  // namespace mu
#endif  // MU_MATRIX_H_