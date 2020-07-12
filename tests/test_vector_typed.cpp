#include "gtest/gtest.h"
#include "vector.h"

template <typename T>
class VectorFixture : public ::testing::Test {
 public:
  virtual void SetUp() {
    value_[0] = 1.0F;
    value_[1] = 2.0F;
  }
  typedef mu::Vector<2, T> VecType;
  VecType value_;
};

using VectorTypes = ::testing::Types<char, int, float>;
TYPED_TEST_SUITE(VectorFixture, VectorTypes);

TYPED_TEST(VectorFixture, ConstructorDefault) {
  typename VectorFixture::VecType vvv;
  /** arrange */
  bool c = std::is_default_constructible<vvv>::value;
  /** assert */
  EXPECT_TRUE(c);
}

TYPED_TEST(VectorFixture, ConstructorSingleValueInit) {
  /** arrange */
  mu::Vector<2, float> v{2.0F};
  /** assert */
  EXPECT_FLOAT_EQ(v[0], 2.0F);
  EXPECT_FLOAT_EQ(v[1], 2.0F);
}
