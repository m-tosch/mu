#ifndef TESTS_MATRIX_TYPE_H_
#define TESTS_MATRIX_TYPE_H_

#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "matrix.h"
#include "utility.h"

template <typename T>
class MatrixTypeFixture : public virtual ::testing::Test {
 public:
  /* true "value" and "size" types of the values that the matrix contains */
  using value_type = typename T::value_type::value_type;
  using size_type = typename T::size_type;
  void SetUp() override {
    auto start = static_cast<value_type>(0);
    auto incr = static_cast<value_type>(1.5F);  // NOLINT
    /* put values into the test values "matrix" (array of array) */
    for (auto& inner : values) {  // rows
      for (auto& item : inner) {  // cols
        item = (start += incr);
      }
    }
  }
  /* dummy just for getting dimensions at compile time (inline variable c++17)*/
  static inline T dummy;
  /* test values. exact dimensions of the corresponding matrix-under-test */
  std::array<mu::Vector<dummy.size()[1], value_type>, dummy.size()[0]> values;
  /* some tests need a converted type, defined as
   * - floating point type -> int
   * - integral type -> float
   * if the test input type is neither integral nor floating point, the
   * converted type is equivalent to the test type (i.e. not converted) */
  using ConvertedType = std::conditional_t<
      std::is_integral_v<value_type>, float,
      std::conditional_t<std::is_floating_point_v<value_type>, int,
                         value_type>>;
};

/**
 * @brief macro for comparing all matrix values to all values of the second
 * argument. both argument must be double nested "lists"
 *
 */
// NOLINTNEXTLINE macro is used for convenience and flexibility
#define EXPECT_THAT_ALL(arg1, arg2, eqfunc)                                  \
  {                                                                          \
    for (typename TestFixture::size_type i = 0; i < (arg1).size()[0]; i++) { \
      EXPECT_THAT((arg1)[i], ::testing::Pointwise(eqfunc, (arg2)[i]));       \
    }                                                                        \
  };

TYPED_TEST_SUITE_P(MatrixTypeFixture);

TYPED_TEST_P(MatrixTypeFixture, ConstructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_default_constructible<TypeParam>::value);
  /* std::is_trivially_constructible is true for Matrix but false for children*/
  EXPECT_TRUE(std::is_nothrow_default_constructible<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorVariadicTemplateSize2x2) {
  /* hardcoding this for two arguments since the size must be known to correctly
   * call the variadic template constructor. the constructor itself is
   * (probably) also tested in Matrix derived classes */
  if constexpr (TestFixture::dummy.size()[0] == 2 &&
                TestFixture::dummy.size()[1] == 2) {
    /** action */
    TypeParam obj{{this->values[0][0], this->values[0][1]},
                  {this->values[1][0], this->values[1][1]}};
    /** assert */
    EXPECT_THAT_ALL(obj, this->values, ::testing::Eq());
  }
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorVariadicTemplateAssignmentSize2x2) {
  if constexpr (TestFixture::dummy.size()[0] == 2 &&
                TestFixture::dummy.size()[1] == 2) {
    /** action */
    TypeParam obj = {{this->values[0][0], this->values[0][1]},
                     {this->values[1][0], this->values[1][1]}};
    /** assert */
    EXPECT_THAT_ALL(obj, this->values, ::testing::Eq());
  }
}

/* note: the following constructors are tested in the type combinations file:
 * - Matrix constructor
 * - std::array of Vectors constructor
 * - single value constructor
 * the rationale is that all of these constructors are able take a different
 * type, which must be tested.
 */

/*
 * note: the following constructors are tested in the matrix type combinations
 * file since they are specific to the Matrix class but are able to take
 * different types:
 * - std::array of std::array constructor
 *
 */

