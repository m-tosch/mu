#include <algorithm>
#include <tuple>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "matrix_type.h"
#include "mu/matrix.h"

/**
 * Instantiate these template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
/* addition */
template mu::Matrix<2, 2, float>& mu::Matrix<2, 2, float>::operator+=
    <float>(const float&);
template mu::Matrix<2, 2, float> mu::operator+
    <2, 2, float, float>(const mu::Matrix<2, 2, float>&, const float&);
template mu::Matrix<2, 2, float> mu::operator+
    <2, 2, float, float>(const float&, const mu::Matrix<2, 2, float>&);
/* subtraction */
template mu::Matrix<2, 2, float>& mu::Matrix<2, 2, float>::operator-=
    <float>(const float&);
template mu::Matrix<2, 2, float> mu::operator-
    <2, 2, float, float>(const mu::Matrix<2, 2, float>&, const float&);
/* multiplication */
template mu::Matrix<2, 2, float>& mu::Matrix<2, 2, float>::operator*=
    <float>(const float&);
template mu::Matrix<2, 2, float> mu::operator*
    <2, 2, float, float>(const mu::Matrix<2, 2, float>&, const float&);
template mu::Matrix<2, 2, float> mu::operator*
    <2, 2, float, float>(const float&, const mu::Matrix<2, 2, float>&);
/* division */
template mu::Matrix<2, 2, float>& mu::Matrix<2, 2, float>::operator/=
    <float>(const float&);
template mu::Matrix<2, 2, float> mu::operator/
    <2, 2, float, float>(const mu::Matrix<2, 2, float>&, const float&);

/**
 * Matrix <> Scalar test combinations
 */
using MatrixScalarCombinations =
    ::testing::Types</* Vector */
                     std::tuple<mu::Matrix<2, 2, int>, int>,
                     std::tuple<mu::Matrix<2, 2, float>, float>,
                     // different types
                     std::tuple<mu::Matrix<2, 2, int>, float>,
                     std::tuple<mu::Matrix<2, 2, float>, int>>;

template <typename T>
class MatrixScalarCombinationsFixture
    : public MatrixTypeFixture<typename std::tuple_element<0, T>::type> {
 public:
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;
  /* scalars used in multiple or all tests */
  static inline T2 zero = static_cast<T2>(0);
  static inline T2 one = static_cast<T2>(1);
};

TYPED_TEST_SUITE(MatrixScalarCombinationsFixture, MatrixScalarCombinations);

TYPED_TEST(MatrixScalarCombinationsFixture, OperatorPlus) {
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

TYPED_TEST(MatrixScalarCombinationsFixture, OperatorPlusEqual) {
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

TYPED_TEST(MatrixScalarCombinationsFixture, OperatorMinus) {
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

TYPED_TEST(MatrixScalarCombinationsFixture, OperatorMinusEqual) {
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

TYPED_TEST(MatrixScalarCombinationsFixture, OperatorMultiply) {
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

TYPED_TEST(MatrixScalarCombinationsFixture, OperatorMultiplyEqual) {
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

TYPED_TEST(MatrixScalarCombinationsFixture, OperatorDivide) {
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

TYPED_TEST(MatrixScalarCombinationsFixture, OperatorDivideEqual) {
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

TYPED_TEST(MatrixScalarCombinationsFixture, OperatorDivideByZeroAssert) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  /** action & assert */
  if constexpr (std::is_integral_v<typename TestFixture::T2>) {
    EXPECT_DEATH({ obj / TestFixture::zero; }, "");  // NOLINT
  }
}