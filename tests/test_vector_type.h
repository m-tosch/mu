#ifndef TESTS_TEST_VECTOR_TYPE_H_
#define TESTS_TEST_VECTOR_TYPE_H_

#include <algorithm>
#include <tuple>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "vector.h"

/**
 * @brief test suite for objects of type "Vector"
 *
 * @tparam T a "Vector" type
 */
template <typename T>
class VectorTypeFixture : public ::testing::Test {
 public:
  void SetUp() override {
    auto start = static_cast<typename T::value_type>(0);
    auto incr = static_cast<typename T::value_type>(1);
    std::generate(values.begin(), values.end(),
                  [&start, &incr]() { return start += incr; });
  }

  std::array<typename T::value_type, T().size()> values;
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

TYPED_TEST_P(VectorTypeFixture, OperatorCopyAssignment) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  TypeParam res = obj;
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj));
}

TYPED_TEST_P(VectorTypeFixture, OperatorMoveAssignment) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  TypeParam res = std::move(obj);
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj));
}

TYPED_TEST_P(VectorTypeFixture, OperatorEqualValuesMatch) {
  /** arrange */
  TypeParam obj1{this->values};
  TypeParam obj2{this->values};
  /** action */
  bool res = (obj1 == obj2);
  /** assert */
  EXPECT_TRUE(res);
}

TYPED_TEST_P(VectorTypeFixture, OperatorEqualValuesDontMatch) {
  /** arrange */
  TypeParam obj1{this->values};
  TypeParam obj2{this->values[0]};
  /** action */
  bool res = (obj1 == obj2);
  /** assert */
  EXPECT_FALSE(res);
}

TYPED_TEST_P(VectorTypeFixture, OperatorNotEqualValuesMatch) {
  /** arrange */
  TypeParam obj1{this->values};
  TypeParam obj2{this->values};
  /** action */
  bool res = (obj1 != obj2);
  /** assert */
  EXPECT_FALSE(res);
}

TYPED_TEST_P(VectorTypeFixture, OperatorNotEqualValuesDontMatch) {
  /** arrange */
  TypeParam obj1{this->values};
  TypeParam obj2{this->values[0]};
  /** action */
  bool res = (obj1 != obj2);
  /** assert */
  EXPECT_TRUE(res);
}

TYPED_TEST_P(VectorTypeFixture, OperatorBrackets) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&obj, i = 0]() mutable { return obj[i++]; });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj));
}

TYPED_TEST_P(VectorTypeFixture, OperatorBracketsConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&kObj, i = 0]() mutable { return kObj[i++]; });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(kObj));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncAt) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&obj, i = 0]() mutable { return obj.at(i++); });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncAtConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&kObj, i = 0]() mutable { return kObj.at(i++); });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(kObj));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncSize) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::size_type size = obj.size();
  /** assert */
  EXPECT_EQ(size, TypeParam().size());
}

REGISTER_TYPED_TEST_SUITE_P(VectorTypeFixture, ConstructorDefault,
                            DestructorDefault, ConstructorFromArray,
                            ConstructorFromSingleValue, ConstructorCopy,
                            ConstructorMove, OperatorCopyAssignment,
                            OperatorMoveAssignment, OperatorEqualValuesMatch,
                            OperatorEqualValuesDontMatch,
                            OperatorNotEqualValuesMatch,
                            OperatorNotEqualValuesDontMatch, OperatorBrackets,
                            OperatorBracketsConst, MemberFuncAt,
                            MemberFuncAtConst, MemberFuncSize);

#endif  // TESTS_TEST_VECTOR_TYPE_H_