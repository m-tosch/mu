#include <gtest/gtest.h>

#include "mu/typetraits.h"

/**
 * Instantiate this template class and template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
// template struct mu::TypeTraits<float>;
// template struct mu::TypeTraitsFloatingPoint<float>;
/**
 * Instantiate the Vector test suite
 */
using FloatingPointTypes = ::testing::Types<float, double, long double>;

/*******************************Vector2D***************************************/

template <typename T>
class TypeTraitsEqualsFixture : public ::testing::Test {
 public:
  void SetUp() /*override*/ {  // NOLINT
    /* variables for convenience */
  }
  // typename T::value_type x;
  // typename T::value_type y;
};

TYPED_TEST_SUITE(TypeTraitsEqualsFixture, FloatingPointTypes);

TYPED_TEST(TypeTraitsEqualsFixture, EqualsAbsolute) {
  /** arrange */
  TypeParam lhs = 1.0F;
  TypeParam rhs = 1.0F;
  /** \action */
  bool res = mu::TypeTraits<TypeParam>::equals(lhs, rhs);
  /** assert */
  EXPECT_TRUE(res);
}
