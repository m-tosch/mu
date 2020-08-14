#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "mu/vector.h"
#include "mu/vector2d.h"
#include "vector_type.h"

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
  void SetUp() override {  // NOLINT gtest method naming
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

TYPED_TEST(Vector2DTypeFixture, ConstructorXY) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** assert */
  EXPECT_THAT(obj, ::testing::Pointwise(::testing::Eq(), this->values));
}

TYPED_TEST(Vector2DTypeFixture, ConstructorCopyInitialization) {
  /** arrange */
  mu::Vector<2, typename TypeParam::value_type> obj1{this->values};
  TypeParam obj2 = obj1;
  /** assert */
  EXPECT_THAT(obj1, ::testing::ContainerEq(obj2));
}

TYPED_TEST(Vector2DTypeFixture, MemberVarX) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** action */
  typename TypeParam::value_type x = obj.x;
  /** assert */
  EXPECT_EQ(x, this->x);
}

TYPED_TEST(Vector2DTypeFixture, MemberVarY) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** action */
  typename TypeParam::value_type y = obj.y;
  /** assert */
  EXPECT_EQ(y, this->y);
}