#include "gtest/gtest.h"
#include "test_vector_type.h"
#include "vector2d.h"

/**
 * Instantiate this template class explicitly so that all functions
 * are generated and thus, the coverage report is complete.
 */
template class mu::Vector2D<float>;

/**
 * Instantiate the Vector test suite
 */
using Vector2DTypes = ::testing::Types<mu::Vector2D<float>, mu::Vector2D<int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector2D, VectorTypeFixture, Vector2DTypes);

/******************************************************************************/
