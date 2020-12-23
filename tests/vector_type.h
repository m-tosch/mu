#ifndef TESTS_VECTOR_TYPE_H_
#define TESTS_VECTOR_TYPE_H_

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
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
class VectorTypeFixture : public virtual ::testing::Test {
 public:
  /* true "value" and "size" types of the values that the vector contains */
  using value_type = typename T::value_type;
  using size_type = typename T::size_type;
  void SetUp() override {
    auto start = static_cast<typename T::value_type>(0);
    auto incr = static_cast<typename T::value_type>(1.5F);  // NOLINT
    /* put values into the test values "vector" (array) */
    std::generate(values.begin(), values.end(),
                  [&start, &incr]() { return start += incr; });
  }

  /* dummy just for getting size at compile time (inline variable c++17) */
  static inline T dummy;
  /* test values. exact length of the corresponding vector-under-test */
  std::array<typename T::value_type, dummy.size()> values;
  /* some tests need a converted type, defined as
   * - floating point type -> int
   * - integral type -> float
   * if the test input type is neither integral nor floating point, the
   * converted type is equivalent to the test type (i.e. not converted) */
  using ConvertedType = std::conditional_t<
      std::is_integral_v<typename T::value_type>, float,
      std::conditional_t<std::is_floating_point_v<typename T::value_type>, int,
                         typename T::value_type>>;
};

TYPED_TEST_SUITE_P(VectorTypeFixture);

TYPED_TEST_P(VectorTypeFixture, ConstructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_default_constructible<TypeParam>::value);
  /* std::is_trivially_constructible is true for Vector but false for V 2D/3D */
  EXPECT_TRUE(std::is_nothrow_default_constructible<TypeParam>::value);
}

TYPED_TEST_P(VectorTypeFixture, ConstructorVariadicTemplateSize2) {
  /* hardcoding this for two arguments since the size must be known to correctly
   * call the variadic template constructor. the constructor itself is
   * (probably) also tested in Vector derived classes */
  static TypeParam dummy;  // just to get the size at compile time here
  if constexpr (dummy.size() == 2) {
    /** action */
    TypeParam obj{this->values[0], this->values[1]};
    /** assert */
    EXPECT_THAT(obj, ::testing::Pointwise(::testing::Eq(), this->values));
  }
}

TYPED_TEST_P(VectorTypeFixture, ConstructorVariadicTemplateAssignmentSize2) {
  static TypeParam dummy;
  if constexpr (dummy.size() == 2) {
    /** action */
    TypeParam obj = {this->values[0], this->values[1]};
    /** assert */
    EXPECT_THAT(obj, ::testing::Pointwise(::testing::Eq(), this->values));
  }
}

/* note: the following constructors are tested in the type combinations file:
 * - Vector constructor
 * - std::array constructor
 * - single value constructor
 * the rationale is that all of these constructors are able take a different
 * type, which must be tested.
 */

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
  // end() returns an iterator to the element following the last element
  typename TypeParam::value_type res = *(obj.end() - 1);
  /** assert */
  EXPECT_EQ(res, obj[obj.size() - 1]);
  EXPECT_TRUE(noexcept(*(obj.end() - 1)));
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncEndConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  // end() returns an iterator to the element following the last element
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
  typename TypeParam::value_type comp =
      std::accumulate(this->values.begin(), this->values.end(),
                      static_cast<typename TypeParam::value_type>(0));
  EXPECT_FLOAT_EQ(sum, comp);
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncMean) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type mean = obj.mean();
  /** assert */
  typename TypeParam::value_type comp =
      std::accumulate(this->values.begin(), this->values.end(),
                      static_cast<typename TypeParam::value_type>(0));
  comp /= this->values.size();
  EXPECT_FLOAT_EQ(mean, comp);
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncMeanConvertType) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::ConvertedType mean =
      obj.template mean<typename TestFixture::ConvertedType>();
  /** assert */
  typename TestFixture::ConvertedType comp =
      std::accumulate(this->values.begin(), this->values.end(),
                      static_cast<typename TypeParam::value_type>(0));
  comp /= this->values.size();
  EXPECT_FLOAT_EQ(mean, comp);
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncLength) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type len = obj.length();
  /** assert */
  typename TypeParam::value_type comp = std::sqrt(
      std::inner_product(obj.begin(), obj.end(), obj.begin(),
                         static_cast<typename TypeParam::value_type>(0)));
  EXPECT_FLOAT_EQ(len, comp);
}

