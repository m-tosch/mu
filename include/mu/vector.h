#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <numeric>
#include <ostream>
#include <type_traits>
#include <utility>

#include "mu/typetraits.h"
#include "mu/utility.h"

namespace mu {

/* forward declaration */
/* lets the Vector class in this header know what "Matrix" is, so the alias can
 * be used for function arguments, return types ... */
template <std::size_t X, std::size_t Y, typename Z>
class Matrix;

/**
 * @brief A generic vector
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
 * @tparam N size
 * @tparam T type
 */
template <std::size_t N, typename T>
class Vector {
  static_assert(N != 0, "Vector dimension cannot be zero");
  static_assert(std::is_arithmetic<mu::unwrap_ref_t<T>>::value,
                "Vector type T must be an arithmetic type or a "
                "std::reference_wrapper that holds an arithmetic type");

 public:
  /* value and size type from the underlying container */
  using value_type = typename std::array<T, N>::value_type;
  using size_type = typename std::array<T, N>::size_type;
  /* use iterators from the underlying container */
  using iterator = typename std::array<T, N>::iterator;
  using const_iterator = typename std::array<T, N>::const_iterator;

  /**
   * @brief Construct a new Vector object
   *
   * @par Example
   * @snippet example_vector.cpp vector constructor
   */
  constexpr Vector() = default;

  /**
   * @brief Construct a new Vector object from a number of N values
   *
   * the number of values must match the static size of this Vector
   * the type must be arithmetic or a reference of an arithmetic
   *
   * @par Example
   * @snippet example_vector.cpp vector variadic template constructor
   * @tparam TArgs
   * @param args
   */
  template <typename... TArgs,
            std::enable_if_t<
                sizeof...(TArgs) == N &&
                    (mu::conjunction<std::is_same<
                         T, std::remove_reference_t<TArgs>>::value...>::value),
                int> = 0>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Vector(TArgs &&... args) : data_{std::forward<TArgs>(args)...} {}

  /**
   * @brief Construct a new Vector from an existing Vector of a different type
   *
   * implicit narrowing may be applied
   * it is checked that the Vector sizes are the same
   *
   * @par Example
   * @snippet example_vector.cpp vector different type constructor
   * @tparam Nn
   * @tparam U
   * @param v
   */
  template <std::size_t Nn, class U>
  // NOLINTNEXTLINE(runtime/explicit) implicit conversion is intentional
  Vector(const Vector<Nn, U> &v) {
    static_assert(N == Nn, "Vector size mismatch");
    std::transform(v.begin(), v.end(), begin(), [](U data) { return data; });
  }

  /**
   * @brief Construct a new Vector object from an std::array
   *
   * @par Example
   * @snippet example_vector.cpp vector array constructor
   * @param a
   */
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Vector(const std::array<T, N> &a) : data_{a} {}

  /**
   * @brief Construct a new Vector object from an std::array of a different type
   *
   * implicit narrowing may be applied
   *
   * @par Example
   * @snippet example_vector.cpp vector array different type constructor
   * @tparam U
   * @param a
   */
  template <typename U = T,
            std::enable_if_t<std::is_arithmetic<U>::value, int> = 0>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Vector(const std::array<U, N> &a) {
    std::transform(a.begin(), a.end(), begin(), [](U data) { return data; });
  }

  /**
   * @brief Construct a new Vector object from a single value
   *
   * all the values inside the vector will be set to this value
   *
   * @par Example
   * @snippet example_vector.cpp vector single value constructor
   * @tparam U
   * @param value
   */
  template <typename U = T,
            std::enable_if_t<std::is_arithmetic<U>::value, int> = 0>
  // NOLINTNEXTLINE(runtime/explicit) implicit to make copy-init. work
  Vector(const U &value) {
    data_.fill(value);
  }

  /**
   * @brief Destroy the Vector object
   *
   */
  ~Vector() = default;

  /**
   * @brief Copy construct a new Vector object
   *
   * @par Example
   * @snippet example_vector.cpp vector copy constructor
   * @param other
   */
  Vector(const Vector &other) = default;

