#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

#include <algorithm>
#include <array>
#include <cmath>
#include <initializer_list>
#include <numeric>
#include <ostream>
#include <type_traits>

#include "mu/typetraits.h"
#include "mu/utility.h"

namespace mu {
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
 * @tparam N size
 * @tparam T type
 */
template <std::size_t N, typename T>
class Vector {
  static_assert(N != 0, "Vector dimension cannot be zero");
  static_assert(std::is_arithmetic_v<T>, "Vector type T must be an arithmetic");

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
   */
  constexpr Vector() = default;

  /**
   * @brief Construct a new Vector object from an amount of N values
   *
   * the amount of values must match the static size of this Vector object.
   * allows object construction as "v{1,2,3}" AND "v = {1,2,3}"
   *
   * @tparam TArgs
   * @param args
   */
  template <
      typename... TArgs,
      std::enable_if_t<
          sizeof...(TArgs) == N && (std::is_same_v<T, TArgs> && ...), int> = 0>
  // NOLINTNEXTLINE(runtime/explicit) implicit conversion is intentional
  Vector(TArgs... args) : data_{{args...}} {}

  /**
   * @brief Construct a new Vector from an existing Vector of a different type
   *
   * IMPORTANT implicit narrowing is applied
   * it is checked that the Vector sizes are the same
   *
   * Example:
   * @code
   * mu::Vector<2, int> a = {1, 2};
   * mu::Vector<2, double> b = {a};
   * @endcode
   *
   * @tparam Nn
   * @tparam Tt
   * @param other
   */
  template <std::size_t Nn, class Tt>
  // NOLINTNEXTLINE(runtime/explicit) implicit conversion is intentional
  Vector(const Vector<Nn, Tt> &other) {
    static_assert(N == Nn, "Vector size mismatch");
    for (std::size_t i = 0; i < N; i++) {
      data_[i] = static_cast<T>(other[i]);
    }
  }

  /**
   * @brief Construct a new Vector object from an std::array
   *
   * @param arr
   */
  explicit Vector(std::array<T, N> arr) : data_(arr) {}

  /**
   * @brief Construct a new Vector object from a single value
   *
   * @param value
   */
  explicit Vector(T value) { data_.fill(value); }

  /**
   * @brief Destroy the Vector object
   *
   */
  ~Vector() = default;

  /**
   * @brief Copy construct a new Vector object
   *
   * @param other
   */
  Vector(const Vector &other) = default;

  /**
   * @brief Move construct a new Vector object
   *
   * @param other
   */
  Vector(Vector &&other) noexcept = default;

  /**
   * @brief Copy assignment operator
   *
   * @param other
   * @return Vector&
   */
  Vector &operator=(const Vector &other) = default;

  /**
   * @brief Move assignment operator
   *
   * @param other
   * @return Vector&
   */
  Vector &operator=(Vector &&other) noexcept = default;

  /**
   * @brief access an element within the vector
   *
   * does not throw an exception if \p idx is out of range
   *
   * @param idx
   * @return T&
   */
  T &operator[](size_type idx) noexcept { return data_[idx]; }

  /**
   * @brief const access an element within the vector
   *
   * does not throw an exception if \p idx is out of range
   *
   * @param idx
   * @return const T&
   */
  const T &operator[](size_type idx) const noexcept { return data_[idx]; }

  /**
   * @brief access an element within the vector
   *
   * @exception out of range
   * @param idx
   * @return T&
   */
  T &at(size_type idx) { return data_.at(idx); }

  /**
   * @brief const access an element within the vector
   *
   * @exception out of range
   * @param idx
   * @return const T&
   */
  const T &at(size_type idx) const { return data_.at(idx); }

  // STL container relevant
  /**
   * @brief returns the size of the vector
   *
   * @return size_type
   */
  constexpr size_type size() const noexcept { return N; }

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

  /**
   * @brief get the min value of the vector
   *
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
   * @return T
   */
  T sum() const {
    T ret(data_[0]);
    for (std::size_t i = 1; i < N; i++) {
      ret += data_[i];
    }
    return ret;
  }

  /**
   * @brief dot product of two vectors
   *
   * @param other
   * @return T
   */
  T dot(const Vector<N, T> &other) const {
    T ret{};
    for (std::size_t i = 0; i < N; i++) {
      ret += data_[i] * other.data_[i];
    }
    return ret;
  }

