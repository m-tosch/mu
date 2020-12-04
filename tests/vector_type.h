#ifndef TESTS_VECTOR_TYPE_H_
#define TESTS_VECTOR_TYPE_H_

#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

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

  /* dummy just for getting size at compile time (inline variable c++17) */
  static inline T dummy;
  /* test values. exact length of the corresponding vector-under-test */
  std::array<typename T::value_type, dummy.size()> values;
};

TYPED_TEST_SUITE_P(VectorTypeFixture);

TYPED_TEST_P(VectorTypeFixture, ConstructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_default_constructible<TypeParam>::value);
  /* std::is_trivially_constructible is true for Vector but false for V 2D/3D */
  EXPECT_TRUE(std::is_nothrow_default_constructible<TypeParam>::value);
}

/* note: type casting constructor is tested in the vector-combinations file! */

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

TYPED_TEST_P(VectorTypeFixture, DestructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_destructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_destructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_destructible<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, ConstructorCopy) {
  /** action & assert */
  EXPECT_TRUE(std::is_copy_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_copy_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_copy_constructible<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, ConstructorMove) {
  /** action & assert */
  EXPECT_TRUE(std::is_move_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_move_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_move_constructible<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, OperatorCopyAssignment) {
  /** action & assert */
  EXPECT_TRUE(std::is_copy_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_copy_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_copy_assignable<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, OperatorMoveAssignment) {
  /** action & assert */
  EXPECT_TRUE(std::is_move_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_move_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_move_assignable<TypeParam>::value);
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
  TypeParam obj2{this->values};
  obj2[0] = 0;
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
  TypeParam obj2{this->values};
  obj2[0] = 0;
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
  EXPECT_TRUE(noexcept(obj[0]));
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
  EXPECT_TRUE(noexcept(kObj[0]));
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
  EXPECT_TRUE(noexcept(obj.size()));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncBegin) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type res = *obj.begin();
  /** assert */
  EXPECT_EQ(res, obj[0]);
  EXPECT_TRUE(noexcept(*obj.begin()));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncBeginConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  typename TypeParam::value_type res = *kObj.begin();
  /** assert */
  EXPECT_EQ(res, kObj[0]);
  EXPECT_TRUE(noexcept(*kObj.begin()));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncEnd) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  // the "end" returns an iterator to the element following the last element
  typename TypeParam::value_type res = *(obj.end() - 1);
  /** assert */
  EXPECT_EQ(res, obj[obj.size() - 1]);
  EXPECT_TRUE(noexcept(*(obj.end() - 1)));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncEndConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  // the "end" returns an iterator to the element following the last element
  typename TypeParam::value_type res = *(kObj.end() - 1);
  /** assert */
  EXPECT_EQ(res, kObj[kObj.size() - 1]);
  EXPECT_TRUE(noexcept(*(kObj.end() - 1)));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncMin) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type min = obj.min();
  /** assert */
  EXPECT_EQ(min, *std::min_element(this->values.begin(), this->values.end()));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncMax) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type max = obj.max();
  /** assert */
  EXPECT_EQ(max, *std::max_element(this->values.begin(), this->values.end()));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncSum) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type sum = obj.sum();
  /** assert */
  EXPECT_EQ(sum, std::accumulate(this->values.begin(), this->values.end(), 0));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncLength) {
  if constexpr (std::is_floating_point_v<typename TypeParam::value_type>) {
    /** arrange */
    TypeParam obj{this->values};
    /** action */
    typename TypeParam::value_type len = obj.length();
    /** assert */
    typename TypeParam::value_type comp =
        std::sqrt(std::inner_product(obj.begin(), obj.end(), obj.begin(), 0));
    EXPECT_EQ(len, comp);
  }
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncFlip) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  obj.flip();
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncFlipped) {
  /** arrange */
  TypeParam obj1{this->values};
  /** action */
  TypeParam obj2 = obj1.flipped();
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj2, ::testing::ContainerEq(comp));
  /* secondary check to ensure that the original object was not changed */
  EXPECT_THAT(TypeParam(this->values), ::testing::ContainerEq(obj1));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncSort) {
  /** arrange */
  TypeParam obj{this->values};
  std::reverse(obj.begin(), obj.end());
  /** action */
  obj.sort();  // ascending
  /** assert */
  TypeParam comp{this->values};
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncSortLambda) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  using vtype = typename TypeParam::value_type;
  obj.sort([](vtype a, vtype b) { return a > b; });  // descending
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncSorted) {
  /** arrange */
  TypeParam obj1{this->values};
  std::reverse(obj1.begin(), obj1.end());
  /** action */
  TypeParam obj2 = obj1.sorted();  // ascending
  /** assert */
  TypeParam comp{this->values};
  EXPECT_THAT(obj2, ::testing::ContainerEq(comp));
  /* secondary check to ensure that the original object was not changed */
  std::reverse(obj1.begin(), obj1.end());
  EXPECT_THAT(TypeParam(this->values), ::testing::ContainerEq(obj1));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncSortedLambda) {
  /** arrange */
  TypeParam obj1{this->values};
  /** action */
  using vtype = typename TypeParam::value_type;  // descending
  TypeParam obj2 = obj1.sorted([](vtype a, vtype b) { return a > b; });
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj2, ::testing::ContainerEq(comp));
  /* secondary check to ensure that the original object was not changed */
  EXPECT_THAT(TypeParam(this->values), ::testing::ContainerEq(obj1));
}

