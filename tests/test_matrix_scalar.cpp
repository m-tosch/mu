#include <algorithm>
#include <tuple>

#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "scalar_combinations.h"

/**
 * Instantiate these template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
/* addition */
template mu::Matrix<2, 2, float>& mu::Matrix<2, 2, float>::operator+=
    <float>(const float&);
template mu::Matrix<2, 2, float> mu::operator+
    <2, 2, float, float>(const mu::Matrix<2, 2, float>&, const float&);
template mu::Matrix<2, 2, float> mu::operator+
    <2, 2, float, float>(const float&, const mu::Matrix<2, 2, float>&);
/* subtraction */
template mu::Matrix<2, 2, float>& mu::Matrix<2, 2, float>::operator-=
    <float>(const float&);
template mu::Matrix<2, 2, float> mu::operator-
    <2, 2, float, float>(const mu::Matrix<2, 2, float>&, const float&);
/* multiplication */
template mu::Matrix<2, 2, float>& mu::Matrix<2, 2, float>::operator*=
    <float>(const float&);
template mu::Matrix<2, 2, float> mu::operator*
    <2, 2, float, float>(const mu::Matrix<2, 2, float>&, const float&);
template mu::Matrix<2, 2, float> mu::operator*
    <2, 2, float, float>(const float&, const mu::Matrix<2, 2, float>&);
/* division */
template mu::Matrix<2, 2, float>& mu::Matrix<2, 2, float>::operator/=
    <float>(const float&);
template mu::Matrix<2, 2, float> mu::operator/
    <2, 2, float, float>(const mu::Matrix<2, 2, float>&, const float&);

/**
 * Matrix <> Scalar test combinations
 */
using MatrixScalarCombinationTypes =
    ::testing::Types</* Vector */
                     std::tuple<mu::Matrix<2, 2, int>, int>,
                     std::tuple<mu::Matrix<2, 2, float>, float>,
                     // different types
                     std::tuple<mu::Matrix<2, 2, int>, float>,
                     std::tuple<mu::Matrix<2, 2, float>, int>>;

INSTANTIATE_TYPED_TEST_SUITE_P(Matrix, ScalarCombinationsFixture,
                               MatrixScalarCombinationTypes);