#include <algorithm>
#include <tuple>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "mu/vector3d.h"
#include "vector_type.h"

using VectorTypeCombinations =
    ::testing::Types<std::tuple<mu::Vector<2, float>, mu::Vector<2, float>>,
                     /* Vector2D */
                     std::tuple<mu::Vector<2, float>, mu::Vector2D<float>>,
                     std::tuple<mu::Vector2D<float>, mu::Vector<2, float>>,
                     std::tuple<mu::Vector2D<float>, mu::Vector2D<float>>,
                     /* Vector3D */
                     std::tuple<mu::Vector<3, float>, mu::Vector3D<float>>,
                     std::tuple<mu::Vector3D<float>, mu::Vector<3, float>>,
                     std::tuple<mu::Vector3D<float>, mu::Vector3D<float>>>;

template <typename T>
class VectorCombinationsFixture
    : public VectorTypeFixture<typename std::tuple_element<0, T>::type> {
 public:
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;
};

TYPED_TEST_SUITE(VectorCombinationsFixture, VectorTypeCombinations);

TYPED_TEST(VectorCombinationsFixture, OperatorPlus) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values};
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

TYPED_TEST(VectorCombinationsFixture, OperatorPlusEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values};
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

TYPED_TEST(VectorCombinationsFixture, OperatorMinus) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values};
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

TYPED_TEST(VectorCombinationsFixture, OperatorMinusEqual) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values};
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

TYPED_TEST(VectorCombinationsFixture, MemberFuncDot) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values};
  /** action */
  typename TestFixture::T1::value_type res = obj1.dot(obj2);
  /** assert */
  EXPECT_EQ(res, std::inner_product(obj1.begin(), obj1.end(), obj2.begin(), 0));
}

TYPED_TEST(VectorCombinationsFixture, UtilityFuncDot) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values};
  /** action */
  typename TestFixture::T1::value_type res = dot(obj1, obj2);
  /** assert */
  EXPECT_EQ(res, std::inner_product(obj1.begin(), obj1.end(), obj2.begin(), 0));
}
