#include <tuple>
#include <utility>

#include "gtest/gtest.h"
#include "vector.h"

template <typename T>
class VectorFixture : public ::testing::Test {
 public:
  virtual void SetUp() {}
  typedef typename std::tuple_element<0, T>::type T1;
  typedef typename std::tuple_element<1, T>::type T2;
};

using VectorTypes =
    ::testing::Types<std::tuple<mu::Vector<2, float>, mu::Vector<2, float>>>;
TYPED_TEST_SUITE(VectorFixture, VectorTypes);

TYPED_TEST(VectorFixture, ConstructorDefault) {
  typedef typename TestFixture::T1 Ftype;
  /** arrange */
  bool c = std::is_default_constructible<Ftype>::value;
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
