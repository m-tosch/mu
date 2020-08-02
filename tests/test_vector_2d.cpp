#include <gtest/gtest-typed-test.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/vector2d.h"
#include "test_vector_type.h"

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

/*******************************Vector2D***************************************/

template <typename T>
class Vector2DTypeFixture : public VectorTypeFixture<T> {
 public:
  void SetUp() override {
    /* explicitly call base class setup */
    VectorTypeFixture<T>::SetUp();
    /* variables for convenience */
    x = this->values[0];
    y = this->values[1];
  }
  typename T::value_type x;
  typename T::value_type y;
};

TYPED_TEST_SUITE(Vector2DTypeFixture, Vector2DTypes);

TYPED_TEST(Vector2DTypeFixture, ConstructorXandY) {
  /** arrange */
  TypeParam obj{this->values};
  /** assert */
  EXPECT_THAT(obj, ::testing::Pointwise(::testing::Eq(), this->values));
}

TYPED_TEST(Vector2DTypeFixture, MemberFuncGetX) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** action */
  typename TypeParam::value_type x = obj.x();
  /** assert */
  EXPECT_EQ(x, this->x);
}

TYPED_TEST(Vector2DTypeFixture, MemberFuncGetY) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** action */
  typename TypeParam::value_type y = obj.y();
  /** assert */
  EXPECT_EQ(y, this->y);
}

TYPED_TEST(Vector2DTypeFixture, MemberFuncSetX) {
  /** arrange */
  TypeParam obj{};
  /** action */
  obj.x(this->x);
  /** assert */
  EXPECT_EQ(obj.x(), this->x);
}

TYPED_TEST(Vector2DTypeFixture, MemberFuncSetY) {
  /** arrange */
  TypeParam obj{};
  /** action */
  obj.y(this->y);
  /** assert */
  EXPECT_EQ(obj.y(), this->y);
}