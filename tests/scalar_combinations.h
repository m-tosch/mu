#ifndef TESTS_SCALAR_COMBINATIONS_H_
#define TESTS_SCALAR_COMBINATIONS_H_

#include <algorithm>
#include <tuple>
#include <type_traits>

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

template <typename T>
class ScalarCombinationsFixture
    : public std::conditional_t<
          is_a_vector<typename std::tuple_element<0, T>::type>::value,
          VectorTypeFixture<typename std::tuple_element<0, T>::type>,
          MatrixTypeFixture<typename std::tuple_element<0, T>::type>> {
 public:
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;
  static inline T2 zero = static_cast<T2>(0);
  static inline T2 one = static_cast<T2>(1);
};

TYPED_TEST_SUITE_P(ScalarCombinationsFixture);

TYPED_TEST_P(ScalarCombinationsFixture, OperatorPlus) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = TestFixture::one;
  /** action test both ways to do addition */
  typename TestFixture::T1 res1 = scalar + obj;
  typename TestFixture::T1 res2 = obj + scalar;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return obj[i] + scalar;
  });
  EXPECT_THAT(res1, ::testing::ContainerEq(comp));
  EXPECT_THAT(res2, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(ScalarCombinationsFixture, OperatorPlusEqual) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = TestFixture::one;
  /** action */
  obj += scalar;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i] + scalar;
  });
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(ScalarCombinationsFixture, OperatorMinus) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = TestFixture::one;
  /** action */
  typename TestFixture::T1 res = obj - scalar;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return obj[i] - scalar;
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(ScalarCombinationsFixture, OperatorMinusEqual) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = TestFixture::one;
  /** action */
  obj -= scalar;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i] - scalar;
  });
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(ScalarCombinationsFixture, OperatorMultiply) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = TestFixture::one;
  /** action test both ways to do addition */
  typename TestFixture::T1 res1 = scalar * obj;
  typename TestFixture::T1 res2 = obj * scalar;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return obj[i] * scalar;
  });
  EXPECT_THAT(res1, ::testing::ContainerEq(comp));
  EXPECT_THAT(res2, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(ScalarCombinationsFixture, OperatorMultiplyEqual) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = TestFixture::one;
  /** action */
  obj *= scalar;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i] * scalar;
  });
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(ScalarCombinationsFixture, OperatorDivide) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = TestFixture::one;
  /** action */
  typename TestFixture::T1 res = obj / scalar;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return obj[i] / scalar;
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(ScalarCombinationsFixture, OperatorDivideEqual) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = TestFixture::one;
  /** action */
  obj /= scalar;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i] / scalar;
  });
  EXPECT_THAT(obj, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(ScalarCombinationsFixture, OperatorDivideByZeroAssert) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  /** action & assert */
  if constexpr (std::is_integral_v<typename TestFixture::T2>) {
    EXPECT_DEATH({ obj / TestFixture::zero; }, "");  // NOLINT
  }
}

REGISTER_TYPED_TEST_SUITE_P(ScalarCombinationsFixture, OperatorPlus,
                            OperatorPlusEqual, OperatorMinus,
                            OperatorMinusEqual, OperatorMultiply,
                            OperatorMultiplyEqual, OperatorDivide,
                            OperatorDivideEqual, OperatorDivideByZeroAssert);

#endif  // TESTS_SCALAR_COMBINATIONS_H_