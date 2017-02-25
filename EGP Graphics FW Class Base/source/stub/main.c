#include "Matrix3.h"
#include "Vector3.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv)
{    
    srand((unsigned int)time(NULL));

    Matrix3 mat = Matrix3_new();
    Matrix3_random(&mat);
    Matrix3_print(mat);
    printf("\n\n");

    Matrix3 amat = Matrix3_new();
    Matrix3_random(&amat);
    Matrix3_print(amat);
    printf("\n\n");

    Vector3 vec = Vector3_new();
    Vector3_random(&vec);
    Vector3_print(vec);
    printf("\n\n");

    Vector3 avec = Vector3_new();
    Vector3_random(&avec);
    Vector3_print(avec);
    printf("\n\n");

    //Vector3_print(Vector3_add(&vec, &avec));
    //printf("\n\n");
    //
    //Vector3_print(Vector3_subtract(&vec, &avec));
    //printf("\n\n");
    //
    //Vector3_print(Vector3_scalarMultiply(&vec, 5));
    //printf("\n\n");
    //
    //printf("%f\n\n", Vector3_dot(&vec, &avec));
    //
    //Vector3_print(Vector3_cross(&vec, &avec));
    //printf("\n\n);
    //
    //printf("%f\n\n", Vector3_magnitude(&vec));
    //
    //printf("%f\n\n", Vector3_magnitudeSquared(&vec));

    //for (float i = 0.0f; i <= 1.0f; i += 0.1f)
    //{
    //    Vector3_print(Vector3_lerp(&vec, &avec, i));
    //    printf("\n");
    //}

    Matrix3_print(Matrix3_identity());
    printf("\n\n");

    Matrix3_print(Matrix3_rotationX(3.1415927f));
    printf("\n\n");

    Matrix3_print(Matrix3_rotationY(3.1415927f));
    printf("\n\n");

    Matrix3_print(Matrix3_rotationZ(3.1415927f));
    printf("\n\n");

    Matrix3_print(Matrix3_concatenate(&mat, &amat));
    printf("\n\n");

    Vector3_print(Matrix3_vectorMultiply(&mat, &vec));
    printf("\n\n");

    Matrix3_print(Matrix3_invert(&mat));
    printf("\n\n");

    Matrix3_print(Matrix3_transpose(&mat));
    printf("\n\n");

    Matrix3_print(Matrix3_scale(&mat, 5));
    printf("\n\n");

    Vector3_print(Matrix3_rotateEulerXYZ(&vec, 3.1415927f / 4, 3.1415927f / 4, 3.1415927f / 4));
    printf("\n\n");

    Vector3_print(Matrix3_rotateEulerZYX(&vec, 3.1415927f / 4, 3.1415927f / 4, 3.1415927f / 4));
    printf("\n\n");

    printf("\n\n");
    system("pause");
    return EXIT_SUCCESS;
}
