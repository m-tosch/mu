#ifndef MU_MATRIX_H_
#define MU_MATRIX_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <type_traits>
#include <vector>

#include "mu/typetraits.h"
#include "mu/utility.h"
#include "vector.h"

namespace mu {

/**
 * @brief A generic matrix
 *
 * Can be instantiated with an arithmetic type as defined by the standard
 * library.
 * - implementation-defined extended integer types, including any signed,
 *   unsigned, and cv-qualified variants. (bool, char, int, long ...)
 * - implementation-defined extended floating-point types including any
 *   cv-qualified variants. (float, double, long double)
 *
 * Can be instantiated with a reference of an arithemtic type using
 * std::reference_wrapper and std::ref
 *
 * @tparam N first matrix dimension (rows)
 * @tparam M second matrix dimension (columns)
 * @tparam T the type of the values inside the matrix
 */
template <std::size_t N, std::size_t M, typename T>
class Matrix {
  static_assert(N != 0, "first matrix dimension (rows) cannot be zero");
  static_assert(M != 0, "second matrix dimension (columns) cannot be zero");
  static_assert(std::is_arithmetic<mu::unwrap_ref_t<T>>::value,
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
   * @par Example
   * @snippet example_matrix.cpp matrix constructor
   */
  constexpr Matrix() = default;

  /**
   * @brief Construct a new Matrix object from a number of NxM values
   *
   * the number of values in every dimension must match the static size of this
   * Matrix.
   *
   * @par Example
   * @snippet example_matrix.cpp matrix variadic template constructor
   * @tparam TArgs
   * @param rows
   */
  template <typename... TArgs,
            std::enable_if_t<
                sizeof...(TArgs) == N &&
                    (mu::conjunction<std::is_same<
                         T, std::remove_reference_t<TArgs>>::value...>::value),
                int> = 0>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Matrix(TArgs const(&&... rows)[M]) : data_{mu::to_array(rows)...} {}

  /**
   * @brief Construct a new Matrix from an existing Matrix of a different type
   *
   * implicit narrowing may be applied \n
   * it is checked that the Matrix sizes are the same \n
   * forwards intialization to Vector for every row
   *
   * @par Example
   * @snippet example_matrix.cpp matrix different type constructor
   * @tparam Nn
   * @tparam Mm
   * @tparam U
   * @param m
   */
  template <std::size_t Nn, std::size_t Mm, class U>
  // NOLINTNEXTLINE(runtime/explicit) implicit conversion is intentional
  Matrix(const Matrix<Nn, Mm, U> &m) {
    static_assert(N == Nn, "Matrix dimension mismatch (rows)");
    static_assert(M == Mm, "Matrix dimension mismatch (columns)");
    std::transform(m.begin(), m.end(), begin(),
                   [](Vector<M, U> data) { return data; });
  }

  /**
   * @brief Construct a new Matrix object from an std::array of Vectors
   *
   * @par Example
   * @snippet example_matrix.cpp matrix array of vectors constructor
   * @param a
   */
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Matrix(const std::array<Vector<M, T>, N> &a) : data_{a} {}

  /**
   * @brief Construct a new Matrix object from an std::array of Vectors of a
   * different type
   *
   * implicit narrowing may be applied \n
   * forwards intialization to Vector for every row
   *
   * @par Example
   * @snippet example_matrix.cpp matrix array of vectors diff. type constructor
   * @tparam U
   * @param a
   */
  template <typename U = T>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Matrix(const std::array<Vector<M, U>, N> &a) {
    std::transform(a.begin(), a.end(), begin(),
                   [](Vector<M, U> data) { return data; });
  }

  /**
   * @brief Construct a new Matrix object from an std::array of std::arrays.
   * possibly of a different type
   *
   * implicit narrowing may be applied \n
   * forwards intialization to Vector for every row
   *
   * @par Example
   * @snippet example_matrix.cpp matrix array of arrays constructor
   * @tparam U
   * @param a
   */
  template <typename U = T,
            std::enable_if_t<std::is_arithmetic<U>::value, int> = 0>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Matrix(const std::array<std::array<U, M>, N> &a) {
    std::transform(a.begin(), a.end(), begin(),
                   [](Vector<M, U> data) { return data; });
  }

  /**
   * @brief Construct a new Matrix object from a single value
   * possibly of a different type
   *
   * all the values inside the vector will be set to this value \n
   * implicit narrowing may be applied \n
   * forwards intialization to Vector for every row
   *
   * @par Example
   * @snippet example_matrix.cpp matrix single value constructor
   * @tparam U
   * @param value
   */
  template <typename U = T,
            std::enable_if_t<std::is_arithmetic<U>::value, int> = 0>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Matrix(const U &value) {
    data_.fill(value);
  }

  /**
   * @brief Destroy the Matrix object
   *
   */
  ~Matrix() = default;

  /**
   * @brief Copy construct a new Matrix object
   *
   * @par Example
   * @snippet example_matrix.cpp matrix copy constructor
   * @param other
   */
  Matrix(const Matrix &other) = default;

  /**
   * @brief Move construct a new Matrix object
   *
   * @par Example
   * @snippet example_matrix.cpp matrix move constructor
   * @param other
   */
  Matrix(Matrix &&other) noexcept = default;

  /**
   * @brief Copy assignment operator
   *
   * @par Example
   * @snippet example_matrix.cpp matrix copy assignment operator
   * @param other
   * @return Matrix&
   */
  Matrix &operator=(const Matrix &other) = default;

  /**
   * @brief Move assignment operator
   *
   * @par Example
   * @snippet example_matrix.cpp matrix move assignment operator
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
  constexpr size_type n_rows() const noexcept { return N; }

  /**
   * @brief returns the number of columns
   *
   * @return constexpr size_type
   */
  constexpr size_type n_cols() const noexcept { return M; }

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
   * @brief get a matrix row as a vector
   *
   * an invalid index that exceeds the matrix dimension causes a runtime error
   *
   * @param idx
   * @return Vector<M, T>
   */
  Vector<M, T> row(const size_type &idx) const {
    /* access to outside the matrix bounds can only be checked at runtime */
    assert(idx >= 0 && idx < N);
    return data_[idx];
  }

  /**
   * @brief get a matrix column as a vector
   *
   * an invalid index that exceeds the matrix dimension causes a runtime error
   *
   * @param idx
   * @return Vector<N, T>
   */
  Vector<N, T> col(const size_type &idx) const {
    /* access to outside the matrix bounds can only be checked at runtime */
    assert(idx >= 0 && idx < M);
    Vector<N, T> ret;
    for (std::size_t i = 0; i < N; i++) {
      ret[i] = data_[i][idx];
    }
    return ret;
  }

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

  /**
   * @brief returns the diagonale of the matrix as a vector
   *
   * the vector is of the size of the smallest matrix dimension. either N or M
   *
   */
  std::conditional_t < N<M, Vector<N, T>, Vector<M, T>> diag() const {
    constexpr std::size_t s = N < M ? N : M;
    Vector<s, T> ret;
    for (std::size_t i = 0; i < s; i++) {
      ret[i] = data_[i][i];
    }
    return ret;
  }

  /**
   * @brief calculates the determinant of the matrix
   *
   * matrix must be symmetrical with N == M
   *
   * @return T
   */
  T det() const {
    static_assert(N == M,
                  "Matrix dimensions must match to calculate the determinant");
    std::vector<std::vector<T>> vv;
    for (std::size_t i = 0; i < N; i++) {
      vv.push_back(std::vector<T>());
      for (const auto &item : data_[i]) {
        vv[i].push_back(item);
      }
    }
    return calc_det(vv);
  }

  /**
   * @brief creates and returns a transposed Matrix object
   *
   * @return Matrix<M, N, T>
   */
  Matrix<M, N, T> transpose() const {
    Matrix<M, N, T> ret;
    for (std::size_t i = 0; i < N; i++) {
      for (std::size_t j = 0; j < M; j++) {
        ret[j][i] = data_[i][j];
      }
    }
    return ret;
  }

  /**
   * @brief dot product of two matrices
   *
   * For a Matrix \f$ A \f$ of size \f$ M \times N \f$ and a Matrix \f$ B \f$ of
   * size \f$ N \times P \f$ the result is a Matrix \f$ C \f$ of size \f$ M
   * \times P \f$,
   *
   *  \f$ C = A \cdot B \f$ with
   *
   *  \f$ c_{ij} = A_{i1} B_{1j} + A_{i2} B_{2j} + ... + A_{iN} B_{Nj} =
   * \sum_{k=1}^{N} A_{ik} B_{kj} \f$
   *
   * Second Matrix dimension (N) of first Matrix must be equal to the first
   * Matrix dimension of the second Matrix (N)
   *
   * For two objects of the same type, specifying the return type is optional.
   * It will be of the type of the two objects by default.
   *
   * For two objects of different types, specifying the return type is required.
   *
   * return value is a Matrix of the size of the first Matrix's first dimension
   * (M) and the second Matrix's second dimension (P) containing the type of the
   * two objects or else of the explicitly stated type
   *
   * @ref https://en.wikipedia.org/wiki/Matrix_multiplication#Definition
   * @par Example
   * @snippet example_matrix.cpp matrix matrix dot function
   * @tparam U
   * @tparam N2
   * @tparam M2
   * @tparam T2
   * @param rhs
   * @return std::conditional_t<std::is_same<U, void>::value, Matrix<N, M2, T>,
   * Matrix<N, M2, U>>
   */
  template <typename U = void, std::size_t N2, std::size_t M2, typename T2>
  std::conditional_t<std::is_same<U, void>::value, Matrix<N, M2, T>,
                     Matrix<N, M2, U>>
  dot(const Matrix<N2, M2, T2> &rhs) const {
    static_assert(
        M == N2,
        "Matrix dimension mismatch. Second dimension of first matrix must be "
        "equal to the first dimension of the second matrix");
    using U_ = std::conditional_t<!std::is_same<T, T2>::value, U, T>;
    static_assert(!std::is_same<U_, void>::value,
                  "Matrix types are different. please specify the return "
                  "type. e.g. \"mat1.dot<float>(mat2);\"");
    Matrix<N, M2, U_> ret;
    for (std::size_t i = 0; i < N; i++) {
      for (std::size_t j = 0; j < M2; j++) {
        U_ sum{0};
        for (std::size_t k = 0; k < M; k++) {
          sum += (data_[i][k] * rhs[k][j]);
        }
        ret[i][j] = sum;
      }
    }
    return ret;
  }

  /**
   * @brief dot product of a matrix and a vector
   *
   * For a Matrix \f$ A \f$ of size \f$ N \times M \f$ and a Vector \f$ b \f$ of
   * size \f$ M \f$ the result is a Vector \f$ c \f$ of size \f$ N \f$,
   *
   *  \f$ c = A \cdot b \f$ with
   *
   *  \f$ c_{j} = A_{j1} b_1 + A_{j2} b_2 + ... + A_{jM} b_M =
   * \sum_{i=1}^{M} A_{ji} b_i \f$
   *
   * Second Matrix dimension (M) must be equal to the size of the Vector (N)
   *
   * For two objects of the same type, specifying the return type is optional.
   * It will be of the type of the two objects by default.
   *
   * For two objects of different types, specifying the return type is required.
   *
   * return value is a Vector of the size of the first Matrix dimension (N)
   * containing the type of the two objects or else of the explicitly stated
   * type
   *
   * @par Example
   * @snippet example_matrix.cpp matrix vector dot function
   * @tparam U
   * @tparam N2
   * @tparam T2
   * @param rhs
   * @return std::conditional_t<std::is_same<U, void>::value, Vector<N, T>,
   * Vector<N, U>>
   */
  template <typename U = void, std::size_t N2, typename T2>
  std::conditional_t<std::is_same<U, void>::value, Vector<N, T>, Vector<N, U>>
  dot(const Vector<N2, T2> &rhs) const {
    static_assert(
        M == N2,
        "Matrix-Vector dimension mismatch. Second dimension of the matrix "
        "must be equal to the vector size");
    using U_ = std::conditional_t<!std::is_same<T, T2>::value, U, T>;
    static_assert(
        !std::is_same<U_, void>::value,
        "Matrix and Vector types are different. please specify the return "
        "type. e.g. \"mat.dot<float>(vec);\"");
    Vector<N, U_> ret;
    for (std::size_t i = 0; i < N; i++) {
      U_ sum{0};
      for (std::size_t k = 0; k < M; k++) {
        sum += (data_[i][k] * rhs[k]);
      }
      ret[i] = sum;
    }
    return ret;
  }

  /**
   * @brief calculates the standard deviation
   *
   * \f$ \sigma = \sqrt{\frac{\sum(x_ij - \mu)^2}{N}} \f$
   *
   * @tparam U
   * @return U
   */
  template <class U = T>
  U std() const {
    U sum{0};
    U m = mean<U>();
    for (const auto &row : data_) {
      for (const auto &item : row) {
        sum += mu::pow(item - m, 2);
      }
    }
    return U(mu::sqrt(sum / (N * M)));
  }

  /********************************* I/O ***********************************/

  /**
   * @brief print matrix values
   *
   * forwards Vector for every row
   *
   * @tparam Nn
   * @tparam U
   * @param os
   * @param v
   * @return std::ostream&
   */
  template <std::size_t Nn, std::size_t Mm, class U>
  friend std::ostream &operator<<(std::ostream &os, const Matrix<Nn, Mm, U> &m);

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

  /**
   * @brief plus equal operator
   *
   * subject to implicit conversions
   *
   * @tparam U
   * @param rhs
   * @return Matrix<N, M, T>&
   */
  template <typename U = T>
  Matrix<N, M, T> &operator+=(const Matrix<N, M, U> &rhs) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] += rhs[i];
    }
    return *this;
  }

  /**
   * @brief minus equal operator
   *
   * subject to implicit conversions
   *
   * @tparam U
   * @param rhs
   * @return Matrix<N, M, T>&
   */
  template <typename U = T>
  Matrix<N, M, T> &operator-=(const Matrix<N, M, U> &rhs) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] -= rhs[i];
    }
    return *this;
  }

  /**
   * @brief multiplication equal operator
   *
   * subject to implicit conversions
   *
   * @tparam U
   * @param rhs
   * @return Matrix<N, M, T>&
   */
  template <typename U = T>
  Matrix<N, M, T> &operator*=(const Matrix<N, M, U> &rhs) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] *= rhs[i];
    }
    return *this;
  }

  /**
   * @brief divison equal operator
   *
   * subject to implicit conversions
   *
   * @tparam U
   * @param rhs
   * @return Matrix<N, M, T>&
   */
  template <typename U = T>
  Matrix<N, M, T> &operator/=(const Matrix<N, M, U> &rhs) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] /= rhs[i];
    }
    return *this;
  }

  /*************************** matrix <> scalar ****************************/

  /*
   * see Vector for more information
   */

  /**
   * @brief add a scalar to this matrix
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic<TScalar>::value,Matrix<N, M, T>
   * &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                            Matrix<N, M, T> &>
  operator+=(const TScalar &scalar) {
    for (auto &row : data_) {
      row += scalar;
    }
    return *this;
  }

  /**
   * @brief subtract a scalar from every element of this matrix
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Matrix<N, M,
   * T> &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                            Matrix<N, M, T> &>
  operator-=(const TScalar &scalar) {
    for (auto &row : data_) {
      row -= scalar;
    }
    return *this;
  }

  /**
   * @brief multiply a scalar with this matrix
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic<TScalar>::value,Matrix<N, M, T>
   * &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                            Matrix<N, M, T> &>
  operator*=(const TScalar &scalar) {
    for (auto &row : data_) {
      row *= scalar;
    }
    return *this;
  }

  /**
   * @brief divide every element of this matrix by a scalar
   *
   * division by zero on integral types triggers an assert
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Matrix<N, M,
   * T> &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                            Matrix<N, M, T> &>
  operator/=(const TScalar &scalar) {
    /* a division by zero is forwarded to and handled by the Vector class */
    for (auto &row : data_) {
      row /= scalar;
    }
    return *this;
  }

  /*************************************************************************/

 protected:
  std::array<Vector<M, T>, N> data_;
};  // namespace mu

