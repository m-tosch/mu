#include <gtest/gtest-typed-test.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "test_vector_type.h"
#include "vector2d.h"

/**
 * Instantiate this template class explicitly so that all functions
 * are generated and thus, the coverage report is complete.
 */
template class mu::Vector2D<float>;

/**
 * Instantiate the Vector test suite
 */
using Vector2DTypes = ::testing::Types<mu::Vector2D<float>, mu::Vector2D<int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector2D, VectorTypeFixture, Vector2DTypes);

/******************************************************************************/

template <typename T>
class Vector2DTypeFixture : public VectorTypeFixture<T> {
 public:
  void SetUp() override {
    /* explicitly call base class setup */
    VectorTypeFixture<T>::SetUp();
  }
};

TYPED_TEST_SUITE(Vector2DTypeFixture, Vector2DTypes);

TYPED_TEST(Vector2DTypeFixture, ConstructorXandY) {
  /** arrange */
  TypeParam obj{this->values[0], this->values[1]};
  /** assert */
  EXPECT_THAT(obj, ::testing::Pointwise(::testing::Eq(), this->values));
}

TYPED_TEST(Vector2DTypeFixture, MemberFuncGetX) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type x = obj.x();
  /** assert */
  EXPECT_EQ(x, this->values[0]);
}

TYPED_TEST(Vector2DTypeFixture, MemberFuncGetY) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type y = obj.y();
  /** assert */
  EXPECT_EQ(y, this->values[1]);
}

TYPED_TEST(Vector2DTypeFixture, MemberFuncSetX) {
  /** arrange */
  TypeParam obj{};
  /** action */
  obj.x(this->values[0]);
  /** assert */
  EXPECT_EQ(obj.x(), this->values[0]);
}

TYPED_TEST(Vector2DTypeFixture, MemberFuncSetY) {
  /** arrange */
  TypeParam obj{};
  /** action */
  obj.y(this->values[1]);
  /** assert */
  EXPECT_EQ(obj.y(), this->values[1]);
}