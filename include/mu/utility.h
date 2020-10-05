#ifndef MU_UTILITY_H_
#define MU_UTILITY_H_

#include <algorithm>
#include <cmath>

namespace mu {

/* the purpose of this file is to use some general purpose math
 * functions from inside the mu namespace. currently, std functions are used
 * but the implementation may/can change through this abstraction.
 * since the functions are "imported" using the "using" mechanism, they can't
 * be explicitly instantiated. thus, no coverage is available. */

/* algorithm */
using std::max;
using std::min;

/* cmath */
using std::abs;
using std::acos;
using std::asin;
using std::atan;
using std::atan2;
using std::cos;
using std::exp;
using std::exp2;
using std::log;
using std::log2;
using std::sin;
using std::sqrt;
using std::tan;

}  // namespace mu

#endif  // MU_UTILITY_H_