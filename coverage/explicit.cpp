#include "mu/matrix.h"
#include "mu/vector.h"
#include "mu/vector2d.h"
#include "mu/vector3d.h"

/**
 * Instantiate this template class and template functions explicitly so that all
 * functions are generated and thus, the coverage report is accurate.
 */

/*************************** test_vector.cpp ***************************/

/* class */
template class mu::Vector<2, float>;
/* functions */
template float mu::Vector<2, float>::length<float>() const;
template float mu::Vector<2, int>::mean<float>() const;
template float mu::Vector<2, int>::dot<float>(const mu::Vector<2, int> &) const;
// workaround for "lambda functions are not allowed in unevaluated operands"
struct LambdaCompare {
  bool operator()(int a, int b) const { return a > b; }
};
template void mu::Vector<2, float>::sort(const LambdaCompare &);
template mu::Vector<2, float> mu::Vector<2, float>::sorted(
    const LambdaCompare &) const;

/* operators */
template std::ostream &mu::operator<<<2, float>(std::ostream &,
                                                const mu::Vector<2, float> &);

/* convenience functions */
/* these functions take a single Vector as argument, so they're here.
 * functions that take e.g a combination of Vectors as argument are
 * elsewhere */
template float mu::min(const mu::Vector<2, float> &);
template float mu::max(const mu::Vector<2, float> &);
template float mu::sum(const mu::Vector<2, float> &);
template float mu::mean<float>(const mu::Vector<2, int> &);
template void mu::flip(mu::Vector<2, float> &);
template mu::Vector<2, float> mu::flipped(const mu::Vector<2, float> &);
template void mu::sort(mu::Vector<2, float> &);
template void mu::sort(mu::Vector<2, float> &, const LambdaCompare &);
template mu::Vector<2, float> mu::sorted(const mu::Vector<2, float> &);
template mu::Vector<2, float> mu::sorted(const mu::Vector<2, float> &,
                                         const LambdaCompare &);

/*************************** test_vector2d.cpp ***************************/

/* class */
template class mu::Vector2D<float>;
/* functions */
template void mu::Vector2D<float>::rotate<float>(float);
template mu::Vector2D<float> mu::Vector2D<float>::rotated<float>(float);

/*************************** test_vector3d.cpp ***************************/

/* class */
template class mu::Vector3D<float>;

/*************************** Vector <> Scalar ***************************/

/* addition */
template mu::Vector<2, float> &mu::Vector<2, float>::operator+=
    <float>(const float &);
template mu::Vector<2, float> mu::operator+
    <2, float, float>(const mu::Vector<2, float> &, const float &);
template mu::Vector<2, float> mu::operator+
    <2, float, float>(const float &, const mu::Vector<2, float> &);
/* subtraction */
template mu::Vector<2, float> &mu::Vector<2, float>::operator-=
    <float>(const float &);
template mu::Vector<2, float> mu::operator-
    <2, float, float>(const mu::Vector<2, float> &, const float &);
/* multiplication */
template mu::Vector<2, float> &mu::Vector<2, float>::operator*=
    <float>(const float &);
template mu::Vector<2, float> mu::operator*
    <2, float, float>(const mu::Vector<2, float> &, const float &);
template mu::Vector<2, float> mu::operator*
    <2, float, float>(const float &, const mu::Vector<2, float> &);
/* division */
template mu::Vector<2, float> &mu::Vector<2, float>::operator/=
    <float>(const float &);
template mu::Vector<2, float> mu::operator/
    <2, float, float>(const mu::Vector<2, float> &, const float &);

/*************************** Vector <> Vector ***************************/

/***** constructors *****/
/* constructor (construct-from-different-typed-vector) */
template mu::Vector<2, float>::Vector(const mu::Vector<2, int> &);
/* constructor (construct-from-different-typed-array) */
template mu::Vector<2, float>::Vector(const std::array<int, 2> &);
/* constructor (construct-from-different-typed-single-value) */
template mu::Vector<2, float>::Vector(const int &);

