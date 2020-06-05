#ifndef MU_VECTOR_H_
#define MU_VECTOR_H_

template <std::size_t N, typename T>
class Vector {
 public:
  /**
   * @brief Construct a new Vector< N,  T> object
   *
   */
  Vector() = default;

  /**
   * @brief Destroy the Vector< N,  T> object
   *
   */
  ~Vector() = default;
};

#endif  // MU_VECTOR_H_