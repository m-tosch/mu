#ifndef MU_LITERALS_H_
#define MU_LITERALS_H_

#include <cmath>

namespace mu {

/* mathematical constants (cmath) */
constexpr double e = M_E;               /* euler constant */
constexpr double log2e = M_LOG2E;       /* log2(e) */
constexpr double log10e = M_LOG10E;     /* log10(e) */
constexpr double ln2 = M_LN2;           /* ln(2) */
constexpr double ln10 = M_LN10;         /* ln(10) */
constexpr double pi = M_PI;             /* pi */
constexpr double pi2 = M_PI_2;          /* pi/2 */
constexpr double pi4 = M_PI_4;          /* pi/4 */
constexpr double inv_pi = M_1_PI;       /* 1/pi */
constexpr double sqrt2 = M_SQRT2;       /* sqrt(2) */
constexpr double inv_sqrt2 = M_SQRT1_2; /* 1/sqrt(2) */

/* floating point epsilons (e.g. used for comparison) */
constexpr float eps_float = 1.0e-5F;
constexpr double eps_double = 1.0e-14;
constexpr long double eps_long_double = 1.0e-14L;

}  // namespace mu

#endif  // MU_LITERALS_H_