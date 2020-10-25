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
template mu::Vector<2, float>& mu::Vector<2, float>::operator+=
    <float>(const float&);
template mu::Vector<2, float> mu::operator+
    <2, float, float>(const mu::Vector<2, float>&, const float&);
template mu::Vector<2, float> mu::operator+
    <2, float, float>(const float&, const mu::Vector<2, float>&);

/**
 * Vector <> Scalar test combinations
 */
using VectorScalarCombinations =
    ::testing::Types</* Vector */
                     std::tuple<mu::Vector<2, int>, int>,
                     std::tuple<mu::Vector<2, float>, float>,
                     /* Vector2D */
                     std::tuple<mu::Vector2D<int>, int>,
                     std::tuple<mu::Vector2D<float>, float>,
                     /* Vector3D */
                     std::tuple<mu::Vector3D<int>, int>,
                     std::tuple<mu::Vector3D<float>, float>>;

template <typename T>
class VectorScalarCombinationsFixture
    : public VectorTypeFixture<typename std::tuple_element<0, T>::type> {
 public:
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;
};

TYPED_TEST_SUITE(VectorScalarCombinationsFixture, VectorScalarCombinations);

TYPED_TEST(VectorScalarCombinationsFixture, OperatorPlus1) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = static_cast<typename TestFixture::T2>(1);
  /** action */
  typename TestFixture::T1 res = obj + scalar;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return obj[i] + scalar;
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST(VectorScalarCombinationsFixture, OperatorPlus2) {
  /** arrange */
  auto scalar = static_cast<typename TestFixture::T2>(1);
  typename TestFixture::T1 obj{this->values};
  /** action */
  typename TestFixture::T1 res = scalar + obj;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return scalar + obj[i];
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST(VectorScalarCombinationsFixture, OperatorPlusEqual) {
  /** arrange */
  typename TestFixture::T1 obj{this->values};
  auto scalar = static_cast<typename TestFixture::T2>(1);
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
