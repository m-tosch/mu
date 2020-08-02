
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <tuple>

#include "mu/vector.h"
#include "mu/vector2d.h"
#include "test_vector_type.h"

using VectorTypeCombinations =
    ::testing::Types<std::tuple<mu::Vector<2, float>, mu::Vector<2, float>>
                     /*, std::tuple<mu::Vector<2, float>, mu::Vector2D<float>>,
                     std::tuple<mu::Vector2D<float>, mu::Vector<2, float>>,
                     std::tuple<mu::Vector2D<float>, mu::Vector2D<float>>*/>;

template <typename T>
class VectorCombinationsFixture
    : public VectorTypeFixture<typename std::tuple_element<0, T>::type> {
 public:
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;
};

TYPED_TEST_SUITE(VectorCombinationsFixture, VectorTypeCombinations);

TYPED_TEST(VectorCombinationsFixture, OperatorAddition) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values};
  /** action */
  typename TestFixture::T1 res = obj1 + obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&obj1, &obj2, i = 0]() mutable {
    return obj1[i] + obj2[i++];
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST(VectorCombinationsFixture, OperatorSubtraction) {
  /** arrange */
  typename TestFixture::T1 obj1{this->values};
  typename TestFixture::T2 obj2{this->values};
  /** action */
  typename TestFixture::T1 res = obj1 - obj2;
  /** assert */
  typename TestFixture::T1 comp;
  std::generate(comp.begin(), comp.end(), [&obj1, &obj2, i = 0]() mutable {
    return obj1[i] - obj2[i++];
  });
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}
