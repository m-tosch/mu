/**
 * @file utility.h
 *
 * Utility math functions
 */
#ifndef MU_UTILITY_H_
#define MU_UTILITY_H_

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

namespace mu {

/* the purpose of this file is to use some general purpose math
 * functions from inside the mu namespace. currently, std functions are used
 * but the implementation may/can change through this abstraction.
 * since the functions are "imported" using the "using" mechanism, they can't
 * be explicitly instantiated. thus, no coverage is available. */

/* algorithm */
using std::max;
using std::min;
using std::reverse;
using std::sort;

/* cmath */
using std::abs;
using std::acos;
using std::asin;
using std::atan;
using std::atan2;
using std::cos;
using std::exp;
using std::exp2;
using std::hypot;
using std::log;
using std::log2;
using std::pow;
using std::sin;
using std::sqrt;
using std::tan;

/* limits */
using std::numeric_limits;

/**
 * @brief calulates the determinant of an arbitrary matrix
 *
 * see
 * https://stackoverflow.com/questions/7898305/calculating-the-determinant-in-c
 *
 * @tparam T
 * @param matrix
 * @return T
 */
template <typename T>
T calc_det(std::vector<std::vector<T>> matrix) {
  T ret = 0;
  // 1x1
  if (matrix.size() == 1) {
    return matrix[0][0];
  }
  // 2x2
  if (matrix.size() == 2) {
    ret = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    return ret;
  }
  // 3x3 or higher
  for (std::size_t p = 0; p < matrix[0].size(); p++) {
    // this loop iterates on each elements of the first row in the matrix.
    // at each element we cancel the row and column it exist in
    // and form a matrix from the rest of the elements in the matrix
    std::vector<std::vector<T>> temp_matrix;  // to hold the shaped matrix;
    for (std::size_t i = 1; i < matrix.size(); i++) {
      // iteration will start from row one cancelling the first row values
      std::vector<T> temp_row;
      for (std::size_t j = 0; j < matrix[i].size(); j++) {
        // iteration will pass all cells of the i row excluding the j
        // value that match p column
        if (j != p) {
          temp_row.push_back(matrix[i][j]);  // add current cell to TempRow
        }
      }
      if (temp_row.size() > 0) {
        temp_matrix.push_back(temp_row);
      }
      // after adding each row of the new matrix to the vector temp_row
      // we add it to the vector temp_matrix which is the vector where the
      // new matrix will be formed
    }
    ret = ret + matrix[0][p] * pow(-1, p) * calc_det(temp_matrix);
    // then we calculate the value of determinant by using a recursive way
    // where we re-call the function by passing to it the new formed matrix
    // we keep doing this until we get our determinant
  }
  return ret;
}

}  // namespace mu

#endif  // MU_UTILITY_H_