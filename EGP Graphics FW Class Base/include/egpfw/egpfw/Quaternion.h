#pragma once
#include "Vector3.h"
#include "Matrix3.h"

//Sources:
//http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm
//http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/index.htm
//http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
//http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
//http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
//https://svn.code.sf.net/p/irrlicht/code/trunk/include/quaternion.h
//https://www.mathworks.com/help/aeroblks/quaternionmultiplication.html

//TODO:
//Rotations
//Make quaternion (from Euler angles)
//Make quaternion (from other?)
//Concatenate

class Quaternion
{
private:
    float mI,mJ,mK,mW;

public:
	//Initilize as identiry
    Quaternion();
	//Copy constructor
	Quaternion(Quaternion& q);
	//Vector of Euler angles
	Quaternion(Vector3& vec);
	//Manually define
    Quaternion(float i, float j, float k, float w);

	~Quaternion(){}

    inline float& i() { return mI; }
    inline float& j() { return mJ; }
    inline float& k() { return mK; }
    inline float& w() { return mW; }

    //Returns an identity quaternion
    Quaternion identity();

    //Returns a rotation quaternion
    Quaternion rotationX(float angle);
    Quaternion rotationY(float angle);
    Quaternion rotationZ(float angle);   
	Quaternion rotationXYZ(float x, float y, float z);
	Quaternion rotationZYX(float x, float y, float z);
  
	//Arithmetic operations
	static Quaternion add(const Quaternion& lh, const Quaternion& rh);
	static Quaternion subtract(const Quaternion& lh, const Quaternion& rh);
	static Quaternion multiply(const Quaternion& lh, const Quaternion& rh);
	static Quaternion scalarMultiply(const Quaternion& q, float f);
	void scale(float f) { *this = scalarMultiply(*this, f); }

	//Normalized
	static Quaternion normalized(const Quaternion& q);
	Quaternion normalized() { return normalized(*this); }
	void normalize(Quaternion& q) { q = normalized(q); }
	void normalize() { normalize(*this); }

	//Dot product
	static float dot(const Quaternion& lh, const Quaternion& rh);
	float dot(const Quaternion& other) { return dot(*this, other); }

	//Magnitude
	static float magnitudeSquare(const Quaternion& q);
	float magnitudeSquare() { return magnitudeSquare(*this); }

	static float magnitude(const Quaternion& q);
	float magnitude() { return magnitude(*this); }

	//Conjugate
	static Quaternion getConjugate(const Quaternion& q);
	Quaternion getConjugate() { return getConjugate(*this); }

	static void makeConjugate(Quaternion& q ) { q = getConjugate(q); }
	void makeConjugate() { *this = getConjugate(*this); }

	//Inverse
	static Quaternion getInverse(const Quaternion& q);
	Quaternion getInverse() const { return getInverse(*this); }

	static void makeInverse(Quaternion& q) { q = getInverse(q); }
	void makeInverse() { *this = getInverse(*this); }

	//3D rotation matrix
	static Matrix3 toRotMatrix(const Quaternion& q);
	Matrix3 toRotMatrix() { return toRotMatrix(*this); }

	static Quaternion fromRotMatrix(const Matrix3& mat);

	//Linear interpolation (time 0 -> 1)
	static Quaternion lerp( Quaternion& start, Quaternion& end, float time);
	Quaternion lerp(Quaternion& end, float time) { lerp(*this, end, time); }

	//Spherical interpolation
	static Quaternion slerp(Quaternion& start, Quaternion& end, float time);
	Quaternion slerp(Quaternion& end, float time) { return slerp(*this, end, time); }

	//Operator overloads
	//Set
	Quaternion operator=(const Quaternion& other);

	//Is equal
	bool operator==(const Quaternion& other);

	//Add
	inline Quaternion operator+(const Quaternion& other) {	return add(*this, other);	}
	inline void operator+=(const Quaternion& other) {	*this = *this + other;	}

	//Subtract
	inline Quaternion operator-(const Quaternion& other) {	return subtract(*this, other);	}
	inline void operator-=(const Quaternion& other) { *this = *this - other; }

	//Multiply
	inline Quaternion operator*(const Quaternion& other) {	return multiply(*this, other);	}
	inline Quaternion operator*(float f) {	return scalarMultiply(*this, f);	}
	inline void operator*=(const Quaternion& other) {	*this = *this * other;	}
	inline void operator*=(float f) {	*this = *this * f;	}
	
	friend inline Quaternion operator* (float f, const Quaternion& q) { return scalarMultiply(q, f); } //added for bi-directional functionality

    //(Unseeded rand) Returns a quaternion with random values from -250 to 250
    Quaternion random();

    //Prints a quaternion
    void print(const Quaternion& quat);
	void print() { print(*this); }
};
