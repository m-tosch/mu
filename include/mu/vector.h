#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

#include <array>

namespace mu {
/**
 * @brief A generic Vector
 *
 * @tparam N size
 * @tparam T type
 */
template <std::size_t N, typename T>
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
   * @brief const access an element within the vector
   *
   * @param idx
   * @return const T&
   */
  const T& operator[](int idx) const noexcept { return data_[idx]; }

  /**
   * @brief access an element within the vector
   *
   * @param idx
   * @return T&
   */
  T& operator[](int idx) noexcept { return data_[idx]; }

 private:
  std::array<T, N> data_;
};
}  // namespace mu
#endif  // MU_VECTOR_H_