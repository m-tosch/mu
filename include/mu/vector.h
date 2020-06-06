#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

#include <vector>

template <std::size_t N, typename T>
class Vector {
 public:
  /**
   * @brief Construct a new Vector< N,  T> object
   *
   */
  Vector() = default;

  /**
   * @brief Destroy the Vector< N,  T> objec
   *
   */
  // ~Vector() = default;

  void FooBar();

 private:
  float x_, y_;
  std::vector<int> v_;
};

#endif  // MU_VECTOR_H_