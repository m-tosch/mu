/**
 * @file literals.h
 *
 * constant values
 */
#ifndef MU_LITERALS_H_
#define MU_LITERALS_H_

#include <cmath>

namespace mu {

/* mathematical constants (cmath) */
/** @brief \f$ \mathrm{e} \approx 2.71828183 \f$ */
constexpr double e = M_E;
/** @brief \f$ \log_2 e \approx 1.44269504 \f$ */
constexpr double log2e = M_LOG2E;
/** @brief \f$ \log_{10} e \approx 0.43429448 \f$ */
constexpr double log10e = M_LOG10E;
/** @brief \f$ \ln 2 \approx 0.69314718 \f$ */
constexpr double ln2 = M_LN2;
/** @brief \f$ \ln 10 \approx 2.30258509 \f$ */
constexpr double ln10 = M_LN10;
/** @brief \f$ \pi \approx 3.14159265 \f$ */
constexpr double pi = M_PI;
/** @brief \f$ \frac{\pi}{2} \approx 1.57079633 \f$ */
constexpr double pi2 = M_PI_2;
/** @brief \f$ \frac{\pi}{4} \approx 0.78539816 \f$ */
constexpr double pi4 = M_PI_4;
/** @brief \f$ \frac{1}{\pi} \approx 0.31830989 \f$ */
constexpr double inv_pi = M_1_PI;
/** @brief \f$ \sqrt{2} \approx 1.41421356 \f$ */
constexpr double sqrt2 = M_SQRT2;
/** @brief \f$ \frac{1}{\sqrt{2}} \approx 0.70710678 \f$ */
constexpr double inv_sqrt2 = M_SQRT1_2;

/* floating point epsilons (e.g. used for comparison) */
constexpr float eps_float = 1.0e-5F;
constexpr double eps_double = 1.0e-14;
constexpr long double eps_long_double = 1.0e-14L;

}  // namespace mu

#endif  // MU_LITERALS_H_