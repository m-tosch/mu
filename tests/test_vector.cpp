#include "gtest/gtest.h"
#include "vector.h"

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
  const int max_size = 42;
  mu::Vector<max_size, int> v{2};
  /** action */
  std::size_t size = v.Size();
  /** assert */
  EXPECT_EQ(size, max_size);
}