TYPED_TEST_P(MatrixTypeFixture, DestructorDefault) {
  /** action & assert */
  EXPECT_TRUE(std::is_destructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_destructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_destructible<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorCopy) {
  /** action & assert */
  EXPECT_TRUE(std::is_copy_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_copy_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_copy_constructible<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorMove) {
  /** action & assert */
  EXPECT_TRUE(std::is_move_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_move_constructible<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_move_constructible<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, OperatorCopyAssignment) {
  /** action & assert */
  EXPECT_TRUE(std::is_copy_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_copy_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_copy_assignable<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, OperatorMoveAssignment) {
  /** action & assert */
  EXPECT_TRUE(std::is_move_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_trivially_move_assignable<TypeParam>::value);
  EXPECT_TRUE(std::is_nothrow_move_assignable<TypeParam>::value);
}

TYPED_TEST_P(MatrixTypeFixture, OperatorBrackets) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&obj, i = 0]() mutable { return obj[i++]; });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj));
  EXPECT_TRUE(noexcept(obj[0]));
}
TYPED_TEST_P(MatrixTypeFixture, OperatorBracketsConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&kObj, i = 0]() mutable { return kObj[i++]; });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(kObj));
  EXPECT_TRUE(noexcept(kObj[0]));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncAt) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&obj, i = 0]() mutable { return obj.at(i++); });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncAtConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  TypeParam res;
  std::generate(res.begin(), res.end(),
                [&kObj, i = 0]() mutable { return kObj.at(i++); });
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(kObj));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncSize) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::size_type size0 = obj.size()[0];
  typename TestFixture::size_type size1 = obj.size()[1];
  /** assert */
  EXPECT_EQ(size0, TypeParam().size()[0]);
  EXPECT_EQ(size1, TypeParam().size()[1]);
  EXPECT_TRUE(noexcept(obj.size()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncNRows) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::size_type rows = obj.n_rows();
  /** assert */
  EXPECT_EQ(rows, TypeParam().n_rows());
  EXPECT_TRUE(noexcept(obj.n_rows()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncNCols) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::size_type cols = obj.n_cols();
  /** assert */
  EXPECT_EQ(cols, TypeParam().n_cols());
  EXPECT_TRUE(noexcept(obj.n_cols()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncBegin) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TypeParam::value_type res = *obj.begin();
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj[0]));
  EXPECT_TRUE(noexcept(*obj.begin()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncBeginConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  typename TypeParam::value_type res = *kObj.begin();
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(kObj[0]));
  EXPECT_TRUE(noexcept(*kObj.begin()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncEnd) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  // end() returns an iterator to the element following the last element
  typename TypeParam::value_type res = *(obj.end() - 1);
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(obj[obj.size()[0] - 1]));
  EXPECT_TRUE(noexcept(*(obj.end() - 1)));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncEndConst) {
  /** arrange */
  const TypeParam kObj{this->values};
  /** action */
  // end() returns an iterator to the element following the last element
  typename TypeParam::value_type res = *(kObj.end() - 1);
  /** assert */
  EXPECT_THAT(res, ::testing::ContainerEq(kObj[kObj.size()[0] - 1]));
  EXPECT_TRUE(noexcept(*(kObj.end() - 1)));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncRow) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  auto row_first = obj.row(0);
  auto row_last = obj.row(TestFixture::dummy.n_rows() - 1);
  /** assert */
  auto comp_first = obj[0];
  auto comp_last = obj[TestFixture::dummy.n_rows() - 1];
  EXPECT_THAT(row_first, ::testing::ContainerEq(comp_first));
  EXPECT_THAT(row_last, ::testing::ContainerEq(comp_last));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncCol) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  auto col_first = obj.col(0);
  auto col_last = obj.col(TestFixture::dummy.n_cols() - 1);
  /** assert */
  mu::Vector<TestFixture::dummy.size()[0], typename TestFixture::value_type>
      comp_first;
  for (std::size_t i = 0; i < TestFixture::dummy.size()[0]; i++) {
    comp_first[i] = this->values[i][0];
  }
  mu::Vector<TestFixture::dummy.size()[0], typename TestFixture::value_type>
      comp_last;
  for (std::size_t i = 0; i < TestFixture::dummy.size()[0]; i++) {
    comp_last[i] = this->values[i][TestFixture::dummy.n_cols() - 1];
  }
  EXPECT_THAT(col_first, ::testing::ContainerEq(comp_first));
  EXPECT_THAT(col_last, ::testing::ContainerEq(comp_last));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncMin) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::value_type min = obj.min();
  /** assert */
  typename TestFixture::value_type comp = obj[0][0];
  for (const auto& row : this->values) {
    comp = std::min(comp, *std::min_element(row.begin(), row.end()));
  }
  EXPECT_EQ(min, comp);
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncMax) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::value_type max = obj.max();
  /** assert */
  typename TestFixture::value_type comp = obj[0][0];
  for (const auto& row : this->values) {
    comp = std::max(comp, *std::max_element(row.begin(), row.end()));
  }
  EXPECT_EQ(max, comp);
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncSum) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::value_type sum_v = obj.sum();
  /** assert */
  typename TestFixture::value_type comp{};
  for (const auto& row : this->values) {
    comp += std::accumulate(row.begin(), row.end(),
                            static_cast<typename TestFixture::value_type>(0));
  }
  EXPECT_EQ(sum_v, comp);
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncMean) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::value_type mean = obj.mean();
  /** assert */
  typename TestFixture::value_type comp{};
  for (const auto& row : this->values) {
    comp += std::accumulate(row.begin(), row.end(),
                            static_cast<typename TestFixture::value_type>(0));
  }
  comp /= (this->values.size() * this->values[0].size());
  EXPECT_EQ(mean, comp);
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncMeanConvertedType) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::ConvertedType mean =
      obj.template mean<typename TestFixture::ConvertedType>();
  /** assert */
  typename TestFixture::value_type sum{};
  for (const auto& row : this->values) {
    sum += std::accumulate(row.begin(), row.end(),
                           static_cast<typename TestFixture::value_type>(0));
  }
  typename TestFixture::ConvertedType comp = sum;
  comp /= (this->values.size() * this->values[0].size());
  EXPECT_EQ(mean, comp);
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncStd) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::value_type std = obj.std();
  /** assert */
  typename TestFixture::value_type sum{};
  for (const auto& row : this->values) {
    sum += std::accumulate(row.begin(), row.end(),
                           static_cast<typename TestFixture::value_type>(0));
  }
  typename TestFixture::value_type mean;
  mean = sum / (this->values.size() * this->values[0].size());

  typename TestFixture::value_type sum2{0};
  for (const auto& row : this->values) {
    for (const auto& item : row) {
      sum2 += mu::pow(item - mean, 2);
    }
  }
  typename TestFixture::value_type comp;
  comp = std::sqrt(sum2 / (this->values.size() * this->values[0].size()));
  EXPECT_FLOAT_EQ(std, comp);
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncStdConvertedType) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::ConvertedType std =
      obj.template std<typename TestFixture::ConvertedType>();
  /** assert */
  typename TestFixture::ConvertedType sum{};
  for (const auto& row : this->values) {
    sum += std::accumulate(row.begin(), row.end(),
                           static_cast<typename TestFixture::value_type>(0));
  }
  typename TestFixture::ConvertedType mean;
  mean = sum / (this->values.size() * this->values[0].size());

  typename TestFixture::ConvertedType sum2{0};
  for (const auto& row : this->values) {
    for (const auto& item : row) {
      sum2 += mu::pow(item - mean, 2);
    }
  }
  typename TestFixture::ConvertedType comp;
  comp = std::sqrt(sum2 / (this->values.size() * this->values[0].size()));
  EXPECT_FLOAT_EQ(std, comp);
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncDiag) {
  /** arrange */
  TypeParam obj{this->values};
  /** action*/
  auto res = obj.diag();
  /** assert */
  constexpr std::size_t s =
      TestFixture::dummy.size()[0] < TestFixture::dummy.size()[1]
          ? TestFixture::dummy.size()[0]
          : TestFixture::dummy.size()[1];
  mu::Vector<s, typename TestFixture::value_type> comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i][i];
  });
  EXPECT_THAT(res, ::testing::Pointwise(::testing::Eq(), comp));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncDet) {
  /* this test is ony for symmetrical matrices */
  if constexpr (TestFixture::dummy.size()[0] == TestFixture::dummy.size()[1]) {
    /** arrange */
    TypeParam obj{this->values};
    /** action*/
    auto res = obj.det();
    /** assert */
    std::vector<std::vector<typename TestFixture::value_type>> vv;
    for (std::size_t i = 0; i < TestFixture::dummy.size()[0]; i++) {
      vv.push_back(std::vector<typename TestFixture::value_type>());
      for (const auto& item : this->values[i]) {
        vv[i].push_back(item);
      }
    }
    /* not an independent comparison value, since the same function to calculate
     * the determinant is used that the matrix function uses. but this test at
     * least ensures that building the 2D nested std::vector from the matrix
     * object works for different sym. matrices */
    typename TestFixture::value_type comp = mu::calc_det(vv);
    EXPECT_EQ(res, comp);
  }
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncTranspose) {
  /* this test is ony for symmetrical matrices */
  if constexpr (TestFixture::dummy.size()[0] == TestFixture::dummy.size()[1]) {
    /** arrange */
    TypeParam obj{this->values};
    /** action */
    obj.transpose();
    /** assert */
    for (std::size_t i = 0; i < TestFixture::dummy.size()[0]; i++) {
      for (std::size_t j = 0; j < TestFixture::dummy.size()[1]; j++) {
        EXPECT_EQ(obj[j][i], this->values[i][j]);
      }
    }
  }
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncTransposed) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  auto res = obj.transposed();
  /** assert */
  for (std::size_t i = 0; i < TestFixture::dummy.size()[0]; i++) {
    for (std::size_t j = 0; j < TestFixture::dummy.size()[1]; j++) {
      EXPECT_EQ(res[j][i], obj[i][j]);
    }
  }
}

