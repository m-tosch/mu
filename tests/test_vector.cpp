#include "gtest/gtest.h"
#include "vector.h"

TEST(Vector, sample_test) {
  // Vector<2, float> v;
  // int a = 5 + 5;
  EXPECT_EQ(1, 1);
}

TEST(Vector, ConstructorSingleValueInit) {
  // arrange
  Vector<2, float> v{0.0f};

  // assert
  EXPECT_FLOAT_EQ(v[0], 0.0f);
  EXPECT_FLOAT_EQ(v[1], 0.0f);
}