/********************************** I/O ************************************/

template <std::size_t Nn, std::size_t Mm, class U>
std::ostream &operator<<(std::ostream &os, const Matrix<Nn, Mm, U> &m) {
  os << "[ ";
  for (std::size_t i = 0; i < Nn; i++) {
    os << m.data_[i];
    if (i < (Nn - 1)) {
      os << ",\n  ";
    } else {
      os << " ";
    }
  }
  os << "]";
  return os;
}

/**************************** matrix <> matrix *****************************/

/**
 * @brief plus operator
 *
 * @tparam N
 * @tparam M
 * @tparam T
 * @tparam U
 * @param lhs
 * @param rhs
 * @return Matrix<N, M, T>
 */
template <std::size_t N, std::size_t M, class T, class U = T>
inline Matrix<N, M, T> operator+(const Matrix<N, M, T> &lhs,
                                 const Matrix<N, M, U> &rhs) {
  return Matrix<N, M, T>(lhs) += rhs;
}

/**
 * @brief minus operator
 *
 * @tparam N
 * @tparam M
 * @tparam T
 * @tparam U
 * @param lhs
 * @param rhs
 * @return Matrix<N, M, T>
 */
template <std::size_t N, std::size_t M, class T, class U = T>
inline Matrix<N, M, T> operator-(const Matrix<N, M, T> &lhs,
                                 const Matrix<N, M, U> &rhs) {
  return Matrix<N, M, T>(lhs) -= rhs;
}

