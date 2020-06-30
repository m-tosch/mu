#include "gtest/gtest.h"
#include "vector.h"

/**
 * Instantiate this template class explicitly so that all functions
 * are generated and thus, the coverage report is complete.
 */
template class mu::Vector<2, float>;

TEST(Vector, ConstructorDefault) {
  /** arrange */
  bool c = std::is_default_constructible<mu::Vector<1, int>>::value;
  /** assert */
  EXPECT_TRUE(c);
}

TEST(Vector, ConstructorSingleValueInit) {
  /** arrange */
  mu::Vector<2, float> v{2.0F};
  /** assert */
  EXPECT_FLOAT_EQ(v[0], 2.0F);
  EXPECT_FLOAT_EQ(v[1], 2.0F);
}

TEST(Vector, DestructorDefault) {
  /** arrange */
  bool d = std::is_destructible<mu::Vector<1, int>>::value;
  /** assert */
  EXPECT_TRUE(d);
}

TEST(Vector, ConstructorCopy) {
  /** arrange */
  mu::Vector<1, float> v1{2.0F};
  /** action */
  mu::Vector<1, float> v2{v1};
  /** assert */
  EXPECT_FLOAT_EQ(v2[0], 2.0F);
}

TEST(Vector, ConstructorMove) {
  /** arrange */
  mu::Vector<1, float> v1{2.0F};
  /** action */
  mu::Vector<1, float> v2{std::move(v1)};
  /** assert */
  EXPECT_FLOAT_EQ(v2[0], 2.0F);
}

TEST(Vector, OperatorCopyAssignment) {
  /** arrange */
  mu::Vector<1, float> v1{2.0F};
  /** action */
  mu::Vector<1, float> v2 = v1;
  /** assert */
  EXPECT_FLOAT_EQ(v2[0], 2.0F);
}

TEST(Vector, OperatorMoveAssignment) {
  /** arrange */
  mu::Vector<1, float> v1{2.0F};
  /** action */
  mu::Vector<1, float> v2 = std::move(v1);
  /** assert */
  EXPECT_FLOAT_EQ(v2[0], 2.0F);
}

TEST(Vector, OperatorEqualsValuesSame) {
  /** arrange */
  mu::Vector<2, float> v1{1.0F};
  mu::Vector<2, float> v2{1.0F};
  /** action */
  bool eq = (v1 == v2);
  /** assert */
  EXPECT_TRUE(eq);
}

TEST(Vector, OperatorEqualsValuesDifferent) {
  /** arrange */
  mu::Vector<2, float> v1{1.0F};
  mu::Vector<2, float> v2{2.0F};
  /** action */
  bool eq = (v1 == v2);
  /** assert */
  EXPECT_FALSE(eq);
}

TEST(Vector, OperatorEqualsLengthDifferent) {
  /** arrange */
  mu::Vector<2, float> v1{1.0F};
  mu::Vector<3, float> v2{1.0F};
  /** action */
  bool eq = (v1 == v2);
  /** assert */
  EXPECT_FALSE(eq);
}

TEST(Vector, OperatorPlus) {
  /** arrange */
  mu::Vector<2, float> v1{1.0F};
  mu::Vector<2, float> v2{1.0F};
  /** action */
  mu::Vector<2, float> res = v1 + v2;
  /** assert */
  EXPECT_FLOAT_EQ(res[0], v1[0] + v2[1]);
  EXPECT_FLOAT_EQ(res[1], v1[0] + v2[1]);
}

TEST(Vector, OperatorMinus) {
  /** arrange */
  mu::Vector<2, float> v1{1.0F};
  mu::Vector<2, float> v2{1.0F};
  /** action */
  mu::Vector<2, float> res = v1 - v2;
  /** assert */
  EXPECT_FLOAT_EQ(res[0], v1[0] - v2[1]);
  EXPECT_FLOAT_EQ(res[1], v1[0] - v2[1]);
}

TEST(Vector, OperatorBrackets) {
  /** arrange */
  mu::Vector<2, float> v{2.0F};
  /** action */
  float a = v[0];
  float b = v[1];
  /** assert */
  EXPECT_FLOAT_EQ(a, 2.0F);
  EXPECT_FLOAT_EQ(b, 2.0F);
}

TEST(Vector, OperatorConstBrackets) {
  /** arrange */
  const mu::Vector<2, float> v{2.0F};
  /** action */
  float a = v[0];
  float b = v[1];
  /** assert */
  EXPECT_FLOAT_EQ(a, 2.0F);
  EXPECT_FLOAT_EQ(b, 2.0F);
}

TEST(Vector, AccessAtFunction) {
  /** arrange */
  mu::Vector<2, float> v{2.0F};
  /** action */
  float a = v.At(0);
  float b = v.At(1);
  /** assert */
  EXPECT_FLOAT_EQ(a, 2.0F);
  EXPECT_FLOAT_EQ(b, 2.0F);
}

TEST(Vector, AccessConstAtFunction) {
  /** arrange */
  const mu::Vector<2, float> v{2.0F};
  /** action */
  float a = v.At(0);
  float b = v.At(1);
  /** assert */
  EXPECT_FLOAT_EQ(a, 2.0F);
  EXPECT_FLOAT_EQ(b, 2.0F);
}

TEST(Vector, Size) {
  /** arrange */
  const int kMaxSize = 42;
  mu::Vector<kMaxSize, float> v{2.0F};
  /** action */
  std::size_t size = v.Size();
  /** assert */
  EXPECT_EQ(size, kMaxSize);
}
