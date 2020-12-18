#include <tuple>

#include "gtest/gtest.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "mu/vector3d.h"
#include "scalar_combinations.h"

/**
 * Instantiate these template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
/* addition */
template mu::Vector<2, float>& mu::Vector<2, float>::operator+=
    <float>(const float&);
template mu::Vector<2, float> mu::operator+
    <2, float, float>(const mu::Vector<2, float>&, const float&);
template mu::Vector<2, float> mu::operator+
    <2, float, float>(const float&, const mu::Vector<2, float>&);
/* subtraction */
template mu::Vector<2, float>& mu::Vector<2, float>::operator-=
    <float>(const float&);
template mu::Vector<2, float> mu::operator-
    <2, float, float>(const mu::Vector<2, float>&, const float&);
/* multiplication */
template mu::Vector<2, float>& mu::Vector<2, float>::operator*=
    <float>(const float&);
template mu::Vector<2, float> mu::operator*
    <2, float, float>(const mu::Vector<2, float>&, const float&);
template mu::Vector<2, float> mu::operator*
    <2, float, float>(const float&, const mu::Vector<2, float>&);
/* division */
template mu::Vector<2, float>& mu::Vector<2, float>::operator/=
    <float>(const float&);
template mu::Vector<2, float> mu::operator/
    <2, float, float>(const mu::Vector<2, float>&, const float&);

/**
 * Vector <> Scalar test combinations
 */
using VectorScalarCombinationTypes =
    ::testing::Types</* Vector */
                     std::tuple<mu::Vector<2, int>, int>,
                     std::tuple<mu::Vector<2, float>, float>,
                     // different types
                     std::tuple<mu::Vector<2, int>, float>,
                     std::tuple<mu::Vector<2, float>, int>,
                     /* Vector2D */
                     std::tuple<mu::Vector2D<int>, int>,
                     std::tuple<mu::Vector2D<float>, float>,
                     // different types
                     std::tuple<mu::Vector2D<int>, float>,
                     std::tuple<mu::Vector2D<float>, int>,
                     /* Vector3D */
                     std::tuple<mu::Vector3D<int>, int>,
                     std::tuple<mu::Vector3D<float>, float>,
                     // different types
                     std::tuple<mu::Vector3D<int>, float>,
                     std::tuple<mu::Vector3D<float>, int>>;

INSTANTIATE_TYPED_TEST_SUITE_P(Vector, ScalarCombinationsFixture,
                               VectorScalarCombinationTypes);
