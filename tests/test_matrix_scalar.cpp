#include <tuple>

#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "scalar_combinations.h"

using MatrixScalarCombinationTypes =
    ::testing::Types</* Vector */
                     std::tuple<mu::Matrix<2, 2, int>, int>,
                     std::tuple<mu::Matrix<2, 2, float>, float>,
                     // different types
                     std::tuple<mu::Matrix<2, 2, int>, float>,
                     std::tuple<mu::Matrix<2, 2, float>, int>>;

INSTANTIATE_TYPED_TEST_SUITE_P(Matrix, ScalarCombinationsFixture,
                               MatrixScalarCombinationTypes);