  /**
   * @brief euclidean vector length
   *
   * only enabled for floating point types. returns the length as the type of
   * this vector
   *
   * @tparam T
   * @return std::enable_if_t<std::is_floating_point_v<U>, T>::type
   */
  template <class U = T>
  typename std::enable_if_t<std::is_floating_point_v<U>, T> length() const {
    return T(mu::sqrt(dot(*this)));
  }

  /**
   * @brief flips this vector, i.e. reverses its elements
   *
   * For example: (1,2,3) becomes (3,2,1)
   */
  void flip() { std::reverse(begin(), end()); }

  /**
   * @brief returns a flipped vector
   *
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
   */
  void sort() { mu::sort(begin(), end()); }

  /**
   * @brief sort vector elements by providing a condition
   *
   * the condition should be a lambda function. it must return a bool
   *
   * @tparam Compare
   * @param comp
   */
  template <typename Compare>
  void sort(const Compare comp) {
    mu::sort(begin(), end(), comp);
  }

  /**
   * @brief returns a sorted vector
   *
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
   * @tparam Compare
   * @param comp
   * @return Vector<N, T>
   */
  template <typename Compare>
  Vector<N, T> sorted(const Compare comp) const {
    Vector<N, T> ret(*this);
    ret.sort(comp);
    return ret;
  }

  /********************************** I/O *************************************/

  /**
   * @brief print vector values
   *
   * @tparam Nn
   * @tparam Tt
   * @param os
   * @param vec
   * @return std::ostream&
   */
  template <std::size_t Nn, class Tt>
  friend std::ostream &operator<<(std::ostream &os, const Vector<Nn, Tt> &vec);

  /**************************** vector <> vector *****************************/

  /**
   * @brief equality operator
   *
   * @param rhs
   * @return bool true if equal, false if unequal
   */
  bool operator==(const Vector<N, T> &rhs) const {
    for (std::size_t i = 0; i < N; i++) {
      if (!mu::TypeTraits<T>::equals(data_[i], rhs.data_[i])) {
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
  bool operator!=(const Vector<N, T> &rhs) const { return !operator==(rhs); }

  /**
   * @brief plus equal operator
   *
   * @param rhs
   * @return Vector<N, T>&
   */
  Vector<N, T> &operator+=(const Vector<N, T> &rhs) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] += rhs[i];
    }
    return *this;
  }

  /**
   * @brief minus equal operator
   *
   * @param rhs
   * @return Vector<N, T>&
   */
  Vector<N, T> &operator-=(const Vector<N, T> &rhs) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] -= rhs[i];
    }
    return *this;
  }

  /**
   * @brief multiplication equal operator
   *
   * @param rhs
   * @return Vector<N, T>&
   */
  Vector<N, T> &operator*=(const Vector<N, T> &rhs) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] *= rhs[i];
    }
    return *this;
  }

  /**
   * @brief divison equal operator
   *
   * @param rhs
   * @return Vector<N, T>&
   */
  Vector<N, T> &operator/=(const Vector<N, T> &rhs) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] /= rhs[i];
    }
    return *this;
  }

  /**************************** vector <> scalar *****************************/

  /* - enable_if's are used to check for an arithmetic type at compile time
   * since it's the only type "family" that is allowed inside a Vector. Here,
   * one could check if the scalar is of the same type as the one inside the
   * Vector directly instead..
   * ..but that gives rather unprecise error messages in case of a mismatch. the
   * enable_if is also needed to only provide this function to scalars
   * - the static_assert provides a more useful error message to the user at
   * compile time. It enforces the type equality requirement!
   *
   * placed inside this class because write access to member data is required
   */

  /**
   * @brief add a scalar to this vector
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic_v<TScalar>,Vector<N, T> &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T> &>
  operator+=(const TScalar &scalar) {
    static_assert(
        std::is_same_v<T, TScalar>,
        "for + or += "
        "the scalar must be of the same type that the Vector contains");
    for (std::size_t i = 0; i < N; i++) {
      data_[i] += scalar;
    }
    return *this;
  }

  /**
   * @brief subtract a scalar from every element of this vector
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T> &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T> &>
  operator-=(const TScalar &scalar) {
    static_assert(
        std::is_same_v<T, TScalar>,
        "for - or -= "
        "the scalar must be of the same type that the Vector contains");
    for (std::size_t i = 0; i < N; i++) {
      data_[i] -= scalar;
    }
    return *this;
  }

  /**
   * @brief multiply a scalar with this vector
   *
   * @tparam TScalar
   * @param scalar
   * @return std::enable_if_t<std::is_arithmetic_v<TScalar>,Vector<N, T> &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T> &>
  operator*=(const TScalar &scalar) {
    static_assert(
        std::is_same_v<T, TScalar>,
        "for * or *= "
        "the scalar must be of the same type that the Vector contains");
    for (std::size_t i = 0; i < N; i++) {
      data_[i] *= scalar;
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
   * @return std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T> &>
   */
  template <class TScalar>
  typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T> &>
  operator/=(const TScalar &scalar) {
    static_assert(
        std::is_same_v<T, TScalar>,
        "for / or /= "
        "the scalar must be of the same type that the Vector contains");
    /* a division by zero of an integral type is undefined in standard c++
     * however, in the context of this Vector class, it is seen as rather
     * harmful and can become the source of non obvious bugs */
    if constexpr (std::is_integral_v<TScalar>) {
      assert(scalar != static_cast<TScalar>(0));
    }
    for (std::size_t i = 0; i < N; i++) {
      data_[i] /= scalar;
    }
    return *this;
  }

  /****************************************************************************/

 protected:
  std::array<T, N> data_;
};