/**
 * @brief multiplication operator
 *
 * @tparam N
 * @tparam M
 * @tparam T
 * @tparam U
 * @param lhs
 * @param rhs
 * @return Matrix<N, M, T>
 */
template <std::size_t N, std::size_t M, class T, class U = T>
inline Matrix<N, M, T> operator*(const Matrix<N, M, T> &lhs,
                                 const Matrix<N, M, U> &rhs) {
  return Matrix<N, M, T>(lhs) *= rhs;
}

/**
 * @brief division operator
 *
 * @tparam N
 * @tparam M
 * @tparam T
 * @tparam U
 * @param lhs
 * @param rhs
 * @return Matrix<N, M, T>
 */
template <std::size_t N, std::size_t M, class T, class U = T>
inline Matrix<N, M, T> operator/(const Matrix<N, M, T> &lhs,
                                 const Matrix<N, M, U> &rhs) {
  return Matrix<N, M, T>(lhs) /= rhs;
}

/**************************** matrix <> scalar *****************************/

/**
 * @brief matrix and scalar addition
 *
 * see operator+=(scalar)
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Matrix<N, M, T>>
 */
template <std::size_t N, std::size_t M, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Matrix<N, M, T>> inline
operator+(const Matrix<N, M, T> &lhs, const TScalar &rhs) {
  return Matrix<N, M, T>(lhs) += rhs;
}

