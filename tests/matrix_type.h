#ifndef TESTS_MATRIX_TYPE_H_
#define TESTS_MATRIX_TYPE_H_

#include <array>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "matrix.h"

template <typename T>
class MatrixTypeFixture : public ::testing::Test {
 public:
  void SetUp() override {
    // TODO
  }
};

TYPED_TEST_SUITE_P(MatrixTypeFixture);

TYPED_TEST_P(MatrixTypeFixture, ConstructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_default_constructible<TypeParam>::value);
  /* std::is_trivially_constructible is true for Matrix but false for children*/
  EXPECT_TRUE(std::is_nothrow_default_constructible<TypeParam>::value);
}

REGISTER_TYPED_TEST_SUITE_P(MatrixTypeFixture, ConstructorDefault);

#endif  // TESTS_MATRIX_TYPE_H_