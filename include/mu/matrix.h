#ifndef MU_MATRIX_H_
#define MU_MATRIX_H_

#include <array>

#include "vector.h"

namespace mu {

/**
 * @brief A generic matrix
 *
 * @tparam N first matrix dimension
 * @tparam M second matrix dimension
 * @tparam T
 */
template <std::size_t N, std::size_t M, typename T>
class Matrix {
  static_assert(N != 0, "first matrix dimension cannot be zero");
  static_assert(M != 0, "second matrix dimension cannot be zero");

 public:
  /**
   * @brief Construct a new Vector object
   *
   */
  constexpr Matrix() = default;

 protected:
  std::array<Vector<N, T>, M> data_;
};
}  // namespace mu
#endif  // MU_MATRIX_H_