#include "gtest/gtest.h"
#include "vector.h"

TEST(Vector, ConstructorSingleValueInit) {
  // arrange
  Vector<2, float> v{0.0F};

  // assert
  EXPECT_FLOAT_EQ(v[0], 0.0F);
  EXPECT_FLOAT_EQ(v[1], 0.0F);
}