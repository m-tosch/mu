#include "gtest/gtest.h"
#include "mu/vector.h"
#include "vector_type.h"

/**
 * Instantiate this template class and template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
template class mu::Vector<2, float>;
/* constructors */
template mu::Vector<2, float>::Vector(const mu::Vector<2, int> &);
/* functions */
template float mu::Vector<2, float>::length<float>() const;
/* operators */
template std::ostream &mu::operator<<<2, float>(std::ostream &,
                                                const mu::Vector<2, float> &);

/**
 * Instantiate the Vector test suite
 */
using VectorTypes = ::testing::Types<mu::Vector<2, float>, mu::Vector<2, int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector, VectorTypeFixture, VectorTypes);
