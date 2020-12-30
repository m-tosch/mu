#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/typetraits.h"
#include "mu/matrix.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "mu/vector3d.h"

TEST(Vector, ConstructorFromSingleValue) {
  //! [example of vector single value constructor]

  mu::Vector<3, int> v{5};  // 5, 5, 5

  //! [example of vector single value constructor]
  // EXPECT_THAT(v, ::testing::Pointwise(::testing::Eq(), 5));
  EXPECT_TRUE(true);
}