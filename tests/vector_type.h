#ifndef TESTS_TEST_VECTOR_TYPE_H_
#define TESTS_TEST_VECTOR_TYPE_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <tuple>
#include <type_traits>
#include <utility>

#include "mu/vector.h"

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
  /** action & assert */
  EXPECT_TRUE(std::is_default_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_default_constructible<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, DestructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_destructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_destructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_destructible<TypeParam>::value);
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
  /** action & assert */
  EXPECT_TRUE(std::is_copy_constructible<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, ConstructorMove) {
  /** action & assert */
  EXPECT_TRUE(std::is_move_constructible<TypeParam>::value);
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

TYPED_TEST_P(VectorTypeFixture, MemberFuncBegin) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type res = *obj.begin();
  /** assert */
  EXPECT_EQ(res, obj[0]);
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncBeginConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  typename TypeParam::value_type res = *kObj.begin();
  /** assert */
  EXPECT_EQ(res, kObj[0]);
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncEnd) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  // the "end" returns an iterator to the element following the last element
  typename TypeParam::value_type res = *(obj.end() - 1);
  /** assert */
  EXPECT_EQ(res, obj[obj.size() - 1]);
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncEndConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  // the "end" returns an iterator to the element following the last element
  typename TypeParam::value_type res = *(kObj.end() - 1);
  /** assert */
  EXPECT_EQ(res, kObj[kObj.size() - 1]);
}

REGISTER_TYPED_TEST_SUITE_P(
    VectorTypeFixture, ConstructorDefault, DestructorDefault,
    ConstructorFromArray, ConstructorFromSingleValue, ConstructorCopy,
    ConstructorMove, OperatorCopyAssignment, OperatorMoveAssignment,
    OperatorEqualValuesMatch, OperatorEqualValuesDontMatch,
    OperatorNotEqualValuesMatch, OperatorNotEqualValuesDontMatch,
    OperatorBrackets, OperatorBracketsConst, MemberFuncAt, MemberFuncAtConst,
    MemberFuncSize, MemberFuncBegin, MemberFuncBeginConst, MemberFuncEnd,
    MemberFuncEndConst);

#endif  // TESTS_TEST_VECTOR_TYPE_H_