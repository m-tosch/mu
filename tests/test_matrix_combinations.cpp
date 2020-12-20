#include <tuple>

#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "same_type_combinations.h"

/**
 * Matrix <> Matrix test combinations
 */
using MatrixTypeCombinations = ::testing::Types<
    /* Matrix */
    std::tuple<mu::Matrix<2, 2, float>, mu::Matrix<2, 2, float>>,
    // both ways
    std::tuple<mu::Matrix<2, 2, float>, mu::Matrix<2, 2, int>>,
    std::tuple<mu::Matrix<2, 2, int>, mu::Matrix<2, 2, float>>>;

/********************************* INIT ************************************/

/**
 * explicit instantiations
 */
/* constructor (construct-from-different-typed-matrix) */
template mu::Matrix<2, 2, float>::Matrix(const mu::Matrix<2, 2, int> &);
/* constructor (construct-from-different-typed-array) */
template mu::Matrix<2, 2, float>::Matrix(
    const std::array<mu::Vector<2, int>, 2> &);
/* constructor (construct-from-different-typed-single-value) */
template mu::Matrix<2, 2, float>::Matrix(const int &);

INSTANTIATE_TYPED_TEST_SUITE_P(Matrix, SameTypeCombinationsInitFixture,
                               MatrixTypeCombinations);

/****************************** MATH ***************************************/

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

INSTANTIATE_TYPED_TEST_SUITE_P(Matrix, SameTypeCombinationsMathFixture,
                               MatrixTypeCombinations);

/************************* Matrix specific tests ***************************/

/* constructor (construct-from-different-typed-array-of-array) */
template mu::Matrix<2, 2, float>::Matrix(
    const std::array<std::array<int, 2>, 2> &);

template <typename T>
class MatrixCombinationsFixture : public SameTypeCombinationsFixture<T> {
 public:
  void SetUp() override {  // NOLINT
    SameTypeCombinationsFixture<T>::SetUp();
  }
  static inline typename SameTypeCombinationsFixture<T>::T1 dummy;
};

TYPED_TEST_SUITE(MatrixCombinationsFixture, MatrixTypeCombinations);

TYPED_TEST(MatrixCombinationsFixture, ConstructorFromArrayOfArrays) {
  /** arrange */
  constexpr auto rows = this->dummy.size()[0];
  constexpr auto cols = this->dummy.size()[1];
  std::array<
      std::array<typename TestFixture::BaseTypeFixture2::value_type, cols>,
      rows>
      arr;
  for (std::size_t i = 0; i < arr.size(); i++) {
    for (std::size_t j = 0; j < arr[0].size(); j++) {
      arr[i][j] = this->values()[i][j];
    }
  }
  /** action */
  typename TestFixture::T1 res1{arr};
  typename TestFixture::T1 res2 = arr;
  typename TestFixture::T1 res3 = {arr};
  /** assert */
  for (typename TestFixture::BaseTypeFixture1::size_type i = 0; i < rows; i++) {
    EXPECT_THAT(res1[i], ::testing::Pointwise(::testing::FloatEq(), arr[i]));
    EXPECT_THAT(res2[i], ::testing::Pointwise(::testing::FloatEq(), arr[i]));
    EXPECT_THAT(res3[i], ::testing::Pointwise(::testing::FloatEq(), arr[i]));
  }
}
