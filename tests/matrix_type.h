#ifndef TESTS_MATRIX_TYPE_H_
#define TESTS_MATRIX_TYPE_H_

#include <array>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "matrix.h"

template <typename T>
class MatrixTypeFixture : public ::testing::Test {
 public:
  /* the true "value type" of the values that the matrix contains */
  using value_type = typename T::value_type::value_type;
  void SetUp() override {
    auto start = static_cast<value_type>(0);
    auto incr = static_cast<value_type>(1.5F);  // NOLINT
    /* put values into the test values "matrix" (array of array) */
    for (auto& inner : values) {
      for (auto& item : inner) {
        item = (start += incr);
      }
    }
  }
  /* dummy just for getting dimensions at compile time (inline variable c++17)*/
  static inline T dummy;
  /* test values. exact dimensions of the corresponding matrix-under-test */
  std::array<std::array<value_type, dummy.size()[1]>, dummy.size()[0]> values;
};

TYPED_TEST_SUITE_P(MatrixTypeFixture);

TYPED_TEST_P(MatrixTypeFixture, ConstructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_default_constructible<TypeParam>::value);
  /* std::is_trivially_constructible is true for Matrix but false for children*/
  EXPECT_TRUE(std::is_nothrow_default_constructible<TypeParam>::value);
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

TYPED_TEST_P(MatrixTypeFixture, MemberFuncSize) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::size_type size0 = obj.size()[0];
  typename TypeParam::size_type size1 = obj.size()[1];
  /** assert */
  EXPECT_EQ(size0, TypeParam().size()[0]);
  EXPECT_EQ(size1, TypeParam().size()[1]);
  EXPECT_TRUE(noexcept(obj.size()));
}

REGISTER_TYPED_TEST_SUITE_P(MatrixTypeFixture, ConstructorDefault,
                            DestructorDefault, ConstructorCopy, ConstructorMove,
                            OperatorCopyAssignment, OperatorMoveAssignment,
                            MemberFuncSize);

#endif  // TESTS_MATRIX_TYPE_H_