#include <tuple>

#include "gtest/gtest.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "mu/vector3d.h"
#include "scalar_combinations.h"

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
