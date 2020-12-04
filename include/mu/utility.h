#ifndef MU_UTILITY_H_
#define MU_UTILITY_H_

#include <algorithm>
#include <cmath>
#include <limits>

namespace mu {

/* the purpose of this file is to use some general purpose math
 * functions from inside the mu namespace. currently, std functions are used
 * but the implementation may/can change through this abstraction.
 * since the functions are "imported" using the "using" mechanism, they can't
 * be explicitly instantiated. thus, no coverage is available. */

/* algorithm */
using std::max;
using std::min;
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
using std::sin;
using std::sqrt;
using std::tan;

/* limits */
using std::numeric_limits;

}  // namespace mu

#endif  // MU_UTILITY_H_