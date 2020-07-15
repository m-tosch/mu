#include <tuple>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "vector.h"


template <typename T>
class VectorFixture : public ::testing::Test {
 public:
  virtual void SetUp() {}
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;

  std::array<typename T1::value_type, T1().Size()> values;
};

using VectorTypes =
    ::testing::Types<std::tuple<mu::Vector<2, float>, mu::Vector<2, float>>>;
TYPED_TEST_SUITE(VectorFixture, VectorTypes);

TYPED_TEST(VectorFixture, ConstructorDefault) {
  /** arrange */
  bool c = std::is_default_constructible<typename TestFixture::T1>::value;
  /** assert */
  EXPECT_TRUE(c);
}

TYPED_TEST(VectorFixture, ConstructorSingleValueInit) {
  /** arrange */
  typename TestFixture::T1 v{2.0F};
  /** assert */
  EXPECT_FLOAT_EQ(v[0], 2.0F);
  EXPECT_FLOAT_EQ(v[1], 2.0F);
}

TYPED_TEST(VectorFixture, plus) {
  /** arrange */
  typename TestFixture::T1 obj1{2.0F};
  typename TestFixture::T2 obj2{2.0F};
  /** action */
  typename TestFixture::T1 res = obj1 + obj2;
  /** assert */
  EXPECT_FLOAT_EQ(res[0], obj1[0] + obj2[0]);
  EXPECT_FLOAT_EQ(res[1], obj1[1] + obj2[1]);
}
