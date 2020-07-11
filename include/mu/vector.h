#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

#include <array>
#include <type_traits>

namespace mu {
/**
 * @brief A generic Vector
 *
 * Can only be instantiated with one of the following numeric types:
 * - bool
 * - char
 * - char16_t
 * - char32_t
 * - wchar_t
 * - short
 * - long long
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
  /**
   * @brief Construct a new Vector object
   *
   */
  Vector() = default;

  /**
   * @brief Construct a new Vector object
   *
   * @param value
   */
  explicit Vector(T value) {
    for (std::size_t i = 0; i < N; i++) {
      data_[i] = value;
    }
  }

  // Vector(std::initializer_list<T> l) TODO

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
  Vector(const Vector& other) = default;

  /**
   * @brief Move construct a new Vector object
   *
   * @param other
   */
  Vector(Vector&& other) noexcept = default;

  /**
   * @brief Copy assignment operator
   *
   * @param other
   * @return Vector&
   */
  Vector& operator=(const Vector& other) = default;

  /**
   * @brief Move assignment operator
   *
   * @param other
   * @return Vector&
   */
  Vector& operator=(Vector&& other) noexcept = default;

  /**
   * @brief compare two objects for equality
   *
   * @tparam Nn size
   * @tparam Tt type
   * @param other
   * @return bool
   */
  template <std::size_t Nn, typename Tt>
  bool operator==(const Vector<Nn, Tt>& other) const {
    if (N != Nn) {
      return false;
    }
    for (std::size_t i = 0; i < Size(); i++) {
      if (data_[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  /**
   * @brief plus operator
   *
   * @param other
   * @return Vector<N, T>
   */
  template <std::size_t Nn, typename Tt>
  Vector<N, T> operator+(const Vector<Nn, Tt>& other) const {
    static_assert(N == Nn, "dimension mismatch");
    Vector<N, T> res;
    for (std::size_t i = 0; i < Size(); i++) {
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
  template <std::size_t Nn, typename Tt>
  Vector<N, T> operator-(const Vector<Nn, Tt>& other) const {
    static_assert(N == Nn, "dimension mismatch");
    Vector<N, T> res;
    for (std::size_t i = 0; i < Size(); i++) {
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
  T& operator[](int idx) noexcept { return data_[idx]; }

  /**
   * @brief const access an element within the vector
   *
   * does not throw an exception if \p idx is out of range
   *
   * @param idx
   * @return const T&
   */
  const T& operator[](int idx) const noexcept { return data_[idx]; }

  /**
   * @brief access an element within the vector
   *
   * @exception out of range
   * @param idx
   * @return T&
   */
  T& At(int idx) { return data_.at(idx); }

  /**
   * @brief const access an element within the vector
   *
   * @exception out of range
   * @param idx
   * @return const T&
   */
  const T& At(int idx) const { return data_.at(idx); }

  /**
   * @brief returns the size of the vector
   *
   * @return std::size_t
   */
  std::size_t Size() const noexcept { return N; }

 private:
  std::array<T, N> data_;
};

}  // namespace mu
#endif  // MU_VECTOR_H_