/**
 * @brief matrix and scalar addition
 *
 * see operator+=(scalar)
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Matrix<N, M, T>>
 */
template <std::size_t N, std::size_t M, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Matrix<N, M, T>> inline
operator+(const TScalar &lhs, const Matrix<N, M, T> &rhs) {
  return Matrix<N, M, T>(rhs) += lhs;
}

/**
 * @brief subtract a scalar from this matrix
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Matrix<N, M, T>>
 */
template <std::size_t N, std::size_t M, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Matrix<N, M, T>> inline
operator-(const Matrix<N, M, T> &lhs, const TScalar &rhs) {
  return Matrix<N, M, T>(lhs) -= rhs;
}

/**
 * @brief matrix and scalar multiplication
 *
 * see operator*=(scalar)
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Matrix<N, M, T>>
 */
template <std::size_t N, std::size_t M, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Matrix<N, M, T>> inline
operator*(const Matrix<N, M, T> &lhs, const TScalar &rhs) {
  return Matrix<N, M, T>(lhs) *= rhs;
}

/**
 * @brief matrix and scalar multiplication
 *
 * see operator*=(scalar)
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Matrix<N, M, T>>
 */
template <std::size_t N, std::size_t M, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Matrix<N, M, T>> inline
operator*(const TScalar &lhs, const Matrix<N, M, T> &rhs) {
  return Matrix<N, M, T>(rhs) *= lhs;
}