TYPED_TEST_P(VectorTypeFixture, MemberFuncLengthConvertType) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::ConvertedType len =
      obj.template length<typename TestFixture::ConvertedType>();
  /** assert */
  typename TestFixture::ConvertedType comp = std::sqrt(
      std::inner_product(obj.begin(), obj.end(), obj.begin(),
                         static_cast<typename TypeParam::value_type>(0)));
  EXPECT_FLOAT_EQ(len, comp);
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
  /* 2. remove unwanted characters. leave ',' separator in */
  std::string s = ss.str();
  char chars[] = " []\n";
  for (unsigned int i = 0; i < strlen(chars); ++i) {              // NOLINT
    s.erase(std::remove(s.begin(), s.end(), chars[i]), s.end());  // NOLINT
  }
  std::stringstream sss;
  sss << s;
  /* 3. put values from string(stream) in a std::vector */
  using vtype = typename TestFixture::value_type;
  std::vector<vtype> v;
  vtype i{};
  while (sss >> i) {
    v.push_back(i);
    if (sss.peek() == ',') {
      sss.ignore();
    }
  }
  /* 4. copy vector to array for easier comparison via gtest macro */
  static TypeParam dummy;
  std::array<vtype, dummy.size()> arr;
  std::copy_n(v.begin(), dummy.size(), arr.begin());
  /** assert */
  EXPECT_THAT(this->values, ::testing::ContainerEq(arr));
}

/************************* convenience functions****************************/

TYPED_TEST_P(VectorTypeFixture, UtilityFuncMin) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type min_v = mu::min(obj);
  /** assert */
  EXPECT_EQ(min_v, *std::min_element(this->values.begin(), this->values.end()));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncMax) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type max_v = mu::max(obj);
  /** assert */
  EXPECT_EQ(max_v, *std::max_element(this->values.begin(), this->values.end()));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncSum) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type sum_v = mu::sum(obj);
  typename TypeParam::value_type comp =
      std::accumulate(this->values.begin(), this->values.end(),
                      static_cast<typename TypeParam::value_type>(0));
  /** assert */
  EXPECT_FLOAT_EQ(sum_v, comp);
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncMean) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type mean = mu::mean(obj);
  /** assert */
  typename TypeParam::value_type comp =
      std::accumulate(this->values.begin(), this->values.end(),
                      static_cast<typename TypeParam::value_type>(0));
  comp /= this->values.size();
  EXPECT_FLOAT_EQ(mean, comp);
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncMeanConvertType) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::ConvertedType mean =
      mu::mean<typename TestFixture::ConvertedType>(obj);
  /** assert */
  typename TestFixture::ConvertedType comp =
      std::accumulate(this->values.begin(), this->values.end(),
                      static_cast<typename TypeParam::value_type>(0));
  comp /= this->values.size();
  EXPECT_FLOAT_EQ(mean, comp);
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncFlip) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  mu::flip(obj);
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncFlipped) {
  /** arrange */
  TypeParam obj1{this->values};
  /** action */
  TypeParam obj2 = mu::flipped(obj1);
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
  mu::sort(obj);
  /** assert */
  TypeParam comp{this->values};
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncSortLambda) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  using vtype = typename TypeParam::value_type;
  mu::sort(obj, [](vtype a, vtype b) { return a > b; });  // descending
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
  TypeParam obj2 = mu::sorted(obj1);  // ascending
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
  TypeParam obj2 = mu::sorted(obj1, [](vtype a, vtype b) { return a > b; });
  /** assert */
  TypeParam comp{this->values};
  std::reverse(comp.begin(), comp.end());
  EXPECT_THAT(obj2, ::testing::ContainerEq(comp));
  /* secondary check to ensure that the original object was not changed */
  EXPECT_THAT(TypeParam(this->values), ::testing::ContainerEq(obj1));
}

TYPED_TEST_P(VectorTypeFixture, UtilityFuncOnes) {
  /** arrange */
  static TypeParam dummy;  // get the size at compile time
  /** action */
  TypeParam res = mu::ones<dummy.size()>();
  /** assert */
  TypeParam comp;
  auto one = static_cast<typename TestFixture::value_type>(1);
  std::generate(comp.begin(), comp.end(), [&one]() { return one; });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

REGISTER_TYPED_TEST_SUITE_P(
    VectorTypeFixture, ConstructorDefault, ConstructorVariadicTemplateSize2,
    ConstructorVariadicTemplateAssignmentSize2, DestructorDefault,
    ConstructorCopy, ConstructorMove, OperatorCopyAssignment,
    OperatorMoveAssignment, OperatorBrackets, OperatorBracketsConst,
    MemberFuncAt, MemberFuncAtConst, MemberFuncSize, MemberFuncBegin,
    MemberFuncBeginConst, MemberFuncEnd, MemberFuncEndConst, MemberFuncMin,
    MemberFuncMax, MemberFuncSum, MemberFuncMean, MemberFuncMeanConvertType,
    MemberFuncLength, MemberFuncLengthConvertType, MemberFuncFlip,
    MemberFuncFlipped, MemberFuncSort, MemberFuncSortLambda, MemberFuncSorted,
    MemberFuncSortedLambda, OperatorStreamOut, UtilityFuncMin, UtilityFuncMax,
    UtilityFuncSum, UtilityFuncMean, UtilityFuncMeanConvertType,
    UtilityFuncFlip, UtilityFuncFlipped, UtilityFuncSort, UtilityFuncSortLambda,
    UtilityFuncSorted, UtilityFuncSortedLambda, UtilityFuncOnes);

#endif  // TESTS_VECTOR_TYPE_H_