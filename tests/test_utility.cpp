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
// can't be done since currently, functions from the std namespace are used

/*
 * floating point types
 */
using FloatingPointTypes = ::testing::Types<float, double, long double>;

/********************************Utility***************************************/

template <typename T>
class UtilityFixture : public ::testing::Test {
 public:
  /* [-2pi | -pi | -pi/2 | -pi/4 | 0 | pi/4 | pi/2 | pi | 2pi] */
  std::vector<T> pi_values = {-2 * mu::pi, -mu::pi, -mu::pi2, -mu::pi4,  0,
                              mu::pi4,     mu::pi2, mu::pi,   2 * mu::pi};
};

TYPED_TEST_SUITE(UtilityFixture, FloatingPointTypes);

/* some of the tests use mu TypeTraits to ensure the correct comparison of
 * floating point types as opposed to e.g. using gtest's EXPECT_FLOAT_EQ which
 * is designed to compare float values*/

TYPED_TEST(UtilityFixture, acos) {
  /** action & assert */
  for (TypeParam i = -1.0; i <= 1.0; i += 1.0) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::acos(i), std::acos(i)));
  }
}

TYPED_TEST(UtilityFixture, asin) {
  /** action & assert */
  for (TypeParam i = -1.0; i <= 1.0; i += 1.0) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::asin(i), std::asin(i)));
  }
}

TYPED_TEST(UtilityFixture, atan) {
  /** action & assert */
  for (TypeParam value : this->pi_values) {
    EXPECT_TRUE(
        mu::TypeTraits<TypeParam>::equals(mu::atan(value), std::atan(value)));
  }
}

TYPED_TEST(UtilityFixture, atan2) {
  /** action & assert */
  for (TypeParam i = 1.0; i >= -1.0; i -= 2.0) {
    for (TypeParam j = -1.0; j <= 1.0; j += 2.0) {
      EXPECT_TRUE(
          mu::TypeTraits<TypeParam>::equals(mu::atan2(i, j), std::atan2(i, j)));
    }
  }
}

TYPED_TEST(UtilityFixture, cos) {
  /** action & assert */
  for (TypeParam value : this->pi_values) {
    EXPECT_TRUE(
        mu::TypeTraits<TypeParam>::equals(mu::cos(value), std::cos(value)));
  }
}

TYPED_TEST(UtilityFixture, sin) {
  /** action & assert */
  for (TypeParam value : this->pi_values) {
    EXPECT_TRUE(
        mu::TypeTraits<TypeParam>::equals(mu::sin(value), std::sin(value)));
  }
}

TYPED_TEST(UtilityFixture, tan) {
  /** action & assert */
  for (TypeParam value : this->pi_values) {
    EXPECT_TRUE(
        mu::TypeTraits<TypeParam>::equals(mu::tan(value), std::tan(value)));
  }
}