TYPED_TEST_P(MatrixTypeFixture, OperatorStreamOut) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  /* 1. read matrix ostream in a stringstream */
  std::stringstream ss;
  ss << obj;
  /* 2. remove unwanted characters. leave ',' separator i */
  std::string s = ss.str();
  char chars[] = " []\n";
  for (unsigned int i = 0; i < strlen(chars); ++i) {              // NOLINT
    s.erase(std::remove(s.begin(), s.end(), chars[i]), s.end());  // NOLINT
  }
  std::stringstream sss;
  sss << s;
  /* 3. put values from string(stream) in a std::vector */
  using vtype = typename TestFixture::value_type;
  std::vector<vtype> v;
  vtype i{};
  while (sss >> i) {
    v.push_back(i);
    if (sss.peek() == ',') {
      sss.ignore();
    }
  }
  /** assert */
  /* compare linear layed out std::vector with nested matrix structure */
  auto rows = this->values.size();
  auto cols = this->values[0].size();
  for (std::size_t i = 0; i < rows; i++) {
    for (std::size_t j = 0; j < cols; j++) {
      EXPECT_EQ(v[i * cols + j], this->values[i][j]);
    }
  }
}

/************************* convenience functions****************************/

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncMin) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::value_type min = mu::min(obj);
  /** assert */
  typename TestFixture::value_type comp = obj[0][0];
  for (const auto& row : this->values) {
    comp = std::min(comp, *std::min_element(row.begin(), row.end()));
  }
  EXPECT_EQ(min, comp);
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncMax) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::value_type max = mu::max(obj);
  /** assert */
  typename TestFixture::value_type comp = obj[0][0];
  for (const auto& row : this->values) {
    comp = std::max(comp, *std::max_element(row.begin(), row.end()));
  }
  EXPECT_EQ(max, comp);
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncSum) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::value_type sum_v = mu::sum(obj);
  /** assert */
  typename TestFixture::value_type comp{};
  for (const auto& row : this->values) {
    comp += std::accumulate(row.begin(), row.end(),
                            static_cast<typename TestFixture::value_type>(0));
  }
  EXPECT_EQ(sum_v, comp);
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncMean) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::value_type mean = mu::mean(obj);
  /** assert */
  typename TestFixture::value_type comp{};
  for (const auto& row : this->values) {
    comp += std::accumulate(row.begin(), row.end(),
                            static_cast<typename TestFixture::value_type>(0));
  }
  comp /= (this->values.size() * this->values[0].size());
  EXPECT_EQ(mean, comp);
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncMeanConvertedType) { /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::ConvertedType mean =
      mu::mean<typename TestFixture::ConvertedType>(obj);
  /** assert */
  typename TestFixture::value_type sum{};
  for (const auto& row : this->values) {
    sum += std::accumulate(row.begin(), row.end(),
                           static_cast<typename TestFixture::value_type>(0));
  }
  typename TestFixture::ConvertedType comp = sum;
  comp /= (this->values.size() * this->values[0].size());
  EXPECT_EQ(mean, comp);
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncDiagMakeVector) {
  /** arrange */
  TypeParam obj{this->values};
  /** action*/
  auto res = mu::diag(obj);
  /** assert */
  constexpr std::size_t s =
      TestFixture::dummy.size()[0] < TestFixture::dummy.size()[1]
          ? TestFixture::dummy.size()[0]
          : TestFixture::dummy.size()[1];
  mu::Vector<s, typename TestFixture::value_type> comp;
  std::generate(comp.begin(), comp.end(), [&, i = -1]() mutable {
    i++;
    return this->values[i][i];
  });
  EXPECT_THAT(res, ::testing::Pointwise(::testing::Eq(), comp));
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncDet) {
  /* this test is ony for symmetrical matrices */
  if constexpr (TestFixture::dummy.size()[0] == TestFixture::dummy.size()[1]) {
    /** arrange */
    TypeParam obj{this->values};
    /** action*/
    auto res = mu::det(obj);
    /** assert */
    std::vector<std::vector<typename TestFixture::value_type>> vv;
    for (std::size_t i = 0; i < TestFixture::dummy.size()[0]; i++) {
      vv.push_back(std::vector<typename TestFixture::value_type>());
      for (const auto& item : this->values[i]) {
        vv[i].push_back(item);
      }
    }
    /* not an independent comparison value! (see det() member function test) */
    typename TestFixture::value_type comp = mu::calc_det(vv);
    EXPECT_EQ(res, comp);
  }
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncTranspose) {
  /* this test is ony for symmetrical matrices */
  if constexpr (TestFixture::dummy.size()[0] == TestFixture::dummy.size()[1]) {
    /** arrange */
    TypeParam obj{this->values};
    /** action */
    mu::transpose(obj);
    /** assert */
    for (std::size_t i = 0; i < TestFixture::dummy.size()[0]; i++) {
      for (std::size_t j = 0; j < TestFixture::dummy.size()[1]; j++) {
        EXPECT_EQ(obj[j][i], this->values[i][j]);
      }
    }
  }
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncTransposed) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  auto res = mu::transposed(obj);
  /** assert */
  for (std::size_t i = 0; i < TestFixture::dummy.size()[0]; i++) {
    for (std::size_t j = 0; j < TestFixture::dummy.size()[1]; j++) {
      EXPECT_EQ(res[j][i], obj[i][j]);
    }
  }
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncEye) {
  /* this test is ony for symmetrical matrices */
  if constexpr (TestFixture::dummy.size()[0] == TestFixture::dummy.size()[1]) {
    /** arrange */
    /** action*/
    TypeParam res = mu::eye<TestFixture::dummy.size()[0]>();
    /** assert */
    TypeParam comp{};
    for (std::size_t i = 0; i < TestFixture::dummy.size()[0]; i++) {
      comp[i][i] = 1;
    }
    EXPECT_THAT(res, ::testing::ContainerEq(comp));
  }
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncOnes) {
  /** action */
  TypeParam res =
      mu::ones<TestFixture::dummy.size()[0], TestFixture::dummy.size()[1]>();
  /** assert */
  TypeParam comp;
  auto one = static_cast<typename TestFixture::value_type>(1);
  for (auto& row : comp) {
    for (auto& item : row) {
      item = one;
    }
  }
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

TYPED_TEST_P(MatrixTypeFixture, UtilityFuncZeros) {
  /** action */
  TypeParam res =
      mu::zeros<TestFixture::dummy.size()[0], TestFixture::dummy.size()[1]>();
  /** assert */
  TypeParam comp;
  auto zero = static_cast<typename TestFixture::value_type>(0);
  for (auto& row : comp) {
    for (auto& item : row) {
      item = zero;
    }
  }
  EXPECT_THAT(res, ::testing::ContainerEq(comp));
}

REGISTER_TYPED_TEST_SUITE_P(
    MatrixTypeFixture, ConstructorDefault, ConstructorVariadicTemplateSize2x2,
    ConstructorVariadicTemplateAssignmentSize2x2, DestructorDefault,
    ConstructorCopy, ConstructorMove, OperatorCopyAssignment,
    OperatorMoveAssignment, OperatorBrackets, OperatorBracketsConst,
    MemberFuncAt, MemberFuncAtConst, MemberFuncSize, MemberFuncNRows,
    MemberFuncNCols, MemberFuncBegin, MemberFuncBeginConst, MemberFuncEnd,
    MemberFuncEndConst, MemberFuncRow, MemberFuncCol, MemberFuncMin,
    MemberFuncMax, MemberFuncSum, MemberFuncMean, MemberFuncDiag, MemberFuncDet,
    MemberFuncMeanConvertedType, MemberFuncStd, MemberFuncStdConvertedType,
    MemberFuncTranspose, MemberFuncTransposed, OperatorStreamOut,
    UtilityFuncMin, UtilityFuncMax, UtilityFuncSum, UtilityFuncMean,
    UtilityFuncMeanConvertedType, UtilityFuncDiagMakeVector, UtilityFuncDet,
    UtilityFuncTranspose, UtilityFuncTransposed, UtilityFuncEye,
    UtilityFuncOnes, UtilityFuncZeros);

#endif  // TESTS_MATRIX_TYPE_H_