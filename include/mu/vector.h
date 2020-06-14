#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

#include <array>

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
  Vector(const Vector&& other) noexcept = default;

  /**
   * @brief
   *
   * @param idx
   * @return T&
   */
  const T& operator[](const int idx) const noexcept { return data_[idx]; }

 private:
  std::array<T, N> data_;
};

#endif  // MU_VECTOR_H_