/**
 * @brief matrix and scalar division
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Matrix<N, M, T>>
 */
template <std::size_t N, std::size_t M, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Matrix<N, M, T>> inline
operator/(const Matrix<N, M, T> &lhs, const TScalar &rhs) {
  return Matrix<N, M, T>(lhs) /= rhs;
}

/************************* convenience functions ***************************/

template <std::size_t N, std::size_t M, class T>
inline T min(const Matrix<N, M, T> &m) {
  return m.min();
}

template <std::size_t N, std::size_t M, class T>
inline T max(const Matrix<N, M, T> &m) {
  return m.max();
}

template <std::size_t N, std::size_t M, class T>
inline T sum(const Matrix<N, M, T> &m) {
  return m.sum();
}

template <class U = void, std::size_t N, std::size_t M, typename T>
inline std::conditional_t<std::is_same<U, void>::value, T, U> mean(
    const Matrix<N, M, T> &m) {
  return m
      .template mean<std::conditional_t<std::is_same<U, void>::value, T, U>>();
}

template <std::size_t N, std::size_t M, typename T>
    std::conditional_t <
    N<M, Vector<N, T>, Vector<M, T>> diag(const Matrix<N, M, T> &m) {
  return m.diag();
}

/**
 * @brief builds and returns a diagonal matrix from a vector
 *
 * where every element is 0 and the vector elements are on the diagonal
 *
 * @tparam N
 * @tparam T
 * @param v
 * @return Matrix<N, N, T>
 */
