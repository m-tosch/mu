#include <array>
#include <functional>
#include <iostream>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "mu/vector.h"

TEST(Vector, Constructor) {
  //! [vector constructor]

  mu::Vector<2, int> a;

  //! [vector constructor]
  EXPECT_EQ(a.size(), 2);
}

TEST(Vector, ConstructorVariadicTemplate) {
  //! [vector variadic template constructor]

  // direct initialization
  mu::Vector<2, int> a{2, 3};
  // list initialization
  mu::Vector<2, int> b = {2, 3};

  // hold references
  int num1 = 2;
  int num2 = 3;
  mu::Vector<2, std::reference_wrapper<int>> c{std::ref(num1), std::ref(num2)};
  c += 1;  // this changes num1 and num2 too

  //! [vector variadic template constructor]
  EXPECT_THAT(a, ::testing::ElementsAre(2, 3));
  EXPECT_THAT(b, ::testing::ElementsAre(2, 3));
  EXPECT_THAT(c, ::testing::ElementsAre(3, 4));
  EXPECT_EQ(num1, 3);
  EXPECT_EQ(num2, 4);
}

TEST(Vector, ConstructorFromDifferentType) {
  //! [vector different type constructor]

  mu::Vector<2, float> a = {1.5F, 2.5F};
  mu::Vector<2, int> b = {a};

  //! [vector different type constructor]
  EXPECT_THAT(b, ::testing::ElementsAre(1, 2));
}

TEST(Vector, ConstructorArray) {
  //! [vector array constructor]

  std::array<int, 3> arr = {3, 4, 5};
  // direct initialization
  mu::Vector<3, int> a{arr};
  // copy initialization
  mu::Vector<3, int> b = arr;
  // list initialization
  mu::Vector<3, int> c = {arr};

  //! [vector array constructor]
  EXPECT_THAT(a, ::testing::ElementsAre(3, 4, 5));
  EXPECT_THAT(b, ::testing::ElementsAre(3, 4, 5));
  EXPECT_THAT(c, ::testing::ElementsAre(3, 4, 5));
}

TEST(Vector, ConstructorArrayDifferentType) {
  //! [vector array different type constructor]

  std::array<float, 3> arr = {3.5F, 4.5F, 5.5F};
  // direct initialization
  mu::Vector<3, int> a{arr};
  // copy initialization
  mu::Vector<3, int> b = arr;
  // list initialization
  mu::Vector<3, int> c = {arr};

  //! [vector array different type constructor]
  EXPECT_THAT(a, ::testing::ElementsAre(3, 4, 5));
  EXPECT_THAT(b, ::testing::ElementsAre(3, 4, 5));
  EXPECT_THAT(c, ::testing::ElementsAre(3, 4, 5));
}

