#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

#include <bits/c++config.h>

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
  static_assert(N != 0, "vector dimension cannot be zero");
  static_assert(std::is_arithmetic<T>::value, "type T must be an arithmetic");

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
   * @brief Construct a new Vector object from an arbitrary amount of values
   *
   * the amount of values must match the static size of this Vector object.
   * allows object construction as "v{1,2,3}" AND "v = {1,2,3}"
   *
   * @param data
   */
  template <typename... Args>
  // NOLINTNEXTLINE(runtime/explicit) implicit conversion is intentional
  Vector(Args... args) : data_({args...}) {}

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
   * @brief plus operator
   *
   * @param rhs
   * @return Vector<N, T>
   */
  Vector<N, T> operator+(const Vector<N, T> &rhs) const {
    return Vector<N, T>(*this) += rhs;
  }

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
   * @brief minus operator
   *
   * @param rhs
   * @return Vector<N, T>
   */
  Vector<N, T> operator-(const Vector<N, T> &rhs) const {
    return Vector<N, T>(*this) -= rhs;
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
   * @brief access an element within the vector
   *
   * does not throw an exception if \p idx is out of range
   *
   * @param idx
   * @return T&
   */
  T &operator[](std::size_t idx) noexcept { return data_[idx]; }

  /**
   * @brief const access an element within the vector
   *
   * does not throw an exception if \p idx is out of range
   *
   * @param idx
   * @return const T&
   */
  const T &operator[](std::size_t idx) const noexcept { return data_[idx]; }

  /**
   * @brief access an element within the vector
   *
   * @exception out of range
   * @param idx
   * @return T&
   */
  T &at(std::size_t idx) { return data_.at(idx); }

  /**
   * @brief const access an element within the vector
   *
   * @exception out of range
   * @param idx
   * @return const T&
   */
  const T &at(std::size_t idx) const { return data_.at(idx); }

  // STL container relevant
  /**
   * @brief returns the size of the vector
   *
   * @return std::size_t
   */
  constexpr std::size_t size() const noexcept { return N; }

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
  T min() const;

  /**
   * @brief get the max value of the vector
   *
   * @return T
   */
  T max() const;

  /**
   * @brief sum up all the elements of the vector
   *
   * @return T
   */
  T sum() const;

  /**
   * @brief dot product of two vectors
   *
   * @param other
   * @return T
   */
  T dot(const Vector<N, T> &other) const;

  /**
   * @brief euclidean vector length
   *
   * only enabled for floating point types. returns the length as the type of
   * this vector
   *
   * @tparam T
   * @return std::enable_if<std::is_floating_point<U>::value, T>::type
   */
  template <class U = T>
  typename std::enable_if<std::is_floating_point<U>::value, T>::type length()
      const {
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
  Vector<N, T> flipped() {
    Vector<N, T> ret(*this);
    ret.flip();
    return ret;
  }

  /**
   * @brief sort vector elements in ascending order
   *
   */
  void sort() { std::sort(begin(), end()); }

  /**
   * @brief sort vector elements by providing a condition
   *
   * the condition should be a lambda function. it mus return a bool
   *
   * @tparam Compare
   * @param comp
   */
  template <typename Compare>
  void sort(const Compare comp) {
    std::sort(begin(), end(), comp);
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const Vector<N, T> &vector) {
    os << "[ ";
    for (auto v : vector.data_) {
      os << v << " ";
    }
    os << "]";
    return os;
  }

 protected:
  std::array<T, N> data_;
};  // namespace mu

template <std::size_t N, class T>
inline T Vector<N, T>::min() const {
  T ret(data_[0]);
  for (std::size_t i = 1; i < N; i++) {
    ret = mu::min(ret, data_[i]);
  }
  return ret;
}

template <std::size_t N, class T>
inline T Vector<N, T>::max() const {
  T ret(data_[0]);
  for (std::size_t i = 1; i < N; i++) {
    ret = mu::max(ret, data_[i]);
  }
  return ret;
}

template <std::size_t N, class T>
inline T Vector<N, T>::sum() const {
  T ret(data_[0]);
  for (std::size_t i = 1; i < N; i++) {
    ret += data_[i];
  }
  return ret;
}

template <std::size_t N, class T>
inline T Vector<N, T>::dot(const Vector<N, T> &other) const {
  T ret{};
  for (std::size_t i = 0; i < N; i++) {
    ret += data_[i] * other.data_[i];
  }
  return ret;
}

/************************* convenience functions*****************************/

template <std::size_t N, class T>
inline T dot(const Vector<N, T> &lhs, const Vector<N, T> &rhs) {
  return lhs.dot(rhs);
}

}  // namespace mu
#endif  // MU_VECTOR_H_