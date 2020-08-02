#include <gtest/gtest.h>

#include "mu/vector.h"
#include "test_vector_type.h"

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
