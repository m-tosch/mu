#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "mu/vector.h"

TEST(Vector, MemberFuncDotMatrixMatrix) {
  //! [matrix matrix dot function]

  // same types
  mu::Matrix<2, 3, int> a{{1, 2, 3}, {4, 5, 6}};
  mu::Matrix<3, 2, int> b{{3, 4}, {5, 6}, {7, 8}};
  mu::Matrix<2, 2, int> res1 = a.dot(b);  // [ [ 34, 40 ], [ 79, 94 ] ]

  // different types (must specify internal precision)
  mu::Matrix<2, 3, float> c{{1.5F, 2.5F, 3.5F}, {4.5F, 5.5F, 6.5F}};
  mu::Matrix<3, 2, int> d{{3, 4}, {5, 6}, {7, 8}};
  mu::Matrix<2, 2, float> res2 = c.dot<int>(d);    // [[ 40, 49 ],[ 85, 103 ]]
  mu::Matrix<2, 2, float> res3 = c.dot<float>(d);  // [[ 41.5,49 ],[ 86.5,103 ]]

  //! [matrix matrix dot function]
  EXPECT_THAT(res1[0], ::testing::ElementsAre(34, 40));
  EXPECT_THAT(res1[1], ::testing::ElementsAre(79, 94));
  EXPECT_THAT(res2[0], ::testing::ElementsAre(40, 49));
  EXPECT_THAT(res2[1], ::testing::ElementsAre(85, 103));
  EXPECT_THAT(res3[0], ::testing::ElementsAre(41.5, 49));
  EXPECT_THAT(res3[1], ::testing::ElementsAre(86.5, 103));
}

TEST(Vector, MemberFuncDotMatrixVector) {
  //! [matrix vector dot function]

  // same types
  mu::Matrix<2, 3, int> a{{3, 4, 5}, {6, 7, 8}};
  mu::Vector<3, int> b{1, 2, 3};
  mu::Vector<2, int> res1 = a.dot(b);  // [ 26, 44 ]

  // different types (must specify internal precision)
  mu::Matrix<2, 3, int> c{{3, 4, 5}, {6, 7, 8}};
  mu::Vector<3, float> d{1.5F, 2.5F, 3.5F};
  mu::Vector<2, float> res2 = c.dot<int>(d);    // [ 31, 54 ]
  mu::Vector<2, float> res3 = c.dot<float>(d);  // [ 32, 54.5 ]

  //! [matrix vector dot function]
  EXPECT_THAT(res1, ::testing::ElementsAre(26, 44));
  EXPECT_THAT(res2, ::testing::ElementsAre(31, 54));
  EXPECT_THAT(res3, ::testing::ElementsAre(32, 54.5));
}
