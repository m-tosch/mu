#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <vector>

#include "mu/literals.h"
#include "mu/utility.h"
#include "typetraits.h"

/**
 * Instantiate the template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 *
 * cannot be done since currently, functions from the std namespace are used.
 */

/*
 * floating point types
 */
using FloatingPointTypes = ::testing::Types<float, double, long double>;

/********************************utility***************************************/

template <typename T>
class UtilityFixture : public ::testing::Test {
 public:
  /* [-2pi | -pi | -pi/2 | -pi/4 | 0 | pi/4 | pi/2 | pi | 2pi] */
  std::vector<T> pi_values = {-2 * mu::pi, -mu::pi, -mu::pi2, -mu::pi4,  0,
                              mu::pi4,     mu::pi2, mu::pi,   2 * mu::pi};
  /* [-1 | 0 | 1] */
  std::vector<T> minus_one_to_one = {-1, 0, 1};
  /* [1 | 0 | -1] */
  std::vector<T> one_to_minus_one = {1, 0, -1};
  /* [0 | 1]*/
  std::vector<T> zero_to_one = {0, 1};
};

TYPED_TEST_SUITE(UtilityFixture, FloatingPointTypes);

/* some of the tests use mu TypeTraits to ensure the correct comparison of
 * floating point types as opposed to e.g. using gtest's EXPECT_FLOAT_EQ which
 * is designed to compare float values*/

/********************************<algorithm>***********************************/
TYPED_TEST(UtilityFixture, max) {
  for (TypeParam v : this->minus_one_to_one) {
    for (TypeParam w : this->one_to_minus_one) {
      EXPECT_TRUE(
          mu::TypeTraits<TypeParam>::equals(mu::max(v, w), std::max(v, w)));
    }
  }
}

TYPED_TEST(UtilityFixture, min) {
  for (TypeParam v : this->minus_one_to_one) {
    for (TypeParam w : this->one_to_minus_one) {
      EXPECT_TRUE(
          mu::TypeTraits<TypeParam>::equals(mu::min(v, w), std::min(v, w)));
    }
  }
}

/**********************************<cmath>*************************************/
TYPED_TEST(UtilityFixture, acos) {
  for (TypeParam v : this->minus_one_to_one) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::acos(v), std::acos(v)));
  }
}

TYPED_TEST(UtilityFixture, asin) {
  for (TypeParam v : this->minus_one_to_one) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::asin(v), std::asin(v)));
  }
}

TYPED_TEST(UtilityFixture, atan) {
  for (TypeParam v : this->pi_values) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::atan(v), std::atan(v)));
  }
}

TYPED_TEST(UtilityFixture, atan2) {
  for (TypeParam v : this->minus_one_to_one) {
    for (TypeParam w : this->minus_one_to_one) {
      EXPECT_TRUE(
          mu::TypeTraits<TypeParam>::equals(mu::atan2(v, w), std::atan2(v, w)));
    }
  }
}

TYPED_TEST(UtilityFixture, cos) {
  for (TypeParam v : this->pi_values) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::cos(v), std::cos(v)));
  }
}

TYPED_TEST(UtilityFixture, exp) {
  for (TypeParam v : this->minus_one_to_one) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::exp(v), std::exp(v)));
  }
}

TYPED_TEST(UtilityFixture, exp2) {
  for (TypeParam v : this->minus_one_to_one) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::exp2(v), std::exp2(v)));
  }
}

TYPED_TEST(UtilityFixture, hypot) {
  for (TypeParam v : this->minus_one_to_one) {
    for (TypeParam w : this->minus_one_to_one) {
      EXPECT_TRUE(
          mu::TypeTraits<TypeParam>::equals(mu::hypot(v, w), std::hypot(v, w)));
    }
  }
}

TYPED_TEST(UtilityFixture, log) {
  for (TypeParam v : this->zero_to_one) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::log(v), std::log(v)));
  }
}

TYPED_TEST(UtilityFixture, log2) {
  for (TypeParam v : this->zero_to_one) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::log2(v), std::log2(v)));
  }
}

TYPED_TEST(UtilityFixture, sin) {
  for (TypeParam v : this->pi_values) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::sin(v), std::sin(v)));
  }
}

TYPED_TEST(UtilityFixture, tan) {
  for (TypeParam v : this->pi_values) {
    EXPECT_TRUE(mu::TypeTraits<TypeParam>::equals(mu::tan(v), std::tan(v)));
  }
}