/*********************************** I/O **************************************/

template <std::size_t Nn, class Tt>
std::ostream &operator<<(std::ostream &os, const Vector<Nn, Tt> &vec) {
  os << "[ ";
  for (auto v : vec.data_) {
    os << v << " ";
  }
  os << "]";
  return os;
}

/***************************** vector <> vector *******************************/

/**
 * @brief plus operator
 *
 * @param lhs
 * @param rhs
 * @return Vector<N, T>
 */
template <std::size_t N, class T>
inline Vector<N, T> operator+(const Vector<N, T> &lhs,
                              const Vector<N, T> &rhs) {
  return Vector<N, T>(lhs) += rhs;
}

/**
 * @brief minus operator
 *
 * @param lhs
 * @param rhs
 * @return Vector<N, T>
 */
template <std::size_t N, class T>
inline Vector<N, T> operator-(const Vector<N, T> &lhs,
                              const Vector<N, T> &rhs) {
  return Vector<N, T>(lhs) -= rhs;
}

/**
 * @brief multiplication operator
 *
 * @param lhs
 * @param rhs
 * @return Vector<N, T>
 */
template <std::size_t N, class T>
inline Vector<N, T> operator*(const Vector<N, T> &lhs,
                              const Vector<N, T> &rhs) {
  return Vector<N, T>(lhs) *= rhs;
}

/**
 * @brief division operator
 *
 * @param lhs
 * @param rhs
 * @return Vector<N, T>
 */
template <std::size_t N, class T>
inline Vector<N, T> operator/(const Vector<N, T> &lhs,
                              const Vector<N, T> &rhs) {
  return Vector<N, T>(lhs) /= rhs;
}

/***************************** vector <> scalar *******************************/

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
 * @return std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>> inline
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
 * @return std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>> inline
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
 * @return std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>> inline
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
 * @return std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>> inline
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
 * @return std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>> inline
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
 * @return std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>>
 */
template <std::size_t N, class T, class TScalar>
typename std::enable_if_t<std::is_arithmetic_v<TScalar>, Vector<N, T>> inline
operator/(const Vector<N, T> &lhs, const TScalar &rhs) {
  return Vector<N, T>(lhs) /= rhs;
}

/************************** convenience functions *****************************/

template <std::size_t N, class T>
inline T min(const Vector<N, T> &other) {
  return other.min();
}

template <std::size_t N, class T>
inline T max(const Vector<N, T> &other) {
  return other.max();
}

template <std::size_t N, class T>
inline T sum(const Vector<N, T> &other) {
  return other.sum();
}

template <std::size_t N, class T>
inline T dot(const Vector<N, T> &lhs, const Vector<N, T> &rhs) {
  return lhs.dot(rhs);
}

template <std::size_t N, class T>
// NOLINTNEXTLINE(runtime/references) intentional non-const reference
inline void flip(Vector<N, T> &other) {
  other.flip();
}

template <std::size_t N, class T>
inline Vector<N, T> flipped(const Vector<N, T> &other) {
  return other.flipped();
}

template <std::size_t N, class T>
// NOLINTNEXTLINE(runtime/references) intentional non-const reference
inline void sort(Vector<N, T> &other) {
  other.sort();
}

template <std::size_t N, class T, typename Compare>
// NOLINTNEXTLINE(runtime/references) intentional non-const reference
inline void sort(Vector<N, T> &other, const Compare compare) {
  other.sort(compare);
}

template <std::size_t N, class T>
inline Vector<N, T> sorted(const Vector<N, T> &other) {
  return other.sorted();
}

/******************************************************************************/

}  // namespace mu
#endif  // MU_VECTOR_H_