  /**
   * @brief Move construct a new Vector object
   *
   * @par Example
   * @snippet example_vector.cpp vector move constructor
   * @param other
   */
  Vector(Vector &&other) noexcept = default;

  /**
   * @brief Copy assignment operator
   *
   * @par Example
   * @snippet example_vector.cpp vector copy assignment operator
   * @param other
   * @return Vector&
   */
  Vector &operator=(const Vector &other) = default;

  /**
   * @brief Move assignment operator
   *
   * @par Example
   * @snippet example_vector.cpp vector move assignment operator
   * @param other
   * @return Vector&
   */
  Vector &operator=(Vector &&other) noexcept = default;

  /**
   * @brief access an element within the vector
   *
   * does not throw an exception if \p idx is out of range
   *
   * @par Example
   * @snippet example_vector.cpp vector brackets operator
   * @param idx
   * @return T&
   */
  T &operator[](size_type idx) noexcept { return data_[idx]; }

  /**
   * @brief const access an element within the vector
   *
   * does not throw an exception if \p idx is out of range
   *
   * @par Example
   * @snippet example_vector.cpp vector const brackets operator
   * @param idx
   * @return const T&
   */
  const T &operator[](size_type idx) const noexcept { return data_[idx]; }

  /**
   * @brief access an element within the vector
   *
   * @par Example
   * @snippet example_vector.cpp vector at function
   * @exception out of range
   * @param idx
   * @return T&
   */
  T &at(size_type idx) { return data_.at(idx); }

  /**
   * @brief const access an element within the vector
   *
   * @par Example
   * @snippet example_vector.cpp vector const at function
   * @exception out of range
   * @param idx
   * @return const T&
   */
  const T &at(size_type idx) const { return data_.at(idx); }

  /**
   * @brief returns the size of the vector
   *
   * @par Example
   * @snippet example_vector.cpp vector size function
   * @return size_type
   */
  constexpr size_type size() const noexcept { return N; }

  /**
   * @brief returns an iterator pointing to the first element
   *
   * @par Example
   * @snippet example_vector.cpp vector begin function
   * @return iterator
   */
  iterator begin() noexcept { return data_.begin(); }

  /**
   * @brief returns a const iterator pointing to the first element
   *
   * @par Example
   * @snippet example_vector.cpp vector const begin function
   * @return const_iterator
   */
  const_iterator begin() const noexcept { return data_.begin(); }

  /**
   * @brief returns an iterator pointing to the element following the last
   * element
   *
   * @par Example
   * @snippet example_vector.cpp vector end function
   * @return iterator
   */
  iterator end() noexcept { return data_.end(); }

  /**
   * @brief returns a const iterator pointing to the element following the last
   * element
   *
   * @par Example
   * @snippet example_vector.cpp vector const end function
   * @return const_iterator
   */
  const_iterator end() const noexcept { return data_.end(); }

  /**
   * @brief get the min value of the vector
   *
   * @par Example
   * @snippet example_vector.cpp vector min function
   * @return T
   */
  T min() const {
    T ret(data_[0]);
    for (std::size_t i = 1; i < N; i++) {
      ret = mu::min(ret, data_[i]);
    }
    return ret;
  }

  /**
   * @brief get the max value of the vector
   *
   * @par Example
   * @snippet example_vector.cpp vector max function
   * @return T
   */
  T max() const {
    T ret(data_[0]);
    for (std::size_t i = 1; i < N; i++) {
      ret = mu::max(ret, data_[i]);
    }
    return ret;
  }

  /**
   * @brief sum up all the elements of the vector
   *
   * @par Example
   * @snippet example_vector.cpp vector sum function
   * @return T
   */
  T sum() const {
    T ret{};
    for (const auto &item : data_) {
      ret += item;
    }
    return ret;
  }

  /**
   * @brief mean of all the elements of the vector
   *
   * \f$ \mu = \frac{\sum(x_i)}{N} \f$
   *
   * returns the mean as
   * - the type of this vector (default)
   * - the explicitly stated type
   *
   * @par Example
   * @snippet example_vector.cpp vector mean function
   * @tparam U
   * @return U
   */
  template <typename U = T>
  U mean() const {
    return U(sum()) / N;
  }

