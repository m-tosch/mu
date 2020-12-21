#include "gtest/gtest.h"
#include "mu/vector.h"
#include "vector_type.h"

using VectorTypes = ::testing::Types<mu::Vector<1, float>, mu::Vector<2, float>,
                                     mu::Vector<3, float>, mu::Vector<1, int>,
                                     mu::Vector<2, int>, mu::Vector<3, int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector, VectorTypeFixture, VectorTypes);
