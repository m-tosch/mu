#include <algorithm>
#include <tuple>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "mu/vector3d.h"
#include "same_type_combinations.h"
#include "vector_type.h"

/********************************* INIT ************************************/

/**
 * explicit instantiations
 */
/* constructor (construct-from-different-typed-vector) */
template mu::Vector<2, float>::Vector(const mu::Vector<2, int> &);

/**
 * Vector <> Vector test combinations
 *
 * in each pair the two Vectors are of a different arithmetic type
 */
using VectorTypeCombinationsInit = ::testing::Types<
    /* Vector */
    std::tuple<mu::Vector<2, float>, mu::Vector<2, int>>,
    std::tuple<mu::Vector<2, int>, mu::Vector<2, float>>,
    /* Vector2D */
    std::tuple<mu::Vector<2, float>, mu::Vector2D<int>>,
    std::tuple<mu::Vector2D<float>, mu::Vector<2, int>>,
    std::tuple<mu::Vector2D<float>, mu::Vector2D<int>>,
    // both ways
    std::tuple<mu::Vector<2, int>, mu::Vector2D<float>>,
    std::tuple<mu::Vector2D<int>, mu::Vector<2, float>>,
    std::tuple<mu::Vector2D<int>, mu::Vector2D<float>>,
    /* Vector3D */
    std::tuple<mu::Vector<3, float>, mu::Vector3D<int>>,
    std::tuple<mu::Vector3D<float>, mu::Vector<3, int>>,
    std::tuple<mu::Vector3D<float>, mu::Vector3D<int>>,
    // both ways
    std::tuple<mu::Vector<3, int>, mu::Vector3D<float>>,
    std::tuple<mu::Vector3D<int>, mu::Vector<3, float>>,
    std::tuple<mu::Vector3D<int>, mu::Vector3D<float>>>;

INSTANTIATE_TYPED_TEST_SUITE_P(Vector, SameTypeCombinationsInitFixture,
                               VectorTypeCombinationsInit);

/****************************** MATH ***************************************/

/**
 * explicit instantiations
 *
 * note: +=, -=, *= and /= do not have to be explicitly instantiated
 */
/* addition */
template mu::Vector<2, float> mu::operator+
    <2, float, int>(const mu::Vector<2, float> &, const mu::Vector<2, int> &);
/* subtraction */
template mu::Vector<2, float> mu::operator-
    <2, float, int>(const mu::Vector<2, float> &, const mu::Vector<2, int> &);
/* multiplication */
template mu::Vector<2, float> mu::operator*
    <2, float, int>(const mu::Vector<2, float> &, const mu::Vector<2, int> &);
/* division */
template mu::Vector<2, float> mu::operator/
    <2, float, int>(const mu::Vector<2, float> &, const mu::Vector<2, int> &);
/* equality (this operator is also called by gtest. probably ContainerEq...) */
template bool mu::Vector<2, float>::operator==
    <int>(const mu::Vector<2, int> &) const;
/* inequality */
template bool mu::Vector<2, float>::operator!=
    <int>(const mu::Vector<2, int> &) const;

using VectorTypeCombinationsMath = ::testing::Types<
    /* Vector */
    std::tuple<mu::Vector<2, float>, mu::Vector<2, float>>,
    // different types (both ways)
    std::tuple<mu::Vector<2, float>, mu::Vector<2, int>>,
    std::tuple<mu::Vector<2, int>, mu::Vector<2, float>>,
    /* Vector2D */
    std::tuple<mu::Vector<2, float>, mu::Vector2D<float>>,
    std::tuple<mu::Vector2D<float>, mu::Vector<2, float>>,
    std::tuple<mu::Vector2D<float>, mu::Vector2D<float>>,
    // different types (both ways)
    std::tuple<mu::Vector<2, float>, mu::Vector2D<int>>,
    std::tuple<mu::Vector2D<float>, mu::Vector<2, int>>,
    std::tuple<mu::Vector2D<float>, mu::Vector2D<int>>,
    std::tuple<mu::Vector<2, int>, mu::Vector2D<float>>,
    std::tuple<mu::Vector2D<int>, mu::Vector<2, float>>,
    std::tuple<mu::Vector2D<int>, mu::Vector2D<float>>,
    /* Vector3D */
    std::tuple<mu::Vector<3, float>, mu::Vector3D<float>>,
    std::tuple<mu::Vector3D<float>, mu::Vector<3, float>>,
    std::tuple<mu::Vector3D<float>, mu::Vector3D<float>>,
    // different types (both ways)
    std::tuple<mu::Vector<3, float>, mu::Vector3D<int>>,
    std::tuple<mu::Vector3D<float>, mu::Vector<3, int>>,
    std::tuple<mu::Vector3D<float>, mu::Vector3D<int>>,
    std::tuple<mu::Vector<3, int>, mu::Vector3D<float>>,
    std::tuple<mu::Vector3D<int>, mu::Vector<3, float>>,
    std::tuple<mu::Vector3D<int>, mu::Vector3D<float>>>;

INSTANTIATE_TYPED_TEST_SUITE_P(Vector, SameTypeCombinationsMathFixture,
                               VectorTypeCombinationsMath);

/************************* Vector specific tests ***************************/

/* convenience functions */
/* these functions should take a combination of Vectors, so they're here.
 * functions that take e.g a single Vector as argument are elsewhere */
template int mu::dot<int, 2, float, 2, float>(const mu::Vector<2, float> &,
                                              const mu::Vector<2, float> &);

template <typename T>
class VectorCombinationsMathFixture : public SameTypeCombinationsFixture<T> {
 public:
  void SetUp() override {  // NOLINT
    SameTypeCombinationsFixture<T>::SetUp();
  }
};

TYPED_TEST_SUITE(VectorCombinationsMathFixture, VectorTypeCombinationsMath);

TYPED_TEST(VectorCombinationsMathFixture, MemberFuncDot) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  typename TestFixture::T1::value_type res{};
  if constexpr (std::is_same_v<typename TestFixture::T1,
                               typename TestFixture::T2>) {
    res = obj1.template dot(obj2);
  } else {
    res = obj1.template dot<typename TestFixture::T1::value_type>(obj2);
  }
  /** assert */
  typename TestFixture::T1::value_type comp =
      std::inner_product(obj1.begin(), obj1.end(), obj2.begin(),
                         static_cast<typename TestFixture::T1::value_type>(0));
  EXPECT_FLOAT_EQ(res, comp);
}

/************************* convenience functions ***************************/

TYPED_TEST(VectorCombinationsMathFixture, UtilityFuncDot) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  typename TestFixture::T1::value_type res{};
  if constexpr (std::is_same_v<typename TestFixture::T1,
                               typename TestFixture::T2>) {
    res = mu::dot(obj1, obj2);
  } else {
    res = mu::dot<typename TestFixture::T1::value_type>(obj1, obj2);
  }
  /** assert */
  typename TestFixture::T1::value_type comp =
      std::inner_product(obj1.begin(), obj1.end(), obj2.begin(),
                         static_cast<typename TestFixture::T1::value_type>(0));
  EXPECT_FLOAT_EQ(res, comp);
}