  /**
   * @brief dot product of two vectors
   *
   * For a Vector \f$ a \f$ of size \f$ N \f$ and a Vector \f$ b \f$ of size \f$
   * N \f$ the result is a scalar,
   *
   * \f$ a \cdot b = \sum_{i=1}^{N} a_i b_i \f$
   *
   * Vector sizes must be equal
   *
   * For two Vectors of the same type, specifying the return type is optional.
   * It will be of the type of the two Vectors by default.
   *
   * For two Vectors of different types, specifying the return type is required.
   *
   * return value is a scalar of the type of the two Vectors or else of the
   * explicitly stated type
   *
   * @par Example
   * @snippet example_vector.cpp vector vector dot function
   * @tparam U
   * @tparam N2
   * @tparam T2
   * @param rhs
   * @return std::conditional_t<std::is_same<U, void>::value, T, U>
   */
  template <typename U = void, std::size_t N2, typename T2>
  std::conditional_t<std::is_same<U, void>::value, T, U> dot(
      const Vector<N2, T2> &rhs) const {
    static_assert(N == N2, "Vector size mismatch");
    using U_ = std::conditional_t<!std::is_same<T, T2>::value, U, T>;
    static_assert(!std::is_same<U_, void>::value,
                  "Vector types are different. please specify the return "
                  "type. e.g. \"vec1.dot<float>(vec2);\"");
    U_ ret{};
    for (std::size_t i = 0; i < N; i++) {
      ret += data_[i] * rhs[i];
    }
    return ret;
  }

  /**
   * @brief dot product of a vector and a matrix
   *
   * For a Vector \f$ a \f$ of size \f$ N \f$ and a Matrix \f$ B \f$ of size \f$
   * N \times M \f$ the result is a Vector \f$ c \f$ of size \f$ M \f$,
   *
   *  \f$ c = a \cdot B \f$ with
   *
   *  \f$ c_{j} = a_1 b_{1j} + a_2 b_{2j} + ... + a_N b_{Nj} =
   * \sum_{i=1}^{N} a_i B_{ij} \f$
   *
   * Vector size must be equal to the size of the first Matrix dimension (N)
   *
   * For two objects of the same type, specifying the return type is optional.
   * It will be of the type of the two objects by default.
   *
   * For two objects of different types, specifying the return type is required.
   *
   * return value is a Vector of the size of the second Matrix dimension (M)
   * containing the type of the two objects or else of the explicitly stated
   * type
   *
   * @par Example
   * @snippet example_vector.cpp vector matrix dot function
   * @tparam U
   * @tparam N2
   * @tparam M2
   * @tparam T2
   * @param rhs
   * @return std::conditional_t<std::is_same<U, void>::value, Vector<M2, T>,
   * Vector<M2, U>>
   */
  template <typename U = void, std::size_t N2, std::size_t M2, typename T2>
  std::conditional_t<std::is_same<U, void>::value, Vector<M2, T>, Vector<M2, U>>
  dot(const Matrix<N2, M2, T2> &rhs) const {
    static_assert(N == N2,
                  "Vector-Matrix dimension mismatch. Vector size must be equal "
                  "to the first dimension of the matrix");
    using U_ = std::conditional_t<!std::is_same<T, T2>::value, U, T>;
    static_assert(
        !std::is_same<U_, void>::value,
        "Vector and Matrix types are different. please specify the return "
        "type. e.g. \"vec.dot<float>(mat);\"");
    Vector<M2, U_> ret;
    for (std::size_t i = 0; i < M2; i++) {
      U_ sum{0};
      for (std::size_t k = 0; k < N; k++) {
        sum += (data_[k] * rhs[k][i]);
      }
      ret[i] = sum;
    }
    return ret;
  }

  /**
   * @brief calculates the standard deviation
   *
   * \f$ \sigma = \sqrt{\frac{\sum(x_i - \mu)^2}{N}} \f$
   *
   * @par Example
   * @snippet example_vector.cpp vector std function
   * @tparam U
   * @return U
   */
  template <class U = T>
  U std() const {
    U sum{0};
    U m = mean<U>();
    for (const auto &item : data_) {
      sum += mu::pow(item - m, 2);
    }
    return U(mu::sqrt(sum / N));
  }

