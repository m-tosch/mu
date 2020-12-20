#ifndef TESTS_MATRIX_TYPE_H_
#define TESTS_MATRIX_TYPE_H_

#include <algorithm>
#include <array>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "matrix.h"

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
  static TypeParam dummy;  // just to get the size at compile time here
  if constexpr (dummy.size()[0] == 2 && dummy.size()[1] == 2) {
    /** action */
    TypeParam obj{{this->values[0][0], this->values[0][1]},
                  {this->values[1][0], this->values[1][1]}};
    /** assert */
    EXPECT_THAT_ALL(obj, this->values, ::testing::Eq());
  }
}

TYPED_TEST_P(MatrixTypeFixture, ConstructorVariadicTemplateAssignmentSize2x2) {
  static TypeParam dummy;
  if constexpr (dummy.size()[0] == 2 && dummy.size()[1] == 2) {
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

TYPED_TEST_P(MatrixTypeFixture, MemberFuncRows) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::size_type rows = obj.rows();
  /** assert */
  EXPECT_EQ(rows, TypeParam().rows());
  EXPECT_TRUE(noexcept(obj.rows()));
}

TYPED_TEST_P(MatrixTypeFixture, MemberFuncCols) {
  /** arrange */
  TypeParam obj{this->values};
  /** action */
  typename TestFixture::size_type cols = obj.cols();
  /** assert */
  EXPECT_EQ(cols, TypeParam().cols());
  EXPECT_TRUE(noexcept(obj.cols()));
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

REGISTER_TYPED_TEST_SUITE_P(
    MatrixTypeFixture, ConstructorDefault, ConstructorVariadicTemplateSize2x2,
    ConstructorVariadicTemplateAssignmentSize2x2, DestructorDefault,
    ConstructorCopy, ConstructorMove, OperatorCopyAssignment,
    OperatorMoveAssignment, OperatorBrackets, OperatorBracketsConst,
    MemberFuncAt, MemberFuncAtConst, MemberFuncSize, MemberFuncRows,
    MemberFuncCols, MemberFuncBegin, MemberFuncBeginConst, MemberFuncEnd,
    MemberFuncEndConst, MemberFuncMin, MemberFuncMax, MemberFuncSum,
    MemberFuncMean, MemberFuncMeanConvertedType, UtilityFuncMin, UtilityFuncMax,
    UtilityFuncSum, UtilityFuncMean, UtilityFuncMeanConvertedType);

#endif  // TESTS_MATRIX_TYPE_H_