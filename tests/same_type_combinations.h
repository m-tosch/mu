#ifndef TESTS_SAME_TYPE_COMBINATIONS_H_
#define TESTS_SAME_TYPE_COMBINATIONS_H_

#include <algorithm>
#include <tuple>
#include <type_traits>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "matrix_type.h"
#include "vector_type.h"

/* abuse overloading to find out if the type the test is specified to run
 * contains a Vector-type, i.e. a Vector or a Vector-derived type */
std::false_type is_a_vector_impl(...);
template <std::size_t N, typename T>
std::true_type is_a_vector_impl(mu::Vector<N, T> const volatile &);
template <typename T>
using is_a_vector = decltype(is_a_vector_impl(std::declval<T &>()));

/* find out the base type fixture based on the first element (index 0) in a
 * tuple. initialize that base type with a tuple element (index I) */
template <typename T, int I>
using BaseTypeFixture = std::conditional_t<
    is_a_vector<typename std::tuple_element<0, T>::type>::value,
    VectorTypeFixture<typename std::tuple_element<I, T>::type>,
    MatrixTypeFixture<typename std::tuple_element<I, T>::type>>;

/* in case that the tuple contains exactly the same types (e.g. Vector<2,int>,
 * Vector<2,int>), the test fixture cannot inherit from both of these because
 * they are the same. the following code uses a little template trickery. it
 * lets the test fixture inherit from and "empty" base when types are the same*/
struct EmptyBase {};

template <typename T>
using SecondBaseTypeFixture =
    std::conditional_t<std::is_same_v<typename std::tuple_element<0, T>::type,
                                      typename std::tuple_element<1, T>::type>,
                       EmptyBase, BaseTypeFixture<T, 1>>;

/* test fixture for same type tests (e.g. vector<>vector). multiple
 * inheritance, because the types inside e.g. two vectors may be different.
 * therefore different type test values are needed. it is assumed that the
 * sizes match */
template <typename T>
class SameTypeCombinationsFixture : public BaseTypeFixture<T, 0>,
                                    public SecondBaseTypeFixture<T> {
  /* ...the test fixture needs to know which base type fixture to use for the
   * second test setup. this evaluates the index for that 2nd base (0 or 1) */
  static constexpr auto base_idx() {
    if constexpr (std::is_same_v<SecondBaseTypeFixture<T>, EmptyBase>) {
      return std::pair<std::size_t, std::size_t>(0, 0);
    } else {
      return std::pair<std::size_t, std::size_t>(0, 1);
    }
  }

  /* actual gtest setup */
 public:
  using BaseTypeFixture1 = BaseTypeFixture<T, base_idx().first>;
  using BaseTypeFixture2 = BaseTypeFixture<T, base_idx().second>;

  void SetUp() override {  // NOLINT
    BaseTypeFixture1::SetUp();
    BaseTypeFixture2::SetUp();
  }
  /* "alias" variables and functions for easier use in test functions */
  using T1 = typename std::tuple_element<base_idx().first, T>::type;
  using T2 = typename std::tuple_element<base_idx().second, T>::type;
  auto values() { return BaseTypeFixture1::values; }
  auto values2() { return BaseTypeFixture2::values; }
};

/********************************* INIT ************************************/

template <typename T>
class SameTypeCombinationsInitFixture : public SameTypeCombinationsFixture<T> {
 public:
  void SetUp() override {  // NOLINT
    SameTypeCombinationsFixture<T>::SetUp();
  }
};

TYPED_TEST_SUITE_P(SameTypeCombinationsInitFixture);

