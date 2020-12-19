#include <tuple>

#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "same_type_combinations.h"

/**
 * explicit instantiations
 *
 * note: +=, -=, *= and /= do not have to be explicitly instantiated
 */
/* addition */
template mu::Matrix<2, 2, float> mu::operator+
    <2, 2, float, int>(const mu::Matrix<2, 2, float> &,
                       const mu::Matrix<2, 2, int> &);
/* subtraction */
template mu::Matrix<2, 2, float> mu::operator-
    <2, 2, float, int>(const mu::Matrix<2, 2, float> &,
                       const mu::Matrix<2, 2, int> &);
/* multiplication */
template mu::Matrix<2, 2, float> mu::operator*
    <2, 2, float, int>(const mu::Matrix<2, 2, float> &,
                       const mu::Matrix<2, 2, int> &);
/* division */
template mu::Matrix<2, 2, float> mu::operator/
    <2, 2, float, int>(const mu::Matrix<2, 2, float> &,
                       const mu::Matrix<2, 2, int> &);
/* equality (this operator is also called by gtest. probably ContainerEq...) */
template bool mu::Matrix<2, 2, float>::operator==
    <int>(const mu::Matrix<2, 2, int> &) const;
/* inequality */
template bool mu::Matrix<2, 2, float>::operator!=
    <int>(const mu::Matrix<2, 2, int> &) const;

/**
 * Matrix <> Matrix test combinations
 */
using MatrixTypeCombinationsMath = ::testing::Types<
    /* Matrix */
    std::tuple<mu::Matrix<2, 2, float>, mu::Matrix<2, 2, int>>>;

INSTANTIATE_TYPED_TEST_SUITE_P(Matrix, SameTypeCombinationsFixture,
                               MatrixTypeCombinationsMath);