  /**
   * @brief euclidean vector length
   *
   * returns the length as
   * - the type of this vector (default)
   * - the explicitly stated type
   *
   * @par Example
   * @snippet example_vector.cpp vector length function
   * @tparam U
   * @return U
   */
  template <class U = T>
  U length() const {
    return U(mu::sqrt(dot(*this)));
  }

  /**
   * @brief flips this vector, i.e. reverses its elements
   *
   * @par Example
   * @snippet example_vector.cpp vector flip function
   */
  void flip() { mu::reverse(begin(), end()); }

  /**
   * @brief returns a flipped vector
   *
   * @par Example
   * @snippet example_vector.cpp vector flipped function
   * @see @ref flip()
   * @return Vector<N, T>
   */
  Vector<N, T> flipped() const {
    Vector<N, T> ret(*this);
    ret.flip();
    return ret;
  }

  /**
   * @brief sort vector elements in ascending order
   *
   * @par Example
   * @snippet example_vector.cpp vector sort function
   */
  void sort() { mu::sort(begin(), end()); }

  /**
   * @brief sort vector elements by providing a condition
   *
   * the condition should be a lambda function. it must return a bool
   *
   * @par Example
   * @snippet example_vector.cpp vector sort lambda function
   * @tparam Compare
   * @param comp
   */
  template <typename Compare>
  void sort(const Compare &comp) {
    mu::sort(begin(), end(), comp);
  }

  /**
   * @brief returns a sorted vector
   *
   * @par Example
   * @snippet example_vector.cpp vector sorted function
   * @return Vector<N, T>
   */
  Vector<N, T> sorted() const {
    Vector<N, T> ret(*this);
    ret.sort();
    return ret;
  }

  /**
   * @brief
   *
   * @par Example
   * @snippet example_vector.cpp vector sorted lambda function
   * @tparam Compare
   * @param comp
   * @return Vector<N, T>
   */
  template <typename Compare>
  Vector<N, T> sorted(const Compare &comp) const {
    Vector<N, T> ret(*this);
    ret.sort(comp);
    return ret;
  }

  /********************************* I/O ***********************************/

  /**
   * @brief print vector values
   *
   * @par Example
   * @snippet example_vector.cpp vector operator stream out
   * @tparam Nn
   * @tparam U
   * @param os
   * @param v
   * @return std::ostream&
   */
  template <std::size_t Nn, class U>
  friend std::ostream &operator<<(std::ostream &os, const Vector<Nn, U> &v);

  /*************************** vector <> vector ****************************/

