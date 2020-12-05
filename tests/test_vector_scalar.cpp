#include <algorithm>
#include <tuple>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "mu/vector3d.h"
#include "vector_type.h"

/**
 * Instantiate these template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
/* addition */
template mu::Vector<2, float>& mu::Vector<2, float>::operator+=
    <float>(const float&);
template mu::Vector<2, float> mu::operator+
    <2, float, float>(const mu::Vector<2, float>&, const float&);
template mu::Vector<2, float> mu::operator+
    <2, float, float>(const float&, const mu::Vector<2, float>&);
/* subtraction */
template mu::Vector<2, float>& mu::Vector<2, float>::operator-=
    <float>(const float&);
template mu::Vector<2, float> mu::operator-
    <2, float, float>(const mu::Vector<2, float>&, const float&);
/* multiplication */
template mu::Vector<2, float>& mu::Vector<2, float>::operator*=
    <float>(const float&);
template mu::Vector<2, float> mu::operator*
    <2, float, float>(const mu::Vector<2, float>&, const float&);
template mu::Vector<2, float> mu::operator*
    <2, float, float>(const float&, const mu::Vector<2, float>&);
/* division */
template mu::Vector<2, float>& mu::Vector<2, float>::operator/=
    <float>(const float&);
template mu::Vector<2, float> mu::operator/
    <2, float, float>(const mu::Vector<2, float>&, const float&);

/**
 * Vector <> Scalar test combinations
 */
using VectorScalarCombinations =
    ::testing::Types</* Vector */
                     std::tuple<mu::Vector<2, int>, int>,
                     std::tuple<mu::Vector<2, float>, float>,
                     // different types
                     std::tuple<mu::Vector<2, int>, float>,
                     std::tuple<mu::Vector<2, float>, int>,
                     /* Vector2D */
                     std::tuple<mu::Vector2D<int>, int>,
                     std::tuple<mu::Vector2D<float>, float>,
                     // different types
                     std::tuple<mu::Vector2D<int>, float>,
                     std::tuple<mu::Vector2D<float>, int>,
                     /* Vector3D */
                     std::tuple<mu::Vector3D<int>, int>,
                     std::tuple<mu::Vector3D<float>, float>,
                     // different types
                     std::tuple<mu::Vector3D<int>, float>,
                     std::tuple<mu::Vector3D<float>, int>>;

template <typename T>
class VectorScalarCombinationsFixture
    : public VectorTypeFixture<typename std::tuple_element<0, T>::type> {
 public:
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;
  /* scalars used in multiple or all tests */
  static inline T2 zero = static_cast<T2>(0);
  static inline T2 one = static_cast<T2>(1);
};

TYPED_TEST_SUITE(VectorScalarCombinationsFixture, VectorScalarCombinations);

TYPED_TEST(VectorScalarCombinationsFixture, OperatorPlus) {
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

TYPED_TEST(VectorScalarCombinationsFixture, OperatorPlusEqual) {
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

TYPED_TEST(VectorScalarCombinationsFixture, OperatorMinus) {
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

TYPED_TEST(VectorScalarCombinationsFixture, OperatorMinusEqual) {
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

TYPED_TEST(VectorScalarCombinationsFixture, OperatorMultiply) {
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

TYPED_TEST(VectorScalarCombinationsFixture, OperatorMultiplyEqual) {
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

TYPED_TEST(VectorScalarCombinationsFixture, OperatorDivide) {
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

TYPED_TEST(VectorScalarCombinationsFixture, OperatorDivideEqual) {
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

TYPED_TEST(VectorScalarCombinationsFixture, OperatorDivideByZeroAssert) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  /** action & assert */
  if constexpr (std::is_integral_v<typename TestFixture::T2>) {
    EXPECT_DEATH({ obj / TestFixture::zero; }, "");  // NOLINT
  }
}