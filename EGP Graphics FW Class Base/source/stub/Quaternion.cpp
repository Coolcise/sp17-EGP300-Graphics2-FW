#include "Quaternion.h"
#include "random"
#include <iostream>

Quaternion::Quaternion()
{
    mX = mY = mZ = mW = 0.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    mX = x;
    mY = y;
    mZ = z;
    mW = w;
}

Quaternion identity()
{
    
}

Quaternion rotationX(float angle)
{
    
}

Quaternion rotationY(float angle)
{
    
}

Quaternion rotationZ(float angle)
{
    
}

Quaternion Quaternion::add(const Quaternion& leftQuat, const Quaternion& rightQuat)
{
    Quaternion result;

    result.mX = leftQuat.mX + rightQuat.mX;
    result.mY = leftQuat.mY + rightQuat.mY;
    result.mZ = leftQuat.mZ + rightQuat.mZ;
    result.mW = leftQuat.mW + rightQuat.mW;

    return result;
}

Quaternion Quaternion::subtract(const Quaternion& leftQuat, const Quaternion& rightQuat)
{
    Quaternion result;

    result.mX = leftQuat.mX - rightQuat.mX;
    result.mY = leftQuat.mY - rightQuat.mY;
    result.mZ = leftQuat.mZ - rightQuat.mZ;
    result.mW = leftQuat.mW - rightQuat.mW;

    return result;
}

Quaternion Quaternion::lerp(const Quaternion& leftQuat, const Quaternion& rightQuat, float time)
{
    if (time < 0.0f || time > 1.0f)
        return Quaternion();

    Quaternion result = subtract(rightQuat, leftQuat);
    result = scalarMultiply(result, time);
    result = add(leftQuat, result);

    return result;
}

float Quaternion::magnitude(const Quaternion& quat)
{
    return static_cast<float>(sqrt(magnitudeSquared(quat)));
}

float Quaternion::magnitudeSquared(const Quaternion& quat)
{
    return  quat.mX * quat.mX +
        quat.mY * quat.mY +
        quat.mZ * quat.mZ +
        quat.mW * quat.mW;
}

float Quaternion::dot(const Quaternion& leftQuat, const Quaternion& rightQuat)
{
    return leftQuat.mX * rightQuat.mX +
        leftQuat.mY * rightQuat.mY +
        leftQuat.mZ * rightQuat.mZ +
        leftQuat.mW * rightQuat.mW;
}

//Quaternion Quaternion::cross(const Quaternion* leftQuat, const Quaternion* rightQuat)
//{
//    Quaternion product;
//
//
//    return product;
//}

Quaternion Quaternion::scalarMultiply(const Quaternion& quat, float scalar)
{
    Quaternion result;

    result.mX = quat.mX * scalar;
    result.mY = quat.mY * scalar;
    result.mZ = quat.mZ * scalar;
    result.mW = quat.mW * scalar;

    return result;
}

Quaternion Quaternion::random()
{
    Quaternion result;

    result.mX = (float)(rand() % 500);
    result.mY = (float)(rand() % 500);
    result.mZ = (float)(rand() % 500);
    result.mW = (float)(rand() % 500);
    
    return result;
}

void Quaternion::print(const Quaternion& quat)
{
    std::cout << " " << quat.mX << " " << quat.mY << " "
        << quat.mZ << " " << quat.mW << std::endl;
}