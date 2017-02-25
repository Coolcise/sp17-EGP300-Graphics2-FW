#include "Matrix3.h"
#include "Vector3.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//Helper function not usable outside this "class"
void swap(float* a, float* b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

Matrix3 Matrix3_new()
{
    Matrix3 newMat = { 0 };
    return newMat;
}

Matrix3 Matrix3_identity()
{
    Matrix3 identityMatrix = Matrix3_new();

    identityMatrix.el[0][0] = 1;
    identityMatrix.el[1][1] = 1;
    identityMatrix.el[2][2] = 1;

    return identityMatrix;
}

Matrix3 Matrix3_rotationX(float angle)
{
    Matrix3 rotationMatrix = Matrix3_new();
    rotationMatrix.el[0][0] = 1;
    rotationMatrix.el[1][1] = (float)cos(angle);
    rotationMatrix.el[1][2] = -(float)sin(angle);
    rotationMatrix.el[2][1] = (float)sin(angle);
    rotationMatrix.el[2][2] = (float)cos(angle);

    return rotationMatrix;
}

Matrix3 Matrix3_rotationY(float angle)
{
    Matrix3 rotationMatrix = Matrix3_new();
    rotationMatrix.el[0][0] = (float)cos(angle);
    rotationMatrix.el[0][2] = (float)sin(angle);
    rotationMatrix.el[1][1] = 1;
    rotationMatrix.el[2][0] = -(float)sin(angle);
    rotationMatrix.el[2][2] = (float)cos(angle);

    return rotationMatrix;
}

Matrix3 Matrix3_rotationZ(float angle)
{
    Matrix3 rotationMatrix = Matrix3_new();
    rotationMatrix.el[0][0] = (float)cos(angle);
    rotationMatrix.el[0][1] = -(float)sin(angle);
    rotationMatrix.el[1][0] = (float)sin(angle);
    rotationMatrix.el[1][1] = (float)cos(angle);
    rotationMatrix.el[2][2] = 1;

    return rotationMatrix;
}

Matrix3 Matrix3_scale(const Matrix3* matrix, float scalar)
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.el[i][j] = matrix->el[i][j] * scalar;

    return result;
}

Matrix3 Matrix3_transpose(const Matrix3* matrix)
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.el[i][j] = matrix->el[j][i];

    return result;
}

Matrix3 Matrix3_invert(const Matrix3* matrix)
{
    return Matrix3_transpose(matrix);
}

Matrix3 Matrix3_concatenate(const Matrix3* leftMatrix, const Matrix3* rightMatrix)
{
    Matrix3 product = Matrix3_new();

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            product.el[i][j] = leftMatrix->el[i][0] * rightMatrix->el[0][j] +
                leftMatrix->el[i][1] * rightMatrix->el[1][j] +
                leftMatrix->el[i][2] * rightMatrix->el[2][j];
        }

    return product;
}

Vector3 Matrix3_rotateEulerXYZ(const Vector3* vector, float xRot, float yRot, float zRot)
{
    Matrix3 xMat = Matrix3_rotationX(xRot);
    Matrix3 yMat = Matrix3_rotationY(yRot);
    Matrix3 zMat = Matrix3_rotationZ(zRot);

    Vector3 result = Matrix3_vectorMultiply(&zMat, vector);
    Vector3 temp = Matrix3_vectorMultiply(&yMat, &result);

    result = Matrix3_vectorMultiply(&xMat, &temp);

    return result;
}

Vector3 Matrix3_rotateEulerZYX(const Vector3* vector, float xRot, float yRot, float zRot)
{
    Matrix3 xMat = Matrix3_rotationX(xRot);
    Matrix3 yMat = Matrix3_rotationY(yRot);
    Matrix3 zMat = Matrix3_rotationZ(zRot);

    Vector3 result = Matrix3_vectorMultiply(&xMat, vector);
    Vector3 temp = Matrix3_vectorMultiply(&yMat, &result);

    result = Matrix3_vectorMultiply(&zMat, &temp);

    return result;
}

Vector3 Matrix3_vectorMultiply(const Matrix3* matrix, const Vector3* vector)
{
    Vector3 result;

    for (int i = 0; i < 3; i++)
        result.el[i] = matrix->el[i][0] * vector->el[0] +
        matrix->el[i][1] * vector->el[1] +
        matrix->el[i][2] * vector->el[2];

    return result;
}

void Matrix3_random(Matrix3* matrix)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            matrix->el[i][j] = (float)(rand() % 500);
}

void Matrix3_print(Matrix3 matrix)
{
    printf(" %.3f  %.3f  %.3f\n", matrix.el[0][0], matrix.el[0][1], matrix.el[0][2]);
    printf(" %.3f  %.3f  %.3f\n", matrix.el[1][0], matrix.el[1][1], matrix.el[1][2]);
    printf(" %.3f  %.3f  %.3f", matrix.el[2][0], matrix.el[2][1], matrix.el[2][2]);
}