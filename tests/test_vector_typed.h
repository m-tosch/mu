#ifndef TESTS_TEST_VECTOR_TYPED_H_
#define TESTS_TEST_VECTOR_TYPED_H_

#include <tuple>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "vector.h"

template <typename T>
class VectorTypeFixture : public ::testing::Test {
 public:
  void SetUp() override {}

  std::array<typename T::value_type, T().Size()> values;
};

TYPED_TEST_SUITE_P(VectorTypeFixture);

TYPED_TEST_P(VectorTypeFixture, ConstructorDefault) {
  /** assert */
  EXPECT_TRUE(std::is_default_constructible<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, ConstructorFromArray) {
  /** arrange */
  TypeParam v{this->values};
  /** assert */
  EXPECT_FLOAT_EQ(v[0], 2.0F);
  EXPECT_FLOAT_EQ(v[1], 2.0F);
}

REGISTER_TYPED_TEST_SUITE_P(VectorTypeFixture, ConstructorDefault,
                            ConstructorFromArray);

#endif  // TESTS_TEST_VECTOR_TYPED_H_