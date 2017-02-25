#ifndef VECTOR_3_H
#define VECTOR_3_H

#ifdef __cplusplus
extern "C"
{
#endif

    struct Vector3_struct
    {
        float el[3];
    };

    typedef struct Vector3_struct Vector3;

    //Returns a 0 initialized vector3
    Vector3 Vector3_new();

    //Vector addition
    Vector3 Vector3_add(const Vector3* leftVector, const Vector3* rightVector);
    //Vector subtraction
    Vector3 Vector3_subtract(const Vector3* leftVector, const Vector3* rightVector);
    
    //Linear Interpolation
    Vector3 Vector3_lerp(const Vector3* leftVector, const Vector3* rightVector, float time);

    //Returns magnitude of vector
    float Vector3_magnitude(const Vector3* vector);
    //Returns magnitude squared of vector
    float Vector3_magnitudeSquared(const Vector3* vector);

    //Returns dot product
    float Vector3_dot(const Vector3* leftVector, const Vector3* rightVector);
    //Returns cross product
    Vector3 Vector3_cross(const Vector3* leftVector, const Vector3* rightVector);
    
    //Scalar multiplication on the vector
    Vector3 Vector3_scalarMultiply(const Vector3* vector, float scalar);

    //(In-place)(Unseeded rand) Populates passed in vector with random ints
    void Vector3_random(Vector3* vector);

    //Prints the vector
    void Vector3_print(Vector3 matrix);

#ifdef __cplusplus
}
#endif
#endif