TYPED_TEST_P(SameTypeCombinationsInitFixture, ConstructorFromDifferentType) {
  /** arrange */
  typename TestFixture::T1 obj{this->values()};
  /* call the type casting constructor. no exception must be thrown */
  EXPECT_NO_THROW((typename TestFixture::T2{obj}));  // NOLINT "pre-assert"
  // for future reference: EXPECT_NO_THROW(([&] { T2 tmp{obj}; }()));
  /** action */
  typename TestFixture::T2 res{obj};
  /** assert */
  /* build comparison object by calling the constructor that takes a (possibly
   * nested) std array of a different type */
  typename TestFixture::T2 comp = this->values();
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(SameTypeCombinationsInitFixture,
             ConstructorFromDifferentTypeAssignment) {
  /** arrange */
  typename TestFixture::T1 obj{this->values()};
  /* call the type casting constructor. no exception must be thrown */
  EXPECT_NO_THROW((typename TestFixture::T2{obj}));  // NOLINT "pre-assert"
  // for future reference: EXPECT_NO_THROW(([&] { T2 tmp{obj}; }()));
  /** action */
  typename TestFixture::T2 res = obj;
  /** assert */
  /* build comparison object by calling the constructor that takes a (possibly
   * nested) std array of a different type */
  typename TestFixture::T2 comp = this->values();
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

REGISTER_TYPED_TEST_SUITE_P(SameTypeCombinationsInitFixture,
                            ConstructorFromDifferentType,
                            ConstructorFromDifferentTypeAssignment);

/********************************* MATH ************************************/

template <typename T>
class SameTypeCombinationsMathFixture : public SameTypeCombinationsFixture<T> {
 public:
  void SetUp() override {  // NOLINT
    SameTypeCombinationsFixture<T>::SetUp();
  }
};

TYPED_TEST_SUITE_P(SameTypeCombinationsMathFixture);

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  typename TestFixture::T1 obj3{this->values()};
  obj3[0] = static_cast<typename TestFixture::T1::value_type>(0);
  /** action */
  bool res1 = (obj1 == obj2);
  bool res2 = (obj1 == obj3);
  /** assert */
  /* for the same value type (e.g. both float, both int ..) we expect the
   * objects to contains the same values. for different value types (e.g.
   * float-int, int-float ..) we expect them to be different because of the
   * values in the test fixture setup*/
  if constexpr (std::is_same_v<typename TestFixture::T1::value_type,
                               typename TestFixture::T2::value_type>) {
    EXPECT_TRUE(res1);
  } else {
    EXPECT_FALSE(res1);
  }
  EXPECT_FALSE(res2);
}

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorNotEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  typename TestFixture::T1 obj3{this->values()};
  obj3[0] = static_cast<typename TestFixture::T1::value_type>(0);
  /** action */
  bool res1 = (obj1 != obj2);
  bool res2 = (obj1 != obj3);
  /** assert */
  /* for the same value type (e.g. both float, both int ..) we expect the
   * objects to contains the same values. for different value types (e.g.
   * float-int, int-float ..) we expect them to be different because of the
   * values in the test fixture setup*/
  if constexpr (std::is_same_v<typename TestFixture::T1::value_type,
                               typename TestFixture::T2::value_type>) {
    EXPECT_FALSE(res1);
  } else {
    EXPECT_TRUE(res1);
  }
  EXPECT_TRUE(res2);
}

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorPlus) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  typename TestFixture::T1 res = obj1 + obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return obj1[i] + obj2[i];
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorPlusEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  obj1 += obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values()[i] + obj2[i];
  });
  EXPECT_THAT(obj1, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorMinus) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  typename TestFixture::T1 res = obj1 - obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return obj1[i] - obj2[i];
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorMinusEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  obj1 -= obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values()[i] - obj2[i];
  });
  EXPECT_THAT(obj1, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorMultiply) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  typename TestFixture::T1 res = obj1 * obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return obj1[i] * obj2[i];
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorMultiplyEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  obj1 *= obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values()[i] * obj2[i];
  });
  EXPECT_THAT(obj1, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorDivide) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  typename TestFixture::T1 res = obj1 / obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return obj1[i] / obj2[i];
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(SameTypeCombinationsMathFixture, OperatorDivideEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  obj1 /= obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values()[i] / obj2[i];
  });
  EXPECT_THAT(obj1, ::testing::ContainerEq(comp));
}

REGISTER_TYPED_TEST_SUITE_P(SameTypeCombinationsMathFixture, OperatorEqual,
                            OperatorNotEqual, OperatorPlus, OperatorPlusEqual,
                            OperatorMinus, OperatorMinusEqual, OperatorMultiply,
                            OperatorMultiplyEqual, OperatorDivide,
                            OperatorDivideEqual);

#endif  // TESTS_SAME_TYPE_COMBINATIONS_H_