#include <gtest/gtest.h>

#include "mu/vector.h"
#include "mu/vector3d.h"
#include "vector_type.h"

/**
 * Instantiate this template class and template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */
template class mu::Vector3D<float>;

/**
 * Instantiate the Vector test suite
 */
using Vector3DTypes = ::testing::Types<mu::Vector3D<float>, mu::Vector3D<int>>;
INSTANTIATE_TYPED_TEST_SUITE_P(Vector3D, VectorTypeFixture, Vector3DTypes);

/*******************************Vector3D***************************************/

template <typename T>
class Vector3DTypeFixture : public VectorTypeFixture<T> {
 public:
  void SetUp() override {  // NOLINT
    /* explicitly call base class setup */
    VectorTypeFixture<T>::SetUp();
    /* variables for convenience */
    x = this->values[0];
    y = this->values[1];
    z = this->values[2];
  }
  typename T::value_type x;
  typename T::value_type y;
  typename T::value_type z;
};

TYPED_TEST_SUITE(Vector3DTypeFixture, Vector3DTypes);

TYPED_TEST(Vector3DTypeFixture, ConstructorXYZ) {
  /** arrange */
  TypeParam obj{this->x, this->y, this->z};
  /** assert */
  EXPECT_THAT(obj, ::testing::Pointwise(::testing::Eq(), this->values));
}

TYPED_TEST(Vector3DTypeFixture, ConstructorCopyInitialization) {
  /** arrange */
  mu::Vector<3, typename TypeParam::value_type> obj1{this->values};
  TypeParam obj2 = obj1;
  /** assert */
  EXPECT_THAT(obj1, ::testing::ContainerEq(obj2));
}

TYPED_TEST(Vector3DTypeFixture, MemberVarX) {
  /** arrange */
  TypeParam obj{this->x, this->y, this->z};
  /** action */
  typename TypeParam::value_type x = obj.x();
  /** assert */
  EXPECT_EQ(x, this->x);
}

TYPED_TEST(Vector3DTypeFixture, MemberVarXConst) {
  /** arrange */
  const TypeParam kObj{this->x, this->y, this->z};
  /** action */
  typename TypeParam::value_type x = kObj.x();
  /** assert */
  EXPECT_EQ(x, this->x);
}

TYPED_TEST(Vector3DTypeFixture, MemberVarY) {
  /** arrange */
  TypeParam obj{this->x, this->y, this->z};
  /** action */
  typename TypeParam::value_type y = obj.y();
  /** assert */
  EXPECT_EQ(y, this->y);
}

TYPED_TEST(Vector3DTypeFixture, MemberVarYConst) {
  /** arrange */
  const TypeParam kObj{this->x, this->y, this->z};
  /** action */
  typename TypeParam::value_type y = kObj.y();
  /** assert */
  EXPECT_EQ(y, this->y);
}

TYPED_TEST(Vector3DTypeFixture, MemberVarZ) {
  /** arrange */
  TypeParam obj{this->x, this->y, this->z};
  /** action */
  typename TypeParam::value_type z = obj.z();
  /** assert */
  EXPECT_EQ(z, this->z);
}

TYPED_TEST(Vector3DTypeFixture, MemberVarZConst) {
  /** arrange */
  const TypeParam kObj{this->x, this->y, this->z};
  /** action */
  typename TypeParam::value_type z = kObj.z();
  /** assert */
  EXPECT_EQ(z, this->z);
}