  /**
   * @brief equality operator
   *
   * comparisons between different arithmetic types are possible. they are
   * subject to the c++ usual arithmetic conversions!
   *
   * checked both ways for equality. First, casting both values to the type of
   * the first argument, then casting both values to the type of the second
   * argument.
   *
   * @param rhs
   * @return bool true if equal, false if unequal
   */
  template <typename U = T>
  bool operator==(const Vector<N, U> &rhs) const {
    for (std::size_t i = 0; i < N; i++) {
      if (!mu::TypeTraits<T>::equals(data_[i], rhs[i]) ||
          !mu::TypeTraits<U>::equals(data_[i], rhs[i])) {
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
  bool operator!=(const Vector<N, U> &rhs) const {
    return !operator==(rhs);
  }

  /**
   * @brief plus equal operator
   *
   * subject to implicit conversions
   *
   * @tparam U
   * @param rhs
   * @return Vector<N, T>&
   */
  template <typename U = T>
  Vector<N, T> &operator+=(const Vector<N, U> &rhs) {
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
   * @return Vector<N, T>&
   */
  template <typename U = T>
  Vector<N, T> &operator-=(const Vector<N, U> &rhs) {
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
   * @return Vector<N, T>&
   */
  template <typename U = T>
  Vector<N, T> &operator*=(const Vector<N, U> &rhs) {
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
   * @return Vector<N, T>&
   */
  template <typename U = T>
  Vector<N, T> &operator/=(const Vector<N, U> &rhs) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] /= rhs[i];
    }
    return *this;
  }

  /*************************** vector <> scalar ****************************/

  /*
   * enable_if's are used to check for an arithmetic type at compile time
   * since it's the only type "family" that is allowed inside a Vector.
   *
   * the vector elements and the scalar can be of different types. c++ usual
   * conversion rules apply.
   *
   * placed inside this class because write access to member data is required
   */

  /**
   * @brief add a scalar to this vector
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic<TScalar>::value,Vector<N, T> &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T> &>
  operator+=(const TScalar &scalar) {
    for (auto &item : data_) {
      item += scalar;
    }
    return *this;
  }

  /**
   * @brief subtract a scalar from every element of this vector
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T>
   * &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T> &>
  operator-=(const TScalar &scalar) {
    for (auto &item : data_) {
      item -= scalar;
    }
    return *this;
  }

  /**
   * @brief multiply a scalar with this vector
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic<TScalar>::value,Vector<N, T> &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T> &>
  operator*=(const TScalar &scalar) {
    for (auto &item : data_) {
      item *= scalar;
    }
    return *this;
  }

  /**
   * @brief divide every element of this vector by a scalar
   *
   * division by zero on integral types triggers an assert
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T>
   * &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T> &>
  operator/=(const TScalar &scalar) {
    /* a division by zero of an integral type is undefined in standard c++
     * however, in the context of this Vector class, it is seen as rather
     * harmful and can become the source of non obvious bugs */
    if (std::is_integral<TScalar>::value) {
      assert(scalar != static_cast<TScalar>(0));
    }
    for (auto &item : data_) {
      item /= scalar;
    }
    return *this;
  }

  /*************************************************************************/

 protected:
  std::array<T, N> data_;
};

/********************************** I/O ************************************/

template <std::size_t Nn, class U>
std::ostream &operator<<(std::ostream &os, const Vector<Nn, U> &v) {
  os << "[ ";
  for (std::size_t i = 0; i < Nn; i++) {
    os << v.data_[i];
    if (i < (Nn - 1)) {
      os << ", ";
    } else {
      os << " ";
    }
  }
  os << "]";
  return os;
}

/**************************** vector <> vector *****************************/

/**
 * @brief plus operator
 *
 * @tparam N
 * @tparam T
 * @tparam U
 * @param lhs
 * @param rhs
 * @return Vector<N, T>
 */
template <std::size_t N, class T, class U = T>
inline Vector<N, T> operator+(const Vector<N, T> &lhs,
                              const Vector<N, U> &rhs) {
  return Vector<N, T>(lhs) += rhs;
}

/**
 * @brief minus operator
 *
 * @tparam N
 * @tparam T
 * @tparam U
 * @param lhs
 * @param rhs
 * @return Vector<N, T>
 */
template <std::size_t N, class T, class U = T>
inline Vector<N, T> operator-(const Vector<N, T> &lhs,
                              const Vector<N, U> &rhs) {
  return Vector<N, T>(lhs) -= rhs;
}

/**
 * @brief multiplication operator
 *
 * @tparam N
 * @tparam T
 * @tparam U
 * @param lhs
 * @param rhs
 * @return Vector<N, T>
 */
template <std::size_t N, class T, class U = T>
inline Vector<N, T> operator*(const Vector<N, T> &lhs,
                              const Vector<N, U> &rhs) {
  return Vector<N, T>(lhs) *= rhs;
}

/**
 * @brief division operator
 *
 * @tparam N
 * @tparam T
 * @tparam U
 * @param lhs
 * @param rhs
 * @return Vector<N, T>
 */
template <std::size_t N, class T, class U = T>
inline Vector<N, T> operator/(const Vector<N, T> &lhs,
                              const Vector<N, U> &rhs) {
  return Vector<N, T>(lhs) /= rhs;
}

/**************************** vector <> scalar *****************************/

/**
 * @brief vector and scalar addition
 *
 * see operator+=(scalar)
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Vector<N, T>> inline
operator+(const Vector<N, T> &lhs, const TScalar &rhs) {
  return Vector<N, T>(lhs) += rhs;
}

/**
 * @brief vector and scalar addition
 *
 * see operator+=(scalar)
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Vector<N, T>> inline
operator+(const TScalar &lhs, const Vector<N, T> &rhs) {
  return Vector<N, T>(rhs) += lhs;
}

/**
 * @brief subtract a scalar from this vector
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Vector<N, T>> inline
operator-(const Vector<N, T> &lhs, const TScalar &rhs) {
  return Vector<N, T>(lhs) -= rhs;
}

/**
 * @brief vector and scalar multiplication
 *
 * see operator*=(scalar)
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Vector<N, T>> inline
operator*(const Vector<N, T> &lhs, const TScalar &rhs) {
  return Vector<N, T>(lhs) *= rhs;
}

/**
 * @brief vector and scalar multiplication
 *
 * see operator*=(scalar)
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Vector<N, T>> inline
operator*(const TScalar &lhs, const Vector<N, T> &rhs) {
  return Vector<N, T>(rhs) *= lhs;
}

/**
 * @brief vector and scalar division
 *
 * @tparam N
 * @tparam T
 * @tparam TScalar
 * @param lhs
 * @param rhs
 * @return std::enable_if_t<std::is_arithmetic<TScalar>::value, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic<TScalar>::value,
                          Vector<N, T>> inline
operator/(const Vector<N, T> &lhs, const TScalar &rhs) {
  return Vector<N, T>(lhs) /= rhs;
}

/************************* convenience functions ***************************/

template <std::size_t N, class T>
inline T min(const Vector<N, T> &v) {
  return v.min();
}

template <std::size_t N, class T>
inline T max(const Vector<N, T> &v) {
  return v.max();
}

template <std::size_t N, class T>
inline T sum(const Vector<N, T> &v) {
  return v.sum();
}

template <class U = void, std::size_t N, typename T>
inline std::conditional_t<std::is_same<U, void>::value, T, U> mean(
    const Vector<N, T> &v) {
  return v
      .template mean<std::conditional_t<std::is_same<U, void>::value, T, U>>();
}

template <class U = void, std::size_t N1, class T1, std::size_t N2, class T2>
inline std::conditional_t<std::is_same<U, void>::value, T1, U> dot(
    const Vector<N1, T1> &lhs, const Vector<N2, T2> &rhs) {
  return lhs.template dot<U>(rhs);
}

template <typename U = void, std::size_t N, typename T, std::size_t N2,
          std::size_t M2, typename T2>
std::conditional_t<std::is_same<U, void>::value, Vector<M2, T>, Vector<M2, U>>
dot(const Vector<N, T> &lhs, const Matrix<N2, M2, T2> &rhs) {
  return lhs.template dot<U>(rhs);
}

template <std::size_t N, class T>
// NOLINTNEXTLINE(runtime/references) intentional non-const reference
inline void flip(Vector<N, T> &v) {
  v.flip();
}

template <std::size_t N, class T>
inline Vector<N, T> flipped(const Vector<N, T> &v) {
  return v.flipped();
}

template <std::size_t N, class T>
// NOLINTNEXTLINE(runtime/references) intentional non-const reference
inline void sort(Vector<N, T> &v) {
  v.sort();
}

template <std::size_t N, class T, typename Compare>
// NOLINTNEXTLINE(runtime/references) intentional non-const reference
inline void sort(Vector<N, T> &v, const Compare &compare) {
  v.sort(compare);
}

template <std::size_t N, class T>
inline Vector<N, T> sorted(const Vector<N, T> &v) {
  return v.sorted();
}

template <std::size_t N, class T, typename Compare>
inline Vector<N, T> sorted(const Vector<N, T> &v, const Compare &compare) {
  return v.sorted(compare);
}

template <std::size_t N, typename T = int>
inline Vector<N, T> ones() {
  return Vector<N, T>{T{1}};
}

template <std::size_t N, typename T = int>
inline Vector<N, T> zeros() {
  return Vector<N, T>{T{0}};
}

}  // namespace mu
#endif  // MU_VECTOR_H_