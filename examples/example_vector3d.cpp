
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "mu/vector3d.h"

TEST(Vector3D, ConstructorFromDifferentType) {
  //! [vector3d different type constructor]

  mu::Vector3D<float> a = {1.5F, 2.5F, 3.5F};
  mu::Vector3D<int> b = {a};

  //! [vector3d different type constructor]
  EXPECT_THAT(b, ::testing::ElementsAre(1, 2, 3));
}

TEST(Vector3D, MemberFuncX) {
  //! [vector3d x function]

  mu::Vector3D<int> a = {7, 8, 9};
  int x = a.x();

  //! [vector3d x function]
  EXPECT_EQ(x, 7);
}

TEST(Vector3D, MemberFuncXConst) {
  //! [vector3d const x function]

  const mu::Vector3D<int> a = {7, 8, 9};
  int x = a.x();

  //! [vector3d const x function]
  EXPECT_EQ(x, 7);
}

TEST(Vector3D, MemberFuncY) {
  //! [vector3d y function]

  mu::Vector3D<int> a = {7, 8, 9};
  int y = a.y();

  //! [vector3d y function]
  EXPECT_EQ(y, 8);
}

TEST(Vector3D, MemberFuncYConst) {
  //! [vector3d const y function]

  const mu::Vector3D<int> a = {7, 8, 9};
  int y = a.y();

  //! [vector3d const y function]
  EXPECT_EQ(y, 8);
}

TEST(Vector3D, MemberFuncZ) {
  //! [vector3d z function]

  mu::Vector3D<int> a = {7, 8, 9};
  int z = a.z();

  //! [vector3d z function]
  EXPECT_EQ(z, 9);
}

TEST(Vector3D, MemberFuncZConst) {
  //! [vector3d const z function]

  const mu::Vector3D<int> a = {7, 8, 9};
  int z = a.z();

  //! [vector3d const z function]
  EXPECT_EQ(z, 9);
}