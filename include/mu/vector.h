#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

#include <array>
#include <type_traits>

namespace mu {
/**
 * @brief A generic vector
 *
 * Can be instantiated with one of the following integral types or any
 * implementation-defined extended integer types, including any signed,
 * unsigned, and cv-qualified variants.
 * - bool
 * - char
 * - char16_t
 * - char32_t
 * - wchar_t
 * - short
 * - int
 * - long
 * - long long
 * Can be instantiated with one of the following floating-point types including
 * any cv-qualified variants.
 * - float
 * - double
 * - long double
 *
 * @tparam N size
 * @tparam T type
 */
template <std::size_t N, typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vector {
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
   * @brief Construct a new Vector object from an array
   *
   * @param data
   */
  explicit Vector(std::array<T, N> data) : data_(data) {}

  /**
   * @brief Construct a new Vector object from a single value
   *
   * @param value
   */
  explicit Vector(T value) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] = value;
    }
  }

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
   * @param other
   * @return bool true if equal, false if unequal
   */
  bool operator==(const Vector<N, T> &other) const {
    for (std::size_t i = 0; i < size(); i++) {
      if (data_[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  /**
   * @brief unequality operator
   *
   * @param other
   * @return bool true if unequal, false if equal
   */
  bool operator!=(const Vector<N, T> &other) const {
    return !this->operator==(other);
  }

  /**
   * @brief plus operator
   *
   * @param other
   * @return Vector<N, T>
   */
  Vector<N, T> operator+(const Vector<N, T> &other) const {
    Vector<N, T> res;
    for (std::size_t i = 0; i < size(); i++) {
      res[i] = data_[i] + other[i];
    }
    return res;
  }

  /**
   * @brief minus operator
   *
   * @param other
   * @return Vector<N, T>
   */
  Vector<N, T> operator-(const Vector<N, T> &other) const {
    Vector<N, T> res;
    for (std::size_t i = 0; i < size(); i++) {
      res[i] = data_[i] - other[i];
    }
    return res;
  }

  /**
   * @brief access an element within the vector
   *
   * does not throw an exception if \p idx is out of range
   *
   * @param idx
   * @return T&
   */
  T &operator[](int idx) noexcept { return data_[idx]; }

  /**
   * @brief const access an element within the vector
   *
   * does not throw an exception if \p idx is out of range
   *
   * @param idx
   * @return const T&
   */
  const T &operator[](int idx) const noexcept { return data_[idx]; }

  /**
   * @brief access an element within the vector
   *
   * @exception out of range
   * @param idx
   * @return T&
   */
  T &at(int idx) { return data_.at(idx); }

  /**
   * @brief const access an element within the vector
   *
   * @exception out of range
   * @param idx
   * @return const T&
   */
  const T &at(int idx) const { return data_.at(idx); }

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

 protected:
  std::array<T, N> data_;
};

}  // namespace mu
#endif  // MU_VECTOR_H_