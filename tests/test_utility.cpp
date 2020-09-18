#include <gtest/gtest.h>

#include <cmath>

#include "mu/literals.h"
#include "mu/utility.h"

/**
 * Instantiate the template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
template float mu::sin<float>(float);
template float mu::cos<float>(float);

/**
 * Instantiate the Vector test suite
 */
using FloatingPointTypes = ::testing::Types<float, double, long double>;

/********************************Utility***************************************/

// template <typename T>
class UtilityFixture : public ::testing::TestWithParam<float> {};

INSTANTIATE_TEST_SUITE_P(InstantiationName,  // just the name
                         UtilityFixture,
                         ::testing::Values(mu::kPI, mu::kPI2, mu::kPI4));

/* TODO value parameterized tests for mu::sin() */

/* TODO value parameterized tests for mu::cos() */
