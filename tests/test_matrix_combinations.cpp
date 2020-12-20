#include <tuple>

#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "same_type_combinations.h"

using MatrixTypeCombinations = ::testing::Types<
    /* Matrix */
    std::tuple<mu::Matrix<2, 2, float>, mu::Matrix<2, 2, float>>/*,
    // both ways
    std::tuple<mu::Matrix<2, 2, float>, mu::Matrix<2, 2, int>>,
    std::tuple<mu::Matrix<2, 2, int>, mu::Matrix<2, 2, float>>*/>;

/********************************* INIT ************************************/

INSTANTIATE_TYPED_TEST_SUITE_P(Matrix, SameTypeCombinationsInitFixture,
                               MatrixTypeCombinations);

/********************************* MATH ************************************/

INSTANTIATE_TYPED_TEST_SUITE_P(Matrix, SameTypeCombinationsMathFixture,
                               MatrixTypeCombinations);

/************************* Matrix specific tests ***************************/

template <typename T>
class MatrixCombinationsFixture : public SameTypeCombinationsFixture<T> {
 public:
  void SetUp() override {  // NOLINT
    SameTypeCombinationsFixture<T>::SetUp();
  }
  static constexpr typename SameTypeCombinationsFixture<T>::T1 dummy;
};

TYPED_TEST_SUITE(MatrixCombinationsFixture, MatrixTypeCombinations);

TYPED_TEST(MatrixCombinationsFixture, ConstructorFromArrayOfArrays) {
  /** arrange */
  constexpr std::size_t rows = this->dummy.size()[0];
  constexpr std::size_t cols = this->dummy.size()[1];
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
