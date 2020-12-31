#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "mu/vector.h"

TEST(Matrix, Constructor) {
  //! [matrix constructor]

  mu::Matrix<2, 2, int> a;

  //! [matrix constructor]
  EXPECT_EQ(a.size()[0], 2);
  EXPECT_EQ(a.size()[1], 2);
}

TEST(Matrix, ConstructorVariadicTemplate) {
  //! [matrix variadic template constructor]

  // direct initialization
  mu::Matrix<2, 3, int> a{{2, 3, 4}, {5, 6, 7}};
  // list initialization
  mu::Matrix<2, 3, int> b = {{2, 3, 4}, {5, 6, 7}};

  // hold references
  int num1 = 2;
  int num2 = 3;
  int num3 = 4;
  int num4 = 5;
  mu::Matrix<2, 2, std::reference_wrapper<int>> c{
      {std::ref(num1), std::ref(num2)}, {std::ref(num3), std::ref(num4)}};
  c += 1;  // this changes num1, num2, num3 and num4 too

  //! [matrix variadic template constructor]
  EXPECT_THAT(a[0], ::testing::ElementsAre(2, 3, 4));
  EXPECT_THAT(a[1], ::testing::ElementsAre(5, 6, 7));
  EXPECT_THAT(b[0], ::testing::ElementsAre(2, 3, 4));
  EXPECT_THAT(b[1], ::testing::ElementsAre(5, 6, 7));
  EXPECT_THAT(c[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(c[1], ::testing::ElementsAre(5, 6));
  EXPECT_EQ(num1, 3);
  EXPECT_EQ(num2, 4);
  EXPECT_EQ(num3, 5);
  EXPECT_EQ(num4, 6);
}

TEST(Matrix, ConstructorFromDifferentType) {
  //! [matrix different type constructor]

  mu::Matrix<2, 2, float> a = {{1.5F, 2.5F}, {3.5F, 4.5F}};
  mu::Matrix<2, 2, int> b = {a};

  //! [matrix different type constructor]
  EXPECT_THAT(b[0], ::testing::ElementsAre(1, 2));
  EXPECT_THAT(b[1], ::testing::ElementsAre(3, 4));
}

TEST(Matrix, ConstructorArrayOfVectors) {
  //! [matrix array of vectors constructor]

  std::array<mu::Vector<2, int>, 3> arr;
  arr[0] = {3, 4};
  arr[1] = {5, 6};
  arr[2] = {7, 8};

  // direct initialization
  mu::Matrix<3, 2, int> a{arr};
  // copy initialization
  mu::Matrix<3, 2, int> b = arr;
  // list initialization
  mu::Matrix<3, 2, int> c = {arr};

  //! [matrix array of vectors constructor]
  EXPECT_THAT(a[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(a[1], ::testing::ElementsAre(5, 6));
  EXPECT_THAT(a[2], ::testing::ElementsAre(7, 8));
  EXPECT_THAT(b[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(b[1], ::testing::ElementsAre(5, 6));
  EXPECT_THAT(b[2], ::testing::ElementsAre(7, 8));
  EXPECT_THAT(c[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(c[1], ::testing::ElementsAre(5, 6));
  EXPECT_THAT(c[2], ::testing::ElementsAre(7, 8));
}

TEST(Matrix, ConstructorArrayOfVectorsDifferentType) {
  //! [matrix array of vectors diff. type constructor]

  std::array<mu::Vector<2, float>, 3> arr;
  arr[0] = {3.5F, 4.5F};
  arr[1] = {5.5F, 6.5F};
  arr[2] = {7.5F, 8.5F};

  // direct initialization
  mu::Matrix<3, 2, int> a{arr};
  // copy initialization
  mu::Matrix<3, 2, int> b = arr;
  // list initialization
  mu::Matrix<3, 2, int> c = {arr};

  //! [matrix array of vectors diff. type constructor]
  EXPECT_THAT(a[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(a[1], ::testing::ElementsAre(5, 6));
  EXPECT_THAT(a[2], ::testing::ElementsAre(7, 8));
  EXPECT_THAT(b[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(b[1], ::testing::ElementsAre(5, 6));
  EXPECT_THAT(b[2], ::testing::ElementsAre(7, 8));
  EXPECT_THAT(c[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(c[1], ::testing::ElementsAre(5, 6));
  EXPECT_THAT(c[2], ::testing::ElementsAre(7, 8));
}

TEST(Matrix, ConstructorArray) {
  //! [matrix array of arrays constructor]

  std::array<std::array<int, 2>, 3> arr;
  arr[0] = {3, 4};
  arr[1] = {5, 6};
  arr[2] = {7, 8};

  // direct initialization
  mu::Matrix<3, 2, int> a{arr};
  // copy initialization
  mu::Matrix<3, 2, int> b = arr;
  // list initialization
  mu::Matrix<3, 2, int> c = {arr};

  //! [matrix array of arrays constructor]
  EXPECT_THAT(a[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(a[1], ::testing::ElementsAre(5, 6));
  EXPECT_THAT(a[2], ::testing::ElementsAre(7, 8));
  EXPECT_THAT(b[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(b[1], ::testing::ElementsAre(5, 6));
  EXPECT_THAT(b[2], ::testing::ElementsAre(7, 8));
  EXPECT_THAT(c[0], ::testing::ElementsAre(3, 4));
  EXPECT_THAT(c[1], ::testing::ElementsAre(5, 6));
  EXPECT_THAT(c[2], ::testing::ElementsAre(7, 8));
}

TEST(Matrix, ConstructorFromSingleValue) {
  //! [matrix single value constructor]

  // direct initialization
  mu::Matrix<3, 3, int> a{5};
  // copy initialization
  mu::Matrix<3, 3, int> b = 5;
  // list initialization
  mu::Matrix<3, 3, int> c = {5};

  //! [matrix single value constructor]
  EXPECT_THAT(a[0], ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(a[1], ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(a[2], ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(b[0], ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(b[1], ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(b[2], ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(c[0], ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(c[1], ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(c[2], ::testing::Each(::testing::AllOf(5)));
}

TEST(Matrix, MemberFuncDotMatrixMatrix) {
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

TEST(Matrix, MemberFuncDotMatrixVector) {
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
