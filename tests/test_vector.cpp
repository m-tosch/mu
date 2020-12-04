#include "gtest/gtest.h"
#include "mu/vector.h"
#include "vector_type.h"

/**
 * Instantiate this template class and template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
template class mu::Vector<2, float>;
/* functions */
template float mu::Vector<2, float>::length<float>() const;
/* operators */
template std::ostream &mu::operator<<<2, float>(std::ostream &,
                                                const mu::Vector<2, float> &);
/* convenience functions */
/* these functions take a single Vector as argument, so they're here. functions
 * that take e.g a combination of Vectors as argument are elsewhere */
template float mu::min(const mu::Vector<2, float> &);
template float mu::max(const mu::Vector<2, float> &);
template float mu::sum(const mu::Vector<2, float> &);
template void mu::flip(mu::Vector<2, float> &);
template mu::Vector<2, float> mu::flipped(const mu::Vector<2, float> &);

/**
 * Instantiate the Vector test suite
 */
using VectorTypes = ::testing::Types<mu::Vector<2, float>, mu::Vector<2, int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector, VectorTypeFixture, VectorTypes);