TYPED_TEST_P(VectorTypeFixture, OperatorStreamOut) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  /* 1. read vector ostream in a stringstream */
  std::stringstream ss;
  ss << obj;
  /* 2. remove first and last character */
  std::string s = ss.str().substr(1, ss.str().size() - 2);
  std::stringstream sss;
  sss << s;
  /* 3. put values from string(stream) in a vector */
  using vtype = typename TypeParam::value_type;
  std::vector<vtype> v;
  std::copy(std::istream_iterator<vtype>(sss), std::istream_iterator<vtype>(),
            std::back_inserter(v));
  /* 4. copy vector to array for easier comparison via gtest macro */
  static TypeParam dummy;
  std::array<vtype, dummy.size()> arr;
  std::copy_n(v.begin(), dummy.size(), arr.begin());
  /** assert */
  EXPECT_THAT(this->values, ::testing::ContainerEq(arr));
}

/************************** convenience functions *****************************/

TYPED_TEST_P(VectorTypeFixture, UtilityFuncMin) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type min_v = min(obj);
  /** assert */
  EXPECT_EQ(min_v, *std::min_element(this->values.begin(), this->values.end()));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncMax) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type max_v = max(obj);
  /** assert */
  EXPECT_EQ(max_v, *std::max_element(this->values.begin(), this->values.end()));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncSum) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type sum_v = sum(obj);
  /** assert */
  EXPECT_EQ(sum_v,
            std::accumulate(this->values.begin(), this->values.end(), 0));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncFlip) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  flip(obj);
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncFlipped) {
  /** arrange */
  TypeParam obj1{this->values};
  /** action */
  TypeParam obj2 = flipped(obj1);
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj2, ::testing::ContainerEq(comp));
  /* secondary check to ensure that the original object was not changed */
  EXPECT_THAT(TypeParam(this->values), ::testing::ContainerEq(obj1));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncSort) {
  /** arrange */
  TypeParam obj{this->values};
  std::reverse(obj.begin(), obj.end());
  /** action */
  sort(obj);
  /** assert */
  TypeParam comp{this->values};
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncSortLambda) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  using vtype = typename TypeParam::value_type;
  sort(obj, [](vtype a, vtype b) { return a > b; });  // descending
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncSorted) {
  /** arrange */
  TypeParam obj1{this->values};
  std::reverse(obj1.begin(), obj1.end());
  /** action */
  TypeParam obj2 = sorted(obj1);  // ascending
  /** assert */
  TypeParam comp{this->values};
  EXPECT_THAT(obj2, ::testing::ContainerEq(comp));
  /* secondary check to ensure that the original object was not changed */
  std::reverse(obj1.begin(), obj1.end());
  EXPECT_THAT(TypeParam(this->values), ::testing::ContainerEq(obj1));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncSortedLambda) {
  /** arrange */
  TypeParam obj1{this->values};
  /** action */
  using vtype = typename TypeParam::value_type;  // descending
  TypeParam obj2 = sorted(obj1, [](vtype a, vtype b) { return a > b; });
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj2, ::testing::ContainerEq(comp));
  /* secondary check to ensure that the original object was not changed */
  EXPECT_THAT(TypeParam(this->values), ::testing::ContainerEq(obj1));
}

REGISTER_TYPED_TEST_SUITE_P(
    VectorTypeFixture, ConstructorDefault, DestructorDefault,
    ConstructorFromArray, ConstructorFromSingleValue, ConstructorCopy,
    ConstructorMove, OperatorCopyAssignment, OperatorMoveAssignment,
    OperatorEqualValuesMatch, OperatorEqualValuesDontMatch,
    OperatorNotEqualValuesMatch, OperatorNotEqualValuesDontMatch,
    OperatorBrackets, OperatorBracketsConst, MemberFuncAt, MemberFuncAtConst,
    MemberFuncSize, MemberFuncBegin, MemberFuncBeginConst, MemberFuncEnd,
    MemberFuncEndConst, MemberFuncMin, MemberFuncMax, MemberFuncSum,
    MemberFuncLength, MemberFuncFlip, MemberFuncFlipped, MemberFuncSort,
    MemberFuncSortLambda, MemberFuncSorted, MemberFuncSortedLambda,
    OperatorStreamOut, UtilityFuncMin, UtilityFuncMax, UtilityFuncSum,
    UtilityFuncFlip, UtilityFuncFlipped, UtilityFuncSort, UtilityFuncSortLambda,
    UtilityFuncSorted, UtilityFuncSortedLambda);

#endif  // TESTS_VECTOR_TYPE_H_