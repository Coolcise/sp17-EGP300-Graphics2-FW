#ifndef MATRIX_3_H
#define MATRIX_3_H


#ifdef __cplusplus
extern "C"
{
#endif
#include "Vector3.h"

    struct Matrix3_struct
    {
        float el[3][3];
    };

    typedef struct Matrix3_struct Matrix3;

    //Returns a 0 initialzied matrix3
    Matrix3 Matrix3_new();

    //Returns a 3x3 identity matrix
    Matrix3 Matrix3_identity();
    //Returns a 3x3 x rotation matrix
    Matrix3 Matrix3_rotationX(float angle);
    //Returns a 3x3 y rotation matrix
    Matrix3 Matrix3_rotationY(float angle);
    //Returns a 3x3 z rotation matrix
    Matrix3 Matrix3_rotationZ(float angle);

    //Scalar multiplication on the matrix
    Matrix3 Matrix3_scale(const Matrix3* matrix, float scalar);

    //Transposes the passed in matrix
    Matrix3 Matrix3_transpose(const Matrix3* matrix);

    //As we assume the matrix is a rotation matrix, 
    //the passed in matrix is transposed (𝑅−1=𝑅𝑇)
    Matrix3 Matrix3_invert(const Matrix3* matrix);

    //Returns a vector that has been rotated using a Euler XYZ rotation
    Vector3 Matrix3_rotateEulerXYZ(const Vector3* vector, float xRot, float yRot, float zRot);
    //Returns a vector that has been rotated using a Euler ZYX rotation
    Vector3 Matrix3_rotateEulerZYX(const Vector3* vector, float xRot, float yRot, float zRot);

    //Returns the result of multiplying two 3x3 matrices
    Matrix3 Matrix3_concatenate(const Matrix3* leftMatrix, const Matrix3* rightMatrix);

    //Multiply a matrix3 with a vector3
    Vector3 Matrix3_vectorMultiply(const Matrix3* matrix, const Vector3* vector);

    //(In-place)(Unseeded rand) Populates passed in matrix with random ints
    void Matrix3_random(Matrix3* matrix);

    //Prints a matrix
    void Matrix3_print(Matrix3 matrix);

#ifdef __cplusplus
}
#endif
#endif
