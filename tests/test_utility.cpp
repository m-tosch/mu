#include <gtest/gtest.h>

#include <cmath>
#include <vector>

#include "mu/literals.h"
#include "mu/utility.h"
#include "typetraits.h"

/**
 * Instantiate the template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
template float mu::sin<float>(float);
template float mu::cos<float>(float);

/*
 * floating point types
 */
using FloatingPointTypes = ::testing::Types<float, double, long double>;

/********************************Utility***************************************/

template <typename T>
class UtilityFixture : public ::testing::Test {
 public:
  /* [-2pi | -pi | -pi/2 | -pi/4 | 0 | pi/4 | pi/2 | pi | 2pi] */
  std::vector<T> values = {-2 * mu::kPI, -mu::kPI, -mu::kPI2, -mu::kPI4,  0,
                           mu::kPI4,     mu::kPI2, mu::kPI,   2 * mu::kPI};
};

TYPED_TEST_SUITE(UtilityFixture, FloatingPointTypes);

TYPED_TEST(UtilityFixture, Sin) {
  /** action & assert */
  /* using mu TypeTraits ensures the correct comparison of floating point types
   * as opposed to e.g. gtest's EXPECT_FLOAT_EQ */
  for (TypeParam value : this->values) {
    EXPECT_TRUE(
        mu::TypeTraits<TypeParam>::equals(mu::sin(value), std::sin(value)));
  }
}

TYPED_TEST(UtilityFixture, Cos) {
  /** action & assert */
  /* using mu TypeTraits ensures the correct comparison of floating point types
   * as opposed to e.g. gtest's EXPECT_FLOAT_EQ */
  for (TypeParam value : this->values) {
    EXPECT_TRUE(
        mu::TypeTraits<TypeParam>::equals(mu::cos(value), std::cos(value)));
  }
}
