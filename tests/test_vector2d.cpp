#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include "mu/matrix.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "vector_type.h"

/**
 * Instantiate the Vector test suite
 */
using Vector2DTypes =
    ::testing::Types</*mu::Vector2D<float>,*/ mu::Vector2D<int>>;
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
  // TypeParam obj{this->x, this->y};
  // TypeParam obj{{this->x, this->y}};

  // mu::Vector<2, typename TypeParam::value_type> obj3{{this->x, this->y}};
  // mu::Vector<2, typename TypeParam::value_type> obj4{this->x, this->y};

  // references
  // int knum1 = 9;
  // int knum2 = 4;
  // mu::Vector<2, std::reference_wrapper<int>> v{std::ref(knum1),
  //                                              std::ref(knum2)};
  // v += 2;
  // int mean_ref = v.mean(); // error

  // ctor-from-different-type
  // mu::Matrix<2, 2, int> aa = {{1, 2}, {3, 4}};
  // mu::Matrix<2, 2, double> bb = {aa};

  // mu::Vector<2, float> aaa = {1.5F, 2.5F};
  // mu::Vector<2, int> v1 = static_cast<mu::Vector<2, float>>(aaa);
  // mu::Vector<2, int> v2 = static_cast<mu::Vector<2, int>>(aaa);
  // mu::Vector<2, int> v3 = aaa;

  // mu::Matrix<2, 2, float> cc = {{1.5F, 2.5F}, {3.5F, 4.5F}};
  // mu::Matrix<2, 2, int> dd = {cc};

  // single value init ctor from different type
  // mu::Vector<3, float> test{5.5F};
  // mu::Vector<3, float> test2{5};
  // mu::Vector<3, int> test3{5.5F};
  // mu::Vector<3, int> test4{5};

  // dot
  mu::Vector<3, float> a{1.1F, 2.2F, 3.3F};
  // // mu::Vector<3, float> b{1.1F, 2.2F, 3.3F};
  // mu::Vector<3, int> b{1, 2, 3};
  // /*************** member function **************/
  // // float dot1 = a.dot(b);
  // // int dot2 = a.dot(b);
  // float dot3 = a.dot<float>(b);
  // int dot4 = a.dot<int>(b);
  // float dot5 = a.dot<int>(b);
  // int dot6 = a.dot<float>(b);
  // // float dot1_ = b.dot(a);
  // // int dot2_ = b.dot(a);
  // float dot3_ = b.dot<float>(a);
  // int dot4_ = b.dot<int>(a);
  // float dot5_ = b.dot<int>(a);
  // int dot6_ = b.dot<float>(a);
  // /*************** convenience function **************/
  // // float c_dot1 = dot(a,b);
  // // int c_dot2 = dot(a,b);
  // float c_dot3 = mu::dot<float>(a, b);
  // int c_dot4 = mu::dot<int>(a, b);
  // float c_dot5 = mu::dot<int>(a, b);
  // int c_dot6 = mu::dot<float>(a, b);
  // // float c_dot1_ = b.dot(a);
  // // int c_dot2_ = b.dot(a);
  // float c_dot3_ = mu::dot<float>(b, a);
  // int c_dot4_ = mu::dot<int>(b, a);
  // float c_dot5_ = mu::dot<int>(b, a);
  // int c_dot6_ = mu::dot<float>(b, a);

  // float b_length = b.length<float>();
  // float b_length2 = b.length();
  // float a_length2 = a.length();
  // float a_length3 = a.length<int>();
  // int a_length4 = a.length<float>();
  // float a_length_gt = a.length<float>();

  // mu::Vector<3, int> vv{2, 3, 5};
  // mu::Vector<3, float> vv{2.0F, 3.0F, 5.0F};
  // float mean_convenience = mu::mean(vv);
  // float mean_convenience2 = mu::mean<float>(vv);
  // float mean_convenience3 = mu::mean<int>(vv);
  // int mean_convenience4 = mu::mean<int>(vv);
  // int mean_convenience5 = mu::mean(vv);

  // float mean_convenience_ = vv.mean();
  // float mean_convenience2_ = vv.mean<float>();
  // float mean_convenience3_ = vv.mean<int>();
  // int mean_convenience4_ = vv.mean<int>();
  // int mean_convenience5_ = vv.mean();

  // mu::Vector2D<int> v1{1, 2};
  // mu::Vector2D<int> v2{3, 4};
  // mu::Matrix<2, 2, int> m{{v1, v2}};

  // mu::Vector<2, int> v1{2, 2};
  // mu::Vector<3, int> v2{2, 2, 2};
  // bool resv = (v1 == v2);

  // mu::Matrix<1, 2, int> m1{{3, 4}};
  // mu::Matrix<1, 2, int> m2{{3, 4}};
  // mu::Matrix<1, 3, int> m3{{2, 4, 8}};
  // bool res1 = (m1 == m2);
  // bool res2 = (m1 == m3);

  // bool res = std::is_same<int,
  // mu::unwrap_ref_t<std::reference_wrapper<int>>>();

  EXPECT_TRUE(true);
}

TYPED_TEST(Vector2DTypeFixture, ConstructorXY) {
  /** arrange */
  TypeParam obj{this->x, this->y};
  /** assert */
  EXPECT_THAT(obj, ::testing::Pointwise(::testing::Eq(), this->values));
}

TYPED_TEST(Vector2DTypeFixture, ConstructorFromParentInitialization) {
  /** arrange */
  mu::Vector<2, typename TypeParam::value_type> obj1{this->values};
  /** action */
  TypeParam obj2{obj1};
  /** assert */
  EXPECT_THAT(obj1, ::testing::ContainerEq(obj2));
}

TYPED_TEST(Vector2DTypeFixture, ConstructorFromParentCopyInitialization) {
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

// // TODO
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