#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/literals.h"
#include "mu/vector2d.h"

TEST(Vector2D, ConstructorFromDifferentType) {
  //! [vector2d different type constructor]

  mu::Vector2D<float> a = {1.5F, 2.5F};
  mu::Vector2D<int> b = {a};

  //! [vector2d different type constructor]
  EXPECT_THAT(b, ::testing::ElementsAre(1, 2));
}

TEST(Vector2D, MemberFuncX) {
  //! [vector2d x function]

  mu::Vector2D<int> a = {7, 8};
  int x = a.x();

  //! [vector2d x function]
  EXPECT_EQ(x, 7);
}

TEST(Vector2D, MemberFuncXConst) {
  //! [vector2d const x function]

  const mu::Vector2D<int> a = {7, 8};
  int x = a.x();

  //! [vector2d const x function]
  EXPECT_EQ(x, 7);
}

TEST(Vector2D, MemberFuncY) {
  //! [vector2d y function]

  mu::Vector2D<int> a = {7, 8};
  int y = a.y();

  //! [vector2d y function]
  EXPECT_EQ(y, 8);
}

TEST(Vector2D, MemberFuncYConst) {
  //! [vector2d const y function]

  const mu::Vector2D<int> a = {7, 8};
  int y = a.y();

  //! [vector2d const y function]
  EXPECT_EQ(y, 8);
}

TEST(Vector2D, MemberFuncRotate) {
  //! [vector2d rotate function]

  // rotate by pi/2 multiple times
  mu::Vector2D<float> a = {1.0F, 0.0F};
  a.rotate(mu::pi2);  // [ 0, 1 ]
  a.rotate(mu::pi2);  // [ -1, 0 ]
  a.rotate(mu::pi2);  // [ 0, -1 ]
  a.rotate(mu::pi2);  // [ 1, 0 ]

  //! [vector2d rotate function]
  EXPECT_NEAR(a[0], 1.0F, 1.e-10F);
  EXPECT_NEAR(a[1], 0.0F, 1.e-10F);
}

TEST(Vector2D, MemberFuncRotated) {
  //! [vector2d rotated function]

  // rotated by pi/2. creates new vector
  mu::Vector2D<float> a = {1.0F, 0.0F};
  mu::Vector2D<float> b = a.rotated(mu::pi2);  // [ 0, 1 ]

  //! [vector2d rotated function]
  EXPECT_NEAR(b[0], 0.0F, 1.e-10F);
  EXPECT_NEAR(b[1], 1.0F, 1.e-10F);
}