/********* math ********/
/* note: +=, -=, *= and /= do not have to be explicitly instantiated */
/* addition */
template mu::Vector<2, float> mu::operator+
    <2, float, int>(const mu::Vector<2, float> &, const mu::Vector<2, int> &);
/* subtraction */
template mu::Vector<2, float> mu::operator-
    <2, float, int>(const mu::Vector<2, float> &, const mu::Vector<2, int> &);
/* multiplication */
template mu::Vector<2, float> mu::operator*
    <2, float, int>(const mu::Vector<2, float> &, const mu::Vector<2, int> &);
/* division */
template mu::Vector<2, float> mu::operator/
    <2, float, int>(const mu::Vector<2, float> &, const mu::Vector<2, int> &);
/* equality (this operator is also called by gtest. probably ContainerEq...) */
template bool mu::Vector<2, float>::operator==
    <int>(const mu::Vector<2, int> &) const;
/* inequality */
template bool mu::Vector<2, float>::operator!=
    <int>(const mu::Vector<2, int> &) const;

/********* vector specific ********/
/* convenience functions */
/* these functions should take a combination of Vectors, so they're here.
 * functions that take e.g a single Vector as argument are elsewhere */
template int mu::dot<int, 2, float, 2, float>(const mu::Vector<2, float> &,
                                              const mu::Vector<2, float> &);

/*************************** test_matrix.cpp ***************************/

/* class */
template class mu::Matrix<2, 2, float>;
/* convenience functions */
/* these functions take a single Matrix as argument, so they're here. functions
 * that take e.g a combination of Matrices as argument are elsewhere */
template float mu::min(const mu::Matrix<2, 2, float> &);
template float mu::max(const mu::Matrix<2, 2, float> &);
template float mu::sum(const mu::Matrix<2, 2, float> &);
template float mu::mean<float>(const mu::Matrix<2, 2, float> &);

/*************************** Matrix <> Scalar ***************************/

/* addition */
template mu::Matrix<2, 2, float> &mu::Matrix<2, 2, float>::operator+=
    <float>(const float &);
template mu::Matrix<2, 2, float> mu::operator+
    <2, 2, float, float>(const mu::Matrix<2, 2, float> &, const float &);
template mu::Matrix<2, 2, float> mu::operator+
    <2, 2, float, float>(const float &, const mu::Matrix<2, 2, float> &);
/* subtraction */
template mu::Matrix<2, 2, float> &mu::Matrix<2, 2, float>::operator-=
    <float>(const float &);
template mu::Matrix<2, 2, float> mu::operator-
    <2, 2, float, float>(const mu::Matrix<2, 2, float> &, const float &);
/* multiplication */
template mu::Matrix<2, 2, float> &mu::Matrix<2, 2, float>::operator*=
    <float>(const float &);
template mu::Matrix<2, 2, float> mu::operator*
    <2, 2, float, float>(const mu::Matrix<2, 2, float> &, const float &);
template mu::Matrix<2, 2, float> mu::operator*
    <2, 2, float, float>(const float &, const mu::Matrix<2, 2, float> &);
/* division */
template mu::Matrix<2, 2, float> &mu::Matrix<2, 2, float>::operator/=
    <float>(const float &);
template mu::Matrix<2, 2, float> mu::operator/
    <2, 2, float, float>(const mu::Matrix<2, 2, float> &, const float &);

/*************************** Matrix <> Matrix ***************************/

/***** constructors *****/
/* constructor (construct-from-different-typed-matrix) */
template mu::Matrix<2, 2, float>::Matrix(const mu::Matrix<2, 2, int> &);
/* constructor (construct-from-different-typed-array) */
template mu::Matrix<2, 2, float>::Matrix(
    const std::array<mu::Vector<2, int>, 2> &);
/* constructor (construct-from-different-typed-single-value) */
template mu::Matrix<2, 2, float>::Matrix(const int &);

/********* math ********/
/* note: +=, -=, *= and /= do not have to be explicitly instantiated */
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

/********* matrix specific ********/
/* constructor (construct-from-different-typed-array-of-array) */
template mu::Matrix<2, 2, float>::Matrix(
    const std::array<std::array<int, 2>, 2> &);
