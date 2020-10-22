#include "gtest/gtest.h"
#include "mu/typetraits.h"

/**
 * NOTE: default instantiations for all floating point types are not needed
 * e.g. template struct mu::TypeTraitsFloatingPoint<float>
 * since the template specializations are already defined in TypeTraits. The
 * coverage will already be correctly reported. Since the functions are
 * generated, the coverage report is accurate.
 */

/**
 * Instantiate the Vector test suite
 */
using FloatingPointTypes = ::testing::Types<float, double, long double>;

/*******************************Vector2D***************************************/

template <typename T>
class TypeTraitsFixture : public ::testing::Test {};

TYPED_TEST_SUITE(TypeTraitsFixture, FloatingPointTypes);

TYPED_TEST(TypeTraitsFixture, EqualsAbsolute) {
  /** arrange */
  TypeParam lhs = 1.0;
  TypeParam rhs = 1.0;
  /** action */
  bool res = mu::TypeTraits<TypeParam>::equals(lhs, rhs);
  /** assert */
  EXPECT_TRUE(res);
}

TYPED_TEST(TypeTraitsFixture, EqualsCloseToZero) {
  /** arrange */
  /* two different, but close to zero values. smaller than std numeric_limits of
   * the respective floating point type. slightly different to triggered the
   * correct condition (close to zero)*/
  TypeParam lhs = 0.1 * std::numeric_limits<TypeParam>::min();
  TypeParam rhs = 0.2 * std::numeric_limits<TypeParam>::min();
  /** action */
  bool res = mu::TypeTraits<TypeParam>::equals(lhs, rhs);
  /** assert */
  EXPECT_FALSE(res);
}

TYPED_TEST(TypeTraitsFixture, EqualsRelative) {
  /** arrange */
  /* two different, but close to zero values. greater than std numeric_limits of
   * the respective floating point type. slightly different to triggered the
   * correct condition (relative error)*/
  TypeParam lhs = 100 * std::numeric_limits<TypeParam>::min();
  TypeParam rhs = 200 * std::numeric_limits<TypeParam>::min();
  /** action */
  bool res = mu::TypeTraits<TypeParam>::equals(lhs, rhs);
  /** assert */
  EXPECT_FALSE(res);
}