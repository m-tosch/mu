#include <tuple>

#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "same_type_combinations.h"

using MatrixTypeCombinations = ::testing::Types<
    /* Matrix */
    std::tuple<mu::Matrix<2, 2, float>, mu::Matrix<2, 2, float>>,
    // both ways
    std::tuple<mu::Matrix<2, 2, float>, mu::Matrix<2, 2, int>>,
    std::tuple<mu::Matrix<2, 2, int>, mu::Matrix<2, 2, float>>>;

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
};

TYPED_TEST_SUITE(MatrixCombinationsFixture, MatrixTypeCombinations);

TYPED_TEST(MatrixCombinationsFixture, ConstructorFromArrayOfArrays) {
  /** arrange */
  static typename TestFixture::T1 dummy;
  constexpr auto rows = dummy.size()[0];
  constexpr auto cols = dummy.size()[1];
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

/* test is only designed for two matrices of exactly the same dimensions */
TYPED_TEST(MatrixCombinationsFixture, MemberFuncDotMatrixMatrix) {
  /** arrange */
  static typename TestFixture::T1 dummy1;
  static typename TestFixture::T2 dummy2;
  constexpr auto rows1 = dummy1.size()[0];
  constexpr auto cols1 = dummy1.size()[1];
  constexpr auto cols2 = dummy2.size()[1];
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  typename TestFixture::T1 res;
  if constexpr (std::is_same_v<typename TestFixture::T1,
                               typename TestFixture::T2>) {
    res = obj1.dot(obj2);
  } else {
    res = obj1.template dot<typename TestFixture::BaseTypeFixture1::value_type>(
        obj2);
  }
  /** assert */
  typename TestFixture::T1 comp;
  for (std::size_t i = 0; i < rows1; i++) {
    for (std::size_t j = 0; j < cols2; j++) {
      typename TestFixture::BaseTypeFixture1::value_type sum{0};
      for (std::size_t k = 0; k < cols1; k++) {
        sum += (obj1[i][k] * obj2[k][j]);
      }
      comp[i][j] = sum;
    }
  }
  EXPECT_TRUE(res == comp);
}

/************************* convenience functions ***************************/

/* test is only designed for two matrices of exactly the same dimensions */
TYPED_TEST(MatrixCombinationsFixture, UtilityFuncDotMatrixMatrix) {
  /** arrange */
  static typename TestFixture::T1 dummy1;
  static typename TestFixture::T2 dummy2;
  constexpr auto rows1 = dummy1.size()[0];
  constexpr auto cols1 = dummy1.size()[1];
  constexpr auto cols2 = dummy2.size()[1];
  typename TestFixture::T1 obj1{this->values()};
  typename TestFixture::T2 obj2{this->values2()};
  /** action */
  typename TestFixture::T1 res;
  if constexpr (std::is_same_v<typename TestFixture::T1,
                               typename TestFixture::T2>) {
    res = mu::dot(obj1, obj2);
  } else {
    res =
        mu::dot<typename TestFixture::BaseTypeFixture1::value_type>(obj1, obj2);
  }
  /** assert */
  typename TestFixture::T1 comp;
  for (std::size_t i = 0; i < rows1; i++) {
    for (std::size_t j = 0; j < cols2; j++) {
      typename TestFixture::BaseTypeFixture1::value_type sum{0};
      for (std::size_t k = 0; k < cols1; k++) {
        sum += (obj1[i][k] * obj2[k][j]);
      }
      comp[i][j] = sum;
    }
  }
  EXPECT_TRUE(res == comp);
}