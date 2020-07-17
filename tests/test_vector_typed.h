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
  void SetUp() override {
    auto start = static_cast<typename T::value_type>(0);
    auto incr = static_cast<typename T::value_type>(1);
    std::generate(values.begin(), values.end(),
                  [&start, &incr]() { return start += incr; });
  }

  std::array<typename T::value_type, T().Size()> values;
};

TYPED_TEST_SUITE_P(VectorTypeFixture);

TYPED_TEST_P(VectorTypeFixture, ConstructorDefault) {
  /** assert */
  EXPECT_TRUE(std::is_default_constructible<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, DestructorDefault) {
  /** assert */
  EXPECT_TRUE(std::is_destructible<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, ConstructorFromArray) {
  /** arrange */
  TypeParam v{this->values};
  /** assert */
  EXPECT_FLOAT_EQ(v[0], this->values[0]);
  EXPECT_FLOAT_EQ(v[1], this->values[1]);
}

TYPED_TEST_P(VectorTypeFixture, ConstructorFromSingleValue) {
  /** arrange */
  TypeParam v{this->values[0]};
  /** assert */
  EXPECT_FLOAT_EQ(v[0], this->values[0]);
  EXPECT_FLOAT_EQ(v[1], this->values[0]);
}

REGISTER_TYPED_TEST_SUITE_P(VectorTypeFixture, ConstructorDefault,
                            DestructorDefault, ConstructorFromArray,
                            ConstructorFromSingleValue);

#endif  // TESTS_TEST_VECTOR_TYPED_H_