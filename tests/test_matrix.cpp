#include "gtest/gtest.h"
#include "matrix_type.h"
#include "mu/matrix.h"

using MatrixTypes = ::testing::Types<
    mu::Matrix<1, 1, float>, mu::Matrix<2, 1, float>, mu::Matrix<1, 2, float>,
    mu::Matrix<2, 2, float>, mu::Matrix<1, 3, float>, mu::Matrix<3, 1, float>,
    mu::Matrix<2, 3, float>, mu::Matrix<3, 2, float>, mu::Matrix<3, 3, float>,
    mu::Matrix<1, 1, int>, mu::Matrix<2, 1, int>, mu::Matrix<1, 2, int>,
    mu::Matrix<2, 2, int>, mu::Matrix<1, 3, int>, mu::Matrix<3, 1, int>,
    mu::Matrix<2, 3, int>, mu::Matrix<3, 2, int>, mu::Matrix<3, 3, int>>;

INSTANTIATE_TYPED_TEST_SUITE_P(Matrix, MatrixTypeFixture, MatrixTypes);
