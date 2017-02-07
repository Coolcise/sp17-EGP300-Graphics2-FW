#include "Vector3.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

Vector3 Vector3_new()
{
    Vector3 vec = { 0 };
    return vec;
}

Vector3 Vector3_add(const Vector3* leftVector, const Vector3* rightVector)
{
    Vector3 result;

    for (int i = 0; i < 3; i++)
        result.el[i] = leftVector->el[i] + rightVector->el[i];

    return result;
}

Vector3 Vector3_subtract(const Vector3* leftVector, const Vector3* rightVector)
{
    Vector3 result = { 0 };

    for (int i = 0; i < 3; i++)
        result.el[i] = leftVector->el[i] - rightVector->el[i];

    return result;
}

Vector3 Vector3_lerp(const Vector3* leftVector, const Vector3* rightVector, float time)
{
    if (time < 0.0f || time > 1.0f)
        return Vector3_new();

    Vector3 result = Vector3_subtract(rightVector, leftVector);
    result = Vector3_scalarMultiply(&result, time);
    result = Vector3_add(leftVector, &result);

    return result;
}

float Vector3_magnitude(const Vector3* vector)
{
    return (float)sqrt(Vector3_magnitudeSquared(vector));
}

float Vector3_magnitudeSquared(const Vector3* vector)
{
    return  vector->el[0] * vector->el[0] +
        vector->el[1] * vector->el[1] +
        vector->el[2] * vector->el[2];
}

float Vector3_dot(const Vector3* leftVector, const Vector3* rightVector)
{
    return leftVector->el[0] * rightVector->el[0] +
        leftVector->el[1] * rightVector->el[1] +
        leftVector->el[2] * rightVector->el[2];
}

Vector3 Vector3_cross(const Vector3* leftVector, const Vector3* rightVector)
{
    Vector3 product;
    product.el[0] = leftVector->el[1] * rightVector->el[2] -
        leftVector->el[2] * rightVector->el[1];
    product.el[1] = leftVector->el[2] * rightVector->el[0] -
        leftVector->el[0] * rightVector->el[2];
    product.el[2] = leftVector->el[0] * rightVector->el[1] -
        leftVector->el[1] * rightVector->el[0];

    return product;
}

Vector3 Vector3_scalarMultiply(const Vector3* vector, float scalar)
{
    Vector3 result;
    for (int i = 0; i < 3; i++)
        result.el[i] = vector->el[i] * scalar;

    return result;
}

void Vector3_random(Vector3* vector)
{
    for (int i = 0; i < 3; i++)
        vector->el[i] = (float)(rand() % 500);
}

void Vector3_print(Vector3 vector)
{
    printf(" %.3f\n %.3f\n %.3f", vector.el[0], vector.el[1], vector.el[2]);
}
