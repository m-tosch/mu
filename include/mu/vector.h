#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

#include <array>

template <std::size_t N, typename T>
class Vector {
 public:
  /**
   * @brief Construct a new Vector<N,  T> object
   *
   */
  Vector() = default;

  /**
   * @brief Construct a new Vector object
   * 
   * @param l 
   */
  Vector(std::initializer_list<T> l) : data_(l) {}

  /**
   * @brief Destroy the Vector< N,  T> objec
   *
   */
  ~Vector() = default;

  // int FooBar(int a) { return 10 + 10; }

 private:
  std::array<T, N> data_;
};

#endif  // MU_VECTOR_H_