#include "gtest/gtest.h"
#include "vector.h"

TEST(Vector, ConstructorDefault) {
  // arrange
  bool c = std::is_default_constructible<Vector<2, int>>::value;
  // assert
  EXPECT_TRUE(c);
}

TEST(Vector, ConstructorSingleValueInit) {
  // arrange
  Vector<2, float> v{0.0F};
  // assert
  EXPECT_FLOAT_EQ(v[0], 0.0F);
  EXPECT_FLOAT_EQ(v[1], 0.0F);
}

TEST(Vector, DestructDefault) {
  // arrange
  bool d = std::is_destructible<Vector<2, int>>::value;
  // assert
  EXPECT_TRUE(d);
}