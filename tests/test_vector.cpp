#include "gtest/gtest.h"
#include "test_vector_type.h"
#include "vector.h"

/**
 * Instantiate this template class explicitly so that all functions
 * are generated and thus, the coverage report is complete.
 */
template class mu::Vector<2, float>;

/**
 * Instantiate the Vector test suite
 */
using VectorTypes = ::testing::Types<mu::Vector<2, float>, mu::Vector<2, int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector, VectorTypeFixture, VectorTypes);

/******************************************************************************/

TEST(Vector, OperatorPlus) {
  /** arrange */
  mu::Vector<2, float> v1{1.0F};
  mu::Vector<2, float> v2{1.0F};
  /** action */
  mu::Vector<2, float> res = v1 + v2;
  /** assert */
  EXPECT_FLOAT_EQ(res[0], v1[0] + v2[1]);
  EXPECT_FLOAT_EQ(res[1], v1[0] + v2[1]);
}

TEST(Vector, OperatorMinus) {
  /** arrange */
  mu::Vector<2, float> v1{1.0F};
  mu::Vector<2, float> v2{1.0F};
  /** action */
  mu::Vector<2, float> res = v1 - v2;
  /** assert */
  EXPECT_FLOAT_EQ(res[0], v1[0] - v2[1]);
  EXPECT_FLOAT_EQ(res[1], v1[0] - v2[1]);
}
