#ifndef TESTS_MATRIX_TYPE_H_
#define TESTS_MATRIX_TYPE_H_

#include <array>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "matrix.h"

template <typename T>
class MatrixTypeFixture : public ::testing::Test {
 public:
  /* true "value" and "size" types of the values that the matrix contains */
  using value_type = typename T::value_type::value_type;
  using size_type = typename T::size_type;
  void SetUp() override {
    auto start = static_cast<value_type>(0);
    auto incr = static_cast<value_type>(1.5F);  // NOLINT
    /* put values into the test values "matrix" (array of array) */
    for (auto& inner : values) {  // rows
      for (auto& item : inner) {  // cols
        item = (start += incr);
      }
    }
  }
  /* dummy just for getting dimensions at compile time (inline variable c++17)*/
  static inline T dummy;
  /* test values. exact dimensions of the corresponding matrix-under-test */
  std::array<std::array<value_type, dummy.size()[1]>, dummy.size()[0]> values;
};

/**
 * @brief macro for comparing all matrix values to all values of the second
 * argument. both argument must be double nested "lists"
 *
 */
// NOLINTNEXTLINE macro is used for convenience and flexibility
#define EXPECT_THAT_ALL(arg1, arg2, eqfunc)                                  \
  {                                                                          \
    for (typename TestFixture::size_type i = 0; i < (arg1).size()[0]; i++) { \
      EXPECT_THAT((arg1)[i], ::testing::Pointwise(eqfunc, (arg2)[i]));       \
    }                                                                        \
  };

TYPED_TEST_SUITE_P(MatrixTypeFixture);

TYPED_TEST_P(MatrixTypeFixture, ConstructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_default_constructible<TypeParam>::value);
  /* std::is_trivially_constructible is true for Matrix but false for children*/
  EXPECT_TRUE(std::is_nothrow_default_constructible<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorFromArrayOfArrays) {
  /** action */
  TypeParam obj{this->values};
  /** assert */
  EXPECT_THAT_ALL(obj, this->values, ::testing::FloatEq())
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorFromArrayOfArraysAssignment) {
  /** action */
  TypeParam obj = this->values;
  /** assert */
  EXPECT_THAT_ALL(obj, this->values, ::testing::FloatEq())
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorFromArrayOfArraysAssignmentBraces) {
  /** action */
  TypeParam obj = {this->values};
  /** assert */
  EXPECT_THAT_ALL(obj, this->values, ::testing::FloatEq())
}

TYPED_TEST_P(MatrixTypeFixture, DestructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_destructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_destructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_destructible<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorCopy) {
  /** action & assert */
  EXPECT_TRUE(std::is_copy_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_copy_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_copy_constructible<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorMove) {
  /** action & assert */
  EXPECT_TRUE(std::is_move_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_move_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_move_constructible<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, OperatorCopyAssignment) {
  /** action & assert */
  EXPECT_TRUE(std::is_copy_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_copy_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_copy_assignable<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, OperatorMoveAssignment) {
  /** action & assert */
  EXPECT_TRUE(std::is_move_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_move_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_move_assignable<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, OperatorBrackets) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&obj, i = 0]() mutable { return obj[i++]; });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj));
  EXPECT_TRUE(noexcept(obj[0]));
}
TYPED_TEST_P(MatrixTypeFixture, OperatorBracketsConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&kObj, i = 0]() mutable { return kObj[i++]; });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(kObj));
  EXPECT_TRUE(noexcept(kObj[0]));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncSize) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::size_type size0 = obj.size()[0];
  typename TestFixture::size_type size1 = obj.size()[1];
  /** assert */
  EXPECT_EQ(size0, TypeParam().size()[0]);
  EXPECT_EQ(size1, TypeParam().size()[1]);
  EXPECT_TRUE(noexcept(obj.size()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncRows) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::size_type rows = obj.rows();
  /** assert */
  EXPECT_EQ(rows, TypeParam().rows());
  EXPECT_TRUE(noexcept(obj.rows()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncCols) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::size_type cols = obj.cols();
  /** assert */
  EXPECT_EQ(cols, TypeParam().cols());
  EXPECT_TRUE(noexcept(obj.cols()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncBegin) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type res = *obj.begin();
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj[0]));
  EXPECT_TRUE(noexcept(*obj.begin()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncBeginConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  typename TypeParam::value_type res = *kObj.begin();
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(kObj[0]));
  EXPECT_TRUE(noexcept(*kObj.begin()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncEnd) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  // end() returns an iterator to the element following the last element
  typename TypeParam::value_type res = *(obj.end() - 1);
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj[obj.size()[0] - 1]));
  EXPECT_TRUE(noexcept(*(obj.end() - 1)));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncEndConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  // end() returns an iterator to the element following the last element
  typename TypeParam::value_type res = *(kObj.end() - 1);
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(kObj[kObj.size()[0] - 1]));
  EXPECT_TRUE(noexcept(*(kObj.end() - 1)));
}

REGISTER_TYPED_TEST_SUITE_P(MatrixTypeFixture, ConstructorDefault,
                            ConstructorFromArrayOfArrays,
                            ConstructorFromArrayOfArraysAssignment,
                            ConstructorFromArrayOfArraysAssignmentBraces,
                            DestructorDefault, ConstructorCopy, ConstructorMove,
                            OperatorCopyAssignment, OperatorMoveAssignment,
                            OperatorBrackets, OperatorBracketsConst,
                            MemberFuncSize, MemberFuncRows, MemberFuncCols,
                            MemberFuncBegin, MemberFuncBeginConst,
                            MemberFuncEnd, MemberFuncEndConst);

#endif  // TESTS_MATRIX_TYPE_H_