TEST(Vector, ConstructorFromSingleValue) {
  //! [vector single value constructor]

  // direct initialization
  mu::Vector<3, int> a{5};
  // copy initialization
  mu::Vector<3, int> b = 5;
  // list initialization
  mu::Vector<3, int> c = {5};

  //! [vector single value constructor]
  EXPECT_THAT(a, ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(b, ::testing::Each(::testing::AllOf(5)));
  EXPECT_THAT(c, ::testing::Each(::testing::AllOf(5)));
}

TEST(Vector, ConstructorCopy) {
  //! [vector copy constructor]

  mu::Vector<2, int> a{1, 2};
  mu::Vector<2, int> b{a};

  //! [vector copy constructor]
  EXPECT_THAT(b, ::testing::ContainerEq(a));
}

TEST(Vector, ConstructorMove) {
  //! [vector move constructor]

  mu::Vector<2, int> a{1, 2};
  mu::Vector<2, int> b{std::move(a)};

  //! [vector move constructor]
  EXPECT_THAT(b, ::testing::ContainerEq(a));
}

TEST(Vector, OperatorCopyAssignment) {
  //! [vector copy assignment operator]

  mu::Vector<2, int> a{1, 2};
  mu::Vector<2, int> b = a;

  //! [vector copy assignment operator]
  EXPECT_THAT(b, ::testing::ContainerEq(a));
}

TEST(Vector, OperatorMoveAssignment) {
  //! [vector move assignment operator]

  mu::Vector<2, int> a{1, 2};
  mu::Vector<2, int> b = std::move(a);

  //! [vector move assignment operator]
  EXPECT_THAT(b, ::testing::ContainerEq(a));
}

TEST(Vector, OperatorBrackets) {
  //! [vector brackets operator]

  mu::Vector<2, int> a{2, 3};
  int first = a[0];
  int second = a[1];

  //! [vector brackets operator]
  EXPECT_EQ(first, a[0]);
  EXPECT_EQ(second, a[1]);
}

TEST(Vector, OperatorBracketsConst) {
  //! [vector const brackets operator]

  const mu::Vector<2, int> a{2, 3};
  int first = a[0];
  int second = a[1];

  //! [vector const brackets operator]
  EXPECT_EQ(first, a[0]);
  EXPECT_EQ(second, a[1]);
}

TEST(Vector, MemberFuncAt) {
  //! [vector at function]

  mu::Vector<2, int> a{2, 3};
  int first = a.at(0);
  int second = a.at(1);

  //! [vector at function]
  EXPECT_EQ(first, a[0]);
  EXPECT_EQ(second, a[1]);
}

TEST(Vector, MemberFuncAtConst) {
  //! [vector const at function]

  const mu::Vector<2, int> a{2, 3};
  int first = a.at(0);
  int second = a.at(1);

  //! [vector const at function]
  EXPECT_EQ(first, a[0]);
  EXPECT_EQ(second, a[1]);
}

TEST(Vector, MemberFuncSize) {
  //! [vector size function]

  mu::Vector<3, int> a{2, 3, 4};
  std::size_t size = a.size();

  //! [vector size function]
  EXPECT_EQ(size, 3);
}

TEST(Vector, MemberFuncBegin) {
  //! [vector begin function]

  mu::Vector<2, int> a{2, 3};
  int first = *a.begin();

  //! [vector begin function]
  EXPECT_EQ(first, a[0]);
}

TEST(Vector, MemberFuncBeginConst) {
  //! [vector const begin function]

  const mu::Vector<2, int> a{2, 3};
  int first = *a.begin();

  //! [vector const begin function]
  EXPECT_EQ(first, a[0]);
}

TEST(Vector, MemberFuncEnd) {
  //! [vector end function]

  mu::Vector<2, int> a{2, 3};
  int last = *(a.end() - 1);

  //! [vector end function]
  EXPECT_EQ(last, a[1]);
}

TEST(Vector, MemberFuncEndConst) {
  //! [vector const end function]

  const mu::Vector<2, int> a{2, 3};
  int last = *(a.end() - 1);

  //! [vector const end function]
  EXPECT_EQ(last, a[1]);
}

TEST(Vector, MemberFuncMin) {
  //! [vector min function]

  mu::Vector<2, int> a{2, 3};
  int min = a.min();

  //! [vector min function]
  EXPECT_EQ(min, 2);
}

TEST(Vector, MemberFuncMax) {
  //! [vector max function]

  mu::Vector<2, int> a{2, 3};
  int max = a.max();

  //! [vector max function]
  EXPECT_EQ(max, 3);
}

TEST(Vector, MemberFuncSum) {
  //! [vector sum function]

  mu::Vector<2, int> a{2, 3};
  int sum = a.sum();

  //! [vector sum function]
  EXPECT_EQ(sum, 5);
}

TEST(Vector, MemberFuncMean) {
  //! [vector mean function]

  mu::Vector<2, int> a{2, 3};
  float mean1 = a.mean();         // 2 (because a holds type int)
  float mean2 = a.mean<float>();  // 2.5F

  //! [vector mean function]
  EXPECT_EQ(mean1, 2);
  EXPECT_EQ(mean2, 2.5F);
}

TEST(Vector, MemberFuncDotVectorVector) {
  //! [vector vector dot function]

  // same types
  mu::Vector<2, int> a{1, 2};
  mu::Vector<2, int> b{3, 4};
  int res1 = a.dot(b);  // 11

  // different types (must specify internal precision)
  mu::Vector<2, int> c{1, 2};
  mu::Vector<2, float> d{3.5F, 4.5F};
  float res2 = c.dot<int>(d);    // 12
  float res3 = c.dot<float>(d);  // 12.5

  //! [vector vector dot function]
  EXPECT_EQ(res1, 11);
  EXPECT_EQ(res2, 12);
  EXPECT_EQ(res3, 12.5F);
}

TEST(Vector, MemberFuncDotVectorMatrix) {
  //! [vector matrix dot function]

  // same types
  mu::Vector<2, int> a{1, 2};
  mu::Matrix<2, 3, int> b{{3, 4, 5}, {6, 7, 8}};
  mu::Vector<3, int> res1 = a.dot(b);  // [ 15, 18, 21 ]

  // different types (must specify internal precision)
  mu::Vector<2, float> c{1.5F, 2.5F};
  mu::Matrix<2, 3, int> d{{3, 4, 5}, {6, 7, 8}};
  mu::Vector<3, float> res2 = c.dot<int>(d);    // [ 19, 23, 27 ]
  mu::Vector<3, float> res3 = c.dot<float>(d);  // [ 19.5, 23.5, 27.5 ]

  //! [vector matrix dot function]
  EXPECT_THAT(res1, ::testing::ElementsAre(15, 18, 21));
  EXPECT_THAT(res2, ::testing::ElementsAre(19, 23, 27));
  EXPECT_THAT(res3, ::testing::ElementsAre(19.5, 23.5, 27.5));
}

TEST(Vector, MemberFuncStd) {
  //! [vector std function]

  mu::Vector<4, int> a{2, 3, 5, 7};
  float std1 = a.std();         // 1 (because a holds type int)
  float std2 = a.std<float>();  // 1.92028642

  //! [vector std function]
  EXPECT_EQ(std1, 1);
  EXPECT_FLOAT_EQ(std2, 1.92028642F);
}

TEST(Vector, MemberFuncLength) {
  //! [vector length function]

  mu::Vector<2, int> a{1, 2};
  float len1 = a.length();         // 2 (because a holds type int)
  float len2 = a.length<float>();  // 2.23606801

  //! [vector length function]
  EXPECT_EQ(len1, 2);
  EXPECT_FLOAT_EQ(len2, 2.23606801F);
}

TEST(Vector, MemberFuncFlip) {
  //! [vector flip function]

  mu::Vector<3, int> a{1, 2, 3};
  a.flip();  // a is now [ 3, 2, 1 ]

  //! [vector flip function]
  EXPECT_THAT(a, ::testing::ElementsAre(3, 2, 1));
}

TEST(Vector, MemberFuncFlipped) {
  //! [vector flipped function]

  mu::Vector<3, int> a{1, 2, 3};
  mu::Vector<3, int> b = a.flipped();  // b is now [ 3, 2, 1 ]

  //! [vector flipped function]
  EXPECT_THAT(b, ::testing::ElementsAre(3, 2, 1));
}

TEST(Vector, MemberFuncSort) {
  //! [vector sort function]

  mu::Vector<5, int> a{6, 4, 9, 3, 1};
  a.sort();  // a is now [ 1, 3, 4, 6, 9 ]

  //! [vector sort function]
  EXPECT_THAT(a, ::testing::ElementsAre(1, 3, 4, 6, 9));
}

TEST(Vector, MemberFuncSortLambda) {
  //! [vector sort lambda function]

  mu::Vector<5, int> a{6, 4, 9, 3, 1};
  a.sort([](int a, int b) { return a > b; });  // a is now [ 9, 6, 4, 3, 1 ]

  //! [vector sort lambda function]
  EXPECT_THAT(a, ::testing::ElementsAre(9, 6, 4, 3, 1));
}

TEST(Vector, MemberFuncSorted) {
  //! [vector sorted function]

  mu::Vector<5, int> a{6, 4, 9, 3, 1};
  mu::Vector<5, int> b = a.sorted();  // b is now [ 1, 3, 4, 6, 9 ]

  //! [vector sorted function]
  EXPECT_THAT(b, ::testing::ElementsAre(1, 3, 4, 6, 9));
}

TEST(Vector, MemberFuncSortedLambda) {
  //! [vector sorted lambda function]

  mu::Vector<5, int> a{6, 4, 9, 3, 1};
  mu::Vector<5, int> b = a.sorted(
      [](int a, int b) { return a > b; });  // b is now [ 9, 6, 4, 3, 1 ]

  //! [vector sorted lambda function]
  EXPECT_THAT(b, ::testing::ElementsAre(9, 6, 4, 3, 1));
}

TEST(Vector, OperatorStreamOut) {
  //! [vector operator stream out]

  mu::Vector<4, int> a{2, 3, 4, 5};
  // std::cout << a << std::endl;
  // [ 2, 3, 4, 5 ]

  //! [vector operator stream out]
  EXPECT_THAT(a, ::testing::ElementsAre(2, 3, 4, 5));
}