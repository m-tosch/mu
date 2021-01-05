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
  for (std::size_t i = 0; i < a.size()[0]; i++) {
    EXPECT_THAT(a[i], ::testing::Each(::testing::AllOf(5)));
    EXPECT_THAT(b[i], ::testing::Each(::testing::AllOf(5)));
    EXPECT_THAT(c[i], ::testing::Each(::testing::AllOf(5)));
  }
}

TEST(Matrix, ConstructorCopy) {
  //! [matrix copy constructor]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  mu::Matrix<2, 2, int> b{a};

  //! [matrix copy constructor]
  EXPECT_THAT(b[0], ::testing::ContainerEq(a[0]));
  EXPECT_THAT(b[1], ::testing::ContainerEq(a[1]));
}

TEST(Matrix, ConstructorMove) {
  //! [matrix move constructor]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  mu::Matrix<2, 2, int> b{std::move(a)};

  //! [matrix move constructor]
  EXPECT_THAT(b[0], ::testing::ContainerEq(a[0]));
  EXPECT_THAT(b[1], ::testing::ContainerEq(a[1]));
}

TEST(Matrix, OperatorCopyAssignment) {
  //! [matrix copy assignment operator]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  mu::Matrix<2, 2, int> b = a;

  //! [matrix copy assignment operator]
  EXPECT_THAT(b[0], ::testing::ContainerEq(a[0]));
  EXPECT_THAT(b[1], ::testing::ContainerEq(a[1]));
}

TEST(Matrix, OperatorMoveAssignment) {
  //! [matrix move assignment operator]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  mu::Matrix<2, 2, int> b = std::move(a);

  //! [matrix move assignment operator]
  EXPECT_THAT(b[0], ::testing::ContainerEq(a[0]));
  EXPECT_THAT(b[1], ::testing::ContainerEq(a[1]));
}

TEST(Matrix, OperatorBrackets) {
  //! [matrix brackets operator]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  mu::Vector<2, int> b = a[0];  // [ 1, 2 ]
  int a21 = a[1][0];            // 3

  //! [matrix brackets operator]
  EXPECT_THAT(b, ::testing::ContainerEq(a[0]));
  EXPECT_EQ(a21, a[1][0]);
}

TEST(Matrix, OperatorBracketsConst) {
  //! [matrix const brackets operator]

  const mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  mu::Vector<2, int> b = a[0];  // [ 1, 2 ]
  int a21 = a[1][0];            // 3

  //! [matrix const brackets operator]
  EXPECT_THAT(b, ::testing::ContainerEq(a[0]));
  EXPECT_EQ(a21, a[1][0]);
}

TEST(Matrix, MemberFuncAt) {
  //! [matrix at function]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  mu::Vector<2, int> b = a.at(0);  // [ 1, 2 ]
  int a21 = a.at(1).at(0);         // 3

  //! [matrix at function]
  EXPECT_THAT(b, ::testing::ContainerEq(a[0]));
  EXPECT_EQ(a21, a[1][0]);
}

TEST(Matrix, MemberFuncAtConst) {
  //! [matrix const at function]

  const mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  mu::Vector<2, int> b = a.at(0);  // [ 1, 2 ]
  int a21 = a.at(1).at(0);         // 3

  //! [matrix const at function]
  EXPECT_THAT(b, ::testing::ContainerEq(a[0]));
  EXPECT_EQ(a21, a[1][0]);
}

TEST(Matrix, MemberFuncSize) {
  //! [matrix size function]

  mu::Matrix<2, 3, int> a{{1, 2, 4}, {2, 4, 8}};
  std::size_t n_rows = a.size()[0];  // 2
  std::size_t n_cols = a.size()[1];  // 3

  //! [matrix size function]
  EXPECT_EQ(n_rows, 2);
  EXPECT_EQ(n_cols, 3);
}

TEST(Matrix, MemberFuncNRows) {
  //! [matrix nrows function]

  mu::Matrix<2, 3, int> a{{1, 2, 4}, {2, 4, 8}};
  std::size_t n_rows = a.n_rows();  // 2

  //! [matrix nrows function]
  EXPECT_EQ(n_rows, 2);
}

TEST(Matrix, MemberFuncNCols) {
  //! [matrix ncols function]

  mu::Matrix<2, 3, int> a{{1, 2, 4}, {2, 4, 8}};
  std::size_t n_cols = a.n_cols();  // 3

  //! [matrix ncols function]
  EXPECT_EQ(n_cols, 3);
}

TEST(Matrix, MemberFuncBegin) {
  //! [matrix begin function]

  mu::Matrix<2, 3, int> a{{1, 2, 4}, {2, 4, 8}};
  mu::Vector<3, int> first = *a.begin();  // [ 1, 2, 4 ]

  //! [matrix begin function]
  EXPECT_THAT(first, ::testing::ElementsAre(1, 2, 4));
}

TEST(Matrix, MemberFuncBeginConst) {
  //! [matrix const begin function]

  const mu::Matrix<2, 3, int> a{{1, 2, 4}, {2, 4, 8}};
  mu::Vector<3, int> first = *a.begin();  // [ 1, 2, 4 ]

  //! [matrix const begin function]
  EXPECT_THAT(first, ::testing::ElementsAre(1, 2, 4));
}