template <std::size_t N, typename T>
inline Matrix<N, N, T> diag(const Vector<N, T> &v) {
  Matrix<N, N, T> ret{};
  for (std::size_t i = 0; i < N; i++) {
    ret[i][i] = v[i];
  }
  return ret;
}

template <std::size_t N, std::size_t M, typename T>
T det(const Matrix<N, M, T> &m) {
  return m.det();
}

template <std::size_t N, std::size_t M, typename T>
Matrix<M, N, T> transpose(const Matrix<N, M, T> &m) {
  return m.transpose();
}

template <typename U = void, std::size_t N1, std::size_t M1, typename T1,
          std::size_t N2, std::size_t M2, typename T2>
std::conditional_t<std::is_same<U, void>::value, Matrix<N1, M2, T1>,
                   Matrix<N1, M2, U>>
dot(const Matrix<N1, M1, T1> &lhs, const Matrix<N2, M2, T2> &rhs) {
  return lhs.template dot<U>(rhs);
}

template <typename U = void, std::size_t N, std::size_t M, typename T,
          std::size_t N2, typename T2>
std::conditional_t<std::is_same<U, void>::value, Vector<N, T>, Vector<N, U>>
dot(const Matrix<N, M, T> &lhs, const Vector<N2, T2> &rhs) {
  return lhs.template dot<U>(rhs);
}

template <std::size_t S, typename T = int>
inline Matrix<S, S, T> eye() {
  Matrix<S, S, T> ret{};
  for (std::size_t i = 0; i < S; i++) {
    ret[i][i] = T{1};
  }
  return ret;
}

template <std::size_t N, std::size_t M, typename T = int>
inline Matrix<N, M, T> ones() {
  return Matrix<N, M, T>{T{1}};
}

template <std::size_t N, std::size_t M, typename T = int>
inline Matrix<N, M, T> zeros() {
  return Matrix<N, M, T>{T{0}};
}

/* alias templates */
template <std::size_t N, typename T>
using MatrixNxN = Matrix<N, N, T>;

template <typename T>
using Matrix2x2 = Matrix<2, 2, T>;

template <typename T>
using Matrix3x3 = Matrix<3, 3, T>;

}  // namespace mu
#endif  // MU_MATRIX_H_