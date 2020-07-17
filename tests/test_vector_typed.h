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
  /** action */
  TypeParam obj{this->values};
  /** assert */
  EXPECT_THAT(obj, ::testing::Pointwise(::testing::FloatEq(), this->values));
}

TYPED_TEST_P(VectorTypeFixture, ConstructorFromSingleValue) {
  /** arrange */
  auto value = this->values[0];
  /** action */
  TypeParam obj{value};
  /** assert */
  EXPECT_THAT(obj, ::testing::Each(::testing::AllOf(::testing::Eq(value))));
}

TYPED_TEST_P(VectorTypeFixture, ConstructorCopy) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  TypeParam res{obj};
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj));
}

TYPED_TEST_P(VectorTypeFixture, ConstructorMove) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  TypeParam res{std::move(obj)};
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj));
}

REGISTER_TYPED_TEST_SUITE_P(VectorTypeFixture, ConstructorDefault,
                            DestructorDefault, ConstructorFromArray,
                            ConstructorFromSingleValue, ConstructorCopy,
                            ConstructorMove);

#endif  // TESTS_TEST_VECTOR_TYPED_H_