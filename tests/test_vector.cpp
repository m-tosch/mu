#include "gtest/gtest.h"
#include "vector.h"

TEST(Vector, ConstructorDefault) {
  /** arrange */
  bool c = std::is_default_constructible<Vector<1, int>>::value;
  /** assert */
  EXPECT_TRUE(c);
}

TEST(Vector, ConstructorSingleValueInit) {
  /** arrange */
  Vector<2, float> v{2.0F};
  /** assert */
  EXPECT_FLOAT_EQ(v[0], 2.0F);
  EXPECT_FLOAT_EQ(v[1], 2.0F);
}

TEST(Vector, DestructorDefault) {
  /** arrange */
  bool d = std::is_destructible<Vector<1, int>>::value;
  /** assert */
  EXPECT_TRUE(d);
}

TEST(Vector, ConstructorCopy) {
  /** arrange */
  Vector<1, float> v1{2.0F};
  /** action */
  Vector<1, float> v2{v1};
  /** assert */
  EXPECT_FLOAT_EQ(v2[0], 2.0F);
}

TEST(Vector, ConstructorMove) {
  /** arrange */
  Vector<1, float> v1{2.0F};
  /** action */
  Vector<1, float> v2{std::move(v1)};
  /** assert */
  EXPECT_FLOAT_EQ(v2[0], 2.0F);
}

TEST(Vector, OperatorCopyAssignment) {
  /** arrange */
  Vector<1, float> v1{2.0F};
  /** action */
  Vector<1, float> v2 = v1;
  /** assert */
  EXPECT_FLOAT_EQ(v2[0], 2.0F);
}

TEST(Vector, OperatorMoveAssignment) {
  /** arrange */
  Vector<1, float> v1{2.0F};
  /** action */
  Vector<1, float> v2 = std::move(v1);
  /** assert */
  EXPECT_FLOAT_EQ(v2[0], 2.0F);
}

TEST(Vector, OperatorBrackets) {
  /** arrange */
  Vector<2, float> v{2.0F};
  /** action */
  float a = v[0];
  float b = v[1];
  /** assert */
  EXPECT_FLOAT_EQ(a, 2.0F);
  EXPECT_FLOAT_EQ(b, 2.0F);
}

TEST(Vector, OperatorConstBrackets) {
  /** arrange */
  const Vector<2, float> v{2.0F};
  /** action */
  float a = v[0];
  float b = v[1];
  /** assert */
  EXPECT_FLOAT_EQ(a, 2.0F);
  EXPECT_FLOAT_EQ(b, 2.0F);
}
