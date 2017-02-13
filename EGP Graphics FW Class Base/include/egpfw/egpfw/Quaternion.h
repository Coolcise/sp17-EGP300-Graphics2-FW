#pragma once

class Quaternion
{
private:
    float mX,mY,mZ,mW;

public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);

    inline float& x() { return mX; }
    inline float& y() { return mY; }
    inline float& z() { return mZ; }
    inline float& w() { return mW; }

    //Returns an identity quaternion
    Quaternion identity();
    //Returns a x rotation quaternion
    Quaternion rotationX(float angle);
    //Returns a y rotation quaternion
    Quaternion rotationY(float angle);
    //Returns a z rotation quaternion
    Quaternion rotationZ(float angle);   
    
    //Vector addition
    Quaternion add(const Quaternion& leftQuat, const Quaternion& rightQuat);
    //Vector subtraction
    Quaternion subtract(const Quaternion& leftQuat, const Quaternion& rightQuat);

    //Linear Interpolation
    Quaternion lerp(const Quaternion& leftQuat, const Quaternion& rightQuat, float time);

    //Returns magnitude of vector
    float magnitude(const Quaternion& quat);
    //Returns magnitude squared of vector
    float magnitudeSquared(const Quaternion& quat);

    //Returns dot product
    float dot(const Quaternion& leftQuat, const Quaternion& rightQuat);
    //Returns cross product
    Quaternion cross(const Quaternion& leftQuat, const Quaternion& rightQuat);

    //Scalar multiplication on the vector
    Quaternion scalarMultiply(const Quaternion& quat, float scalar);




    //(In-place)(Unseeded rand) Populates passed in vector with random ints
    Quaternion random();

    //Prints the quaternion
    void print(const Quaternion& quat);
};
