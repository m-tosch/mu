#include <tuple>

#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include "literals.h"
#include "mu/matrix.h"
#include "mu/utility.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "vector_type.h"

using Vector2DTypes = ::testing::Types<mu::Vector2D<float>, mu::Vector2D<int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector2D, VectorTypeFixture, Vector2DTypes);

/*******************************Vector2D***************************************/

template <typename T>
class Vector2DTypeFixture : public VectorTypeFixture<T> {
 public:
  void SetUp() override {  // NOLINT
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

TYPED_TEST(Vector2DTypeFixture, ConstructorFromParentInitialization) {
  /** arrange */
  mu::Vector<2, typename TypeParam::value_type> obj1{this->values};
  /** action */
  TypeParam obj2{obj1};
  /** assert */
  EXPECT_THAT(obj1, ::testing::ContainerEq(obj2));
}

TYPED_TEST(Vector2DTypeFixture, ConstructorFromParentCopyInitialization) {
  /** arrange */
  mu::Vector<2, typename TypeParam::value_type> obj1{this->values};
  /** action */
  TypeParam obj2 = obj1;
  /** assert */
  EXPECT_THAT(obj1, ::testing::ContainerEq(obj2));
}

TYPED_TEST(Vector2DTypeFixture, MemberVarX) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** action */
  typename TypeParam::value_type x = obj.x();
  /** assert */
  EXPECT_EQ(x, this->x);
  EXPECT_TRUE(noexcept(obj.x()));
}

TYPED_TEST(Vector2DTypeFixture, MemberVarXConst) {
  /** arrange */
  const TypeParam kObj{this->x, this->y};
  /** action */
  typename TypeParam::value_type x = kObj.x();
  /** assert */
  EXPECT_EQ(x, this->x);
  EXPECT_TRUE(noexcept(kObj.x()));
}

TYPED_TEST(Vector2DTypeFixture, MemberVarY) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** action */
  typename TypeParam::value_type y = obj.y();
  /** assert */
  EXPECT_EQ(y, this->y);
  EXPECT_TRUE(noexcept(obj.y()));
}

TYPED_TEST(Vector2DTypeFixture, MemberVarYConst) {
  /** arrange */
  const TypeParam kObj{this->x, this->y};
  /** action */
  typename TypeParam::value_type y = kObj.y();
  /** assert */
  EXPECT_EQ(y, this->y);
  EXPECT_TRUE(noexcept(kObj.y()));
}

/* since value-param. and typed tests can't be easily combined in one test
 * suite, this test tests for positive and negative rotation fully aware that
 * test code is duplicated. could be improved in the future */
TYPED_TEST(Vector2DTypeFixture, MemberFuncRotate) {
  /** arrange */
  TypeParam obj1{this->x, this->y};
  TypeParam obj2{this->x, this->y};
  const auto kAngle1 = mu::pi2;
  const auto kAngle2 = -mu::pi2;
  const typename TypeParam::value_type kLen1 = obj1.length();
  const typename TypeParam::value_type kLen2 = obj2.length();
  /** action */
  obj1.rotate(kAngle1);
  obj2.rotate(kAngle2);
  /** assert */
  typename TypeParam::value_type comp1_x =
      ((this->x * mu::cos(kAngle1)) - (this->y * mu::sin(kAngle1)));
  typename TypeParam::value_type comp1_y =
      ((this->x * mu::sin(kAngle1)) + (this->y * mu::cos(kAngle1)));
  EXPECT_EQ(obj1.x(), comp1_x);
  EXPECT_EQ(obj1.y(), comp1_y);
  EXPECT_EQ(kLen1, obj1.length());  // length must be same as before rotation
  typename TypeParam::value_type comp2_x =
      ((this->x * mu::cos(kAngle2)) - (this->y * mu::sin(kAngle2)));
  typename TypeParam::value_type comp2_y =
      ((this->x * mu::sin(kAngle2)) + (this->y * mu::cos(kAngle2)));
  EXPECT_EQ(obj2.x(), comp2_x);
  EXPECT_EQ(obj2.y(), comp2_y);
  EXPECT_EQ(kLen2, obj2.length());
}

TYPED_TEST(Vector2DTypeFixture, MemberFuncRotated) {
  /** arrange */
  TypeParam obj1{this->x, this->y};
  TypeParam obj2{this->x, this->y};
  const auto kAngle1 = mu::pi2;
  const auto kAngle2 = -mu::pi2;
  const typename TypeParam::value_type kLen1 = obj1.length();
  const typename TypeParam::value_type kLen2 = obj2.length();
  /** action */
  TypeParam res1 = obj1.rotated(kAngle1);
  TypeParam res2 = obj2.rotated(kAngle2);
  /** assert */
  typename TypeParam::value_type comp1_x =
      ((this->x * mu::cos(kAngle1)) - (this->y * mu::sin(kAngle1)));
  typename TypeParam::value_type comp1_y =
      ((this->x * mu::sin(kAngle1)) + (this->y * mu::cos(kAngle1)));
  EXPECT_EQ(res1.x(), comp1_x);
  EXPECT_EQ(res1.y(), comp1_y);
  EXPECT_EQ(kLen1, res1.length());  // length must be same as before rotation
  typename TypeParam::value_type comp2_x =
      ((this->x * mu::cos(kAngle2)) - (this->y * mu::sin(kAngle2)));
  typename TypeParam::value_type comp2_y =
      ((this->x * mu::sin(kAngle2)) + (this->y * mu::cos(kAngle2)));
  EXPECT_EQ(res2.x(), comp2_x);
  EXPECT_EQ(res2.y(), comp2_y);
  EXPECT_EQ(kLen2, res2.length());
}