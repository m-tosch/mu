#include "gtest/gtest.h"
#include "matrix_type.h"
#include "mu/matrix.h"

/**
 * Instantiate this template class and template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
template class mu::Matrix<2, 2, float>;

/**
 * Instantiate the Matrix test suite
 */
using MatrixTypes =
    ::testing::Types<mu::Matrix<1, 1, float>, mu::Matrix<2, 1, float>,
                     mu::Matrix<1, 2, float>, mu::Matrix<2, 2, float>,
                     mu::Matrix<1, 1, int>, mu::Matrix<2, 1, int>,
                     mu::Matrix<1, 2, int>, mu::Matrix<2, 2, int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Matrix, MatrixTypeFixture, MatrixTypes);