TEST(Matrix, MemberFuncEnd) {
  //! [matrix end function]

  mu::Matrix<2, 3, int> a{{1, 2, 4}, {2, 4, 8}};
  mu::Vector<3, int> last = *(a.end() - 1);  // [ 2, 4, 8 ]

  //! [matrix end function]
  EXPECT_THAT(last, ::testing::ElementsAre(2, 4, 8));
}

TEST(Matrix, MemberFuncEndConst) {
  //! [matrix const end function]

  const mu::Matrix<2, 3, int> a{{1, 2, 4}, {2, 4, 8}};
  mu::Vector<3, int> last = *(a.end() - 1);  // [ 2, 4, 8 ]

  //! [matrix const end function]
  EXPECT_THAT(last, ::testing::ElementsAre(2, 4, 8));
}

TEST(Matrix, MemberFuncRow) {
  //! [matrix row function]

  mu::Matrix<2, 3, int> a{{1, 2, 4}, {2, 4, 8}};
  mu::Vector<3, int> first_row = a.row(0);  // [ 1, 2, 4 ]

  //! [matrix row function]
  EXPECT_THAT(first_row, ::testing::ElementsAre(1, 2, 4));
}

TEST(Matrix, MemberFuncCol) {
  //! [matrix row function]

  mu::Matrix<2, 3, int> a{{1, 2, 3}, {4, 5, 6}};
  mu::Vector<2, int> second_col = a.col(1);  // [ 2, 5 ]

  //! [matrix row function]
  EXPECT_THAT(second_col, ::testing::ElementsAre(2, 5));
}

TEST(Matrix, MemberFuncMin) {
  //! [matrix min function]

  mu::Matrix<2, 3, int> a{{8, 5, 3}, {4, 5, 6}};
  int min = a.min();  // 3

  //! [matrix min function]
  EXPECT_EQ(min, 3);
}

TEST(Matrix, MemberFuncMax) {
  //! [matrix max function]

  mu::Matrix<2, 3, int> a{{8, 5, 3}, {4, 5, 6}};
  int max = a.max();  // 8

  //! [matrix max function]
  EXPECT_EQ(max, 8);
}

TEST(Matrix, MemberFuncSum) {
  //! [matrix sum function]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  int sum = a.sum();  // 10

  //! [matrix sum function]
  EXPECT_EQ(sum, 10);
}

TEST(Matrix, MemberFuncMean) {
  //! [matrix mean function]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  float mean1 = a.mean();         // 2 (because a holds type int)
  float mean2 = a.mean<float>();  // 2.5F

  //! [matrix mean function]
  EXPECT_EQ(mean1, 2);
  EXPECT_EQ(mean2, 2.5F);
}

TEST(Matrix, MemberFuncDiag) {
  //! [matrix diag function]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  mu::Vector<2, int> diag = a.diag();  // [ 1, 4 ]

  //! [matrix diag function]
  EXPECT_THAT(diag, ::testing::ElementsAre(1, 4));
}

TEST(Matrix, MemberFuncDet) {
  //! [matrix det function]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  int det = a.det();  // -2

  //! [matrix det function]
  EXPECT_EQ(det, -2);
}

TEST(Matrix, MemberFuncTranspose) {
  //! [matrix transpose function]

  mu::Matrix<2, 2, int> a{{1, 2}, {3, 4}};
  a.transpose();

  //! [matrix transpose function]
  EXPECT_THAT(a[0], ::testing::ElementsAre(1, 3));
  EXPECT_THAT(a[1], ::testing::ElementsAre(2, 4));
}

TEST(Matrix, MemberFuncTransposed) {
  //! [matrix transposed function]

  mu::Matrix<2, 3, int> a{{1, 2, 3}, {4, 5, 6}};
  mu::Matrix<3, 2, int> a_transposed = a.transposed();

  //! [matrix transposed function]
  EXPECT_THAT(a_transposed[0], ::testing::ElementsAre(1, 4));
  EXPECT_THAT(a_transposed[1], ::testing::ElementsAre(2, 5));
  EXPECT_THAT(a_transposed[2], ::testing::ElementsAre(3, 6));
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

TEST(Matrix, MemberFuncStd) {
  //! [matrix std function]

  mu::Matrix<2, 2, int> a{{2, 3}, {5, 7}};
  float std1 = a.std();         // 1 (because a holds type int)
  float std2 = a.std<float>();  // 1.92028642

  //! [matrix std function]
  EXPECT_EQ(std1, 1);
  EXPECT_FLOAT_EQ(std2, 1.92028642F);
}

TEST(Matrix, OperatorStreamOut) {
  //! [matrix operator stream out]

  mu::Matrix<2, 2, int> a{{2, 3}, {5, 7}};
  // std::cout << a << std::endl;
  // [ [ 2, 3 ],
  //   [ 5, 7 ] ]

  //! [matrix operator stream out]
  EXPECT_THAT(a[0], ::testing::ElementsAre(2, 3));
  EXPECT_THAT(a[1], ::testing::ElementsAre(5, 7));
}