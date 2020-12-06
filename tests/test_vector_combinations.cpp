#include <algorithm>
#include <tuple>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "mu/vector3d.h"
#include "vector_type.h"

/**************************** INITIALIZATION **********************************/

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
    std::tuple<mu::Vector<2, int>, mu::Vector<2, float>>,
    std::tuple<mu::Vector<2, int>, mu::Vector2D<float>>,
    std::tuple<mu::Vector<3, int>, mu::Vector3D<float>>,
    /* Vector2D */
    std::tuple<mu::Vector2D<int>, mu::Vector2D<float>>,
    std::tuple<mu::Vector2D<int>, mu::Vector<2, float>>,
    /* Vector3D */
    std::tuple<mu::Vector3D<int>, mu::Vector3D<float>>,
    std::tuple<mu::Vector3D<int>, mu::Vector<3, float>>>;

template <typename T>
class VectorCombinationsInitFixture
    : public VectorTypeFixture<typename std::tuple_element<0, T>::type> {
 public:
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;
};

TYPED_TEST_SUITE(VectorCombinationsInitFixture, VectorTypeCombinationsInit);

TYPED_TEST(VectorCombinationsInitFixture, ConstructorFromDifferentTypeVector) {
  /* call the type casting constructor in Vector. no exception must be thrown */
  using T1 = typename TestFixture::T1;
  using T2 = typename TestFixture::T2;
  using T1_v = typename TestFixture::T1::value_type;
  using T2_v = typename TestFixture::T2::value_type;
  /** arrange */
  T1 obj{this->values};
  EXPECT_NO_THROW((T2{obj}));  // NOLINT "pre-assert"
  // for future reference: EXPECT_NO_THROW(([&] { T2 tmp{obj}; }()));
  /** action */
  T2 res{obj};
  /* build comparison array. mimic what the constructor in Vector does */
  static T2 dummy;
  std::array<typename T2::value_type, dummy.size()> comp;
  std::transform(this->values.begin(), this->values.end(), comp.begin(),
                 [](T1_v i) { return static_cast<T2_v>(i); });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(T2{comp}));
}

/******************************* MATH *****************************************/

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

/* convenience functions */
/* these functions should take a combination of Vectors, so they're here.
 * functions that take e.g a single Vector as argument are elsewhere */
template float mu::dot<2, float, int>(const mu::Vector<2, float> &,
                                      const mu::Vector<2, int> &);

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

template <typename T>
class VectorCombinationsMathFixture
    : public VectorTypeFixture<typename std::tuple_element<0, T>::type> {
 public:
  /* 0: first Vector type (e.g. mu::Vector<2,float>)
   * 1: second Vector type (e.g. mu::Vector2D<float>) */
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;

  void SetUp() override {  // NOLINT
    /* explicitly call base class setup with first tuple type */
    VectorTypeFixture<T1>::SetUp();
    /* build a second values list (just like in the parent fixture) with the
     * type of the second tuple element. this type may be different! */
    auto start = static_cast<typename T2::value_type>(0);
    auto incr = static_cast<typename T2::value_type>(1);
    std::generate(values2.begin(), values2.end(),
                  [&start, &incr]() { return start += incr; });
  }
  std::array<typename T2::value_type, VectorTypeFixture<T2>::dummy.size()>
      values2;
};

TYPED_TEST_SUITE(VectorCombinationsMathFixture, VectorTypeCombinationsMath);

TYPED_TEST(VectorCombinationsMathFixture, OperatorEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
  typename TestFixture::T1 obj3{this->values};
  obj3[0] = 0;
  /** action & assert */
  EXPECT_TRUE(obj1 == obj2);
  EXPECT_FALSE(obj1 == obj3);
}

TYPED_TEST(VectorCombinationsMathFixture, OperatorNotEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
  typename TestFixture::T1 obj3{this->values};
  obj3[0] = 0;
  /** action & assert */
  EXPECT_FALSE(obj1 != obj2);
  EXPECT_TRUE(obj1 != obj3);
}

TYPED_TEST(VectorCombinationsMathFixture, OperatorPlus) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
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

TYPED_TEST(VectorCombinationsMathFixture, OperatorPlusEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
  /** action */
  obj1 += obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i] + obj2[i];
  });
  EXPECT_THAT(obj1, ::testing::ContainerEq(comp));
}

TYPED_TEST(VectorCombinationsMathFixture, OperatorMinus) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
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

TYPED_TEST(VectorCombinationsMathFixture, OperatorMinusEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
  /** action */
  obj1 -= obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i] - obj2[i];
  });
  EXPECT_THAT(obj1, ::testing::ContainerEq(comp));
}

TYPED_TEST(VectorCombinationsMathFixture, OperatorMultiply) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
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

TYPED_TEST(VectorCombinationsMathFixture, OperatorMultiplyEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
  /** action */
  obj1 *= obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i] * obj2[i];
  });
  EXPECT_THAT(obj1, ::testing::ContainerEq(comp));
}

TYPED_TEST(VectorCombinationsMathFixture, OperatorDivide) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
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

TYPED_TEST(VectorCombinationsMathFixture, OperatorDivideEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
  /** action */
  obj1 /= obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i] / obj2[i];
  });
  EXPECT_THAT(obj1, ::testing::ContainerEq(comp));
}

TYPED_TEST(VectorCombinationsMathFixture, MemberFuncDot) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
  /** action */
  typename TestFixture::T1::value_type res = obj1.dot(obj2);
  /** assert */
  EXPECT_EQ(res, std::inner_product(obj1.begin(), obj1.end(), obj2.begin(), 0));
}

/************************** convenience functions *****************************/

TYPED_TEST(VectorCombinationsMathFixture, UtilityFuncDot) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values2};
  /** action */
  typename TestFixture::T1::value_type res = dot(obj1, obj2);
  /** assert */
  EXPECT_EQ(res, std::inner_product(obj1.begin(), obj1.end(), obj2.begin(), 0));
}
