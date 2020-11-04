#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "vector_type.h"

/**
 * Instantiate this template class and template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
template class mu::Vector2D<float>;
/* functions */
template void mu::Vector2D<float>::rotate<float>(float);

/**
 * Instantiate the Vector test suite
 */
using Vector2DTypes = ::testing::Types<mu::Vector2D<float>, mu::Vector2D<int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector2D, VectorTypeFixture, Vector2DTypes);

/*******************************Vector2D***************************************/

template <typename T>
class Vector2DTypeFixture : public VectorTypeFixture<T> {
 public:
  void SetUp() override {  // NOLINT
    /* explicitly call base class setup */
    VectorTypeFixture<T>::SetUp();
    /* variables for convenience */
    x = this->values[0];
    y = this->values[1];
  }
  typename T::value_type x;
  typename T::value_type y;
};

TYPED_TEST_SUITE(Vector2DTypeFixture, Vector2DTypes);

TYPED_TEST(Vector2DTypeFixture, testTestTestTest) {
  /** arrange */
  // mu::Vector<2, float> a = {1.5F, 2.5F};
  // mu::Vector<2, int> b{a};
  // mu::Vector<2, int> a = {1, 2};
  // compiles
  // std::array<int, 2> arr = {1, 2};

  // mu::Vector2D<int> a{1, 2};
  // mu::Vector<2, float> b{a};
  // // mu::Vector<2, float> bb{a, b};
  // // compiles
  // mu::Vector<2, int> c{3, 4};
  // mu::Vector2D<float> d{c};
  // // compiles
  // mu::Vector2D<int> e{5, 6};
  // mu::Vector2D<float> f{e};
  // // compiles
  // mu::Vector<2, int> g{7, 8};
  // mu::Vector<2, float> h{g};

  /** action */
  // a = a + 2;
  // a = 2 + a;
  // a = b + 2;
  // a = 2 + b;
  // a += 2;
  /** assert */
  EXPECT_TRUE(true);
}

TYPED_TEST(Vector2DTypeFixture, ConstructorXY) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** assert */
  EXPECT_THAT(obj, ::testing::Pointwise(::testing::Eq(), this->values));
}

TYPED_TEST(Vector2DTypeFixture, ConstructorCopyInitialization) {
  /** arrange */
  mu::Vector<2, typename TypeParam::value_type> obj1{this->values};
  /** action */
  TypeParam obj2 = obj1;
  /** assert */
  EXPECT_THAT(obj1, ::testing::ContainerEq(obj2));
}

TYPED_TEST(Vector2DTypeFixture, MemberVarX) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** action */
  typename TypeParam::value_type x = obj.x();
  /** assert */
  EXPECT_EQ(x, this->x);
  EXPECT_TRUE(noexcept(obj.x()));
}

TYPED_TEST(Vector2DTypeFixture, MemberVarXConst) {
  /** arrange */
  const TypeParam kObj{this->x, this->y};
  /** action */
  typename TypeParam::value_type x = kObj.x();
  /** assert */
  EXPECT_EQ(x, this->x);
  EXPECT_TRUE(noexcept(kObj.x()));
}

TYPED_TEST(Vector2DTypeFixture, MemberVarY) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** action */
  typename TypeParam::value_type y = obj.y();
  /** assert */
  EXPECT_EQ(y, this->y);
  EXPECT_TRUE(noexcept(obj.y()));
}

TYPED_TEST(Vector2DTypeFixture, MemberVarYConst) {
  /** arrange */
  const TypeParam kObj{this->x, this->y};
  /** action */
  typename TypeParam::value_type y = kObj.y();
  /** assert */
  EXPECT_EQ(y, this->y);
  EXPECT_TRUE(noexcept(kObj.y()));
}

//  // TODO
// TYPED_TEST(Vector2DTypeFixture, MemberFuncRotate) {

//   if constexpr (std::is_floating_point_v<typename TypeParam::value_type>) {
//     /** arrange */
//     TypeParam obj{1, 0};
//     /** action */
//     obj.rotate(1.57F);
//     /** assert */
//     EXPECT_FLOAT_EQ(obj.x(), 0);
//     EXPECT_FLOAT_EQ(obj.y(), 1);
//   }
// }