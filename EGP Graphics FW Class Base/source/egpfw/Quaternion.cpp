#include <iostream>
#include "Quaternion.h"
#include <math.h>
//#include <complex>


Quaternion::Quaternion()
{
	mI = 0.0f;
	mJ = 0.0f;
	mK = 0.0f;
	mW = 1.0f;
}

Quaternion::Quaternion(Vector3& vec)
{

}

Quaternion::Quaternion(float i, float j, float k, float w)
{
	mI = i;
	mJ = j;
	mK = k;
	mW = w;
}

Quaternion::Quaternion(Quaternion& q)
{
	mI = q.i();
	mJ = q.j();
	mK = q.k();
	mW = q.w();
}

Quaternion identity()
{
	return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion rotationX(float angle)
{
	return identity();

}

Quaternion rotationY(float angle)
{
	return identity();

}

Quaternion rotationZ(float angle)
{
	return identity();

}

Quaternion rotationXYZ(float x, float y, float z)
{
	return identity();
}

Quaternion rotationZYX(float x, float y, float z)
{
	return identity();

}

Quaternion Quaternion::add(const Quaternion& lh, const Quaternion& rh)
{
	return Quaternion(lh.mI + rh.mI,
		lh.mJ + rh.mJ,
		lh.mK + rh.mK,
		lh.mW + rh.mW);
}

Quaternion Quaternion::subtract(const Quaternion& lh, const Quaternion& rh)
{
	return Quaternion(lh.mI - rh.mI,
		lh.mJ - rh.mJ,
		lh.mK - rh.mK,
		lh.mW - rh.mW);
}

Quaternion Quaternion::multiply(const Quaternion& lh, const Quaternion& rh)
{
	Quaternion result;

	result.mI = rh.mI * lh.mI - rh.mJ * lh.mJ - rh.mK * lh.mK - rh.mW * lh.mW;
	result.mJ = rh.mI * lh.mJ + rh.mJ * lh.mI - rh.mK * lh.mW + rh.mW * lh.mK;
	result.mK = rh.mI * lh.mK + rh.mJ * lh.mW + rh.mK * lh.mI - rh.mW * lh.mJ;
	result.mW = rh.mI * lh.mW - rh.mJ * lh.mK + rh.mK * lh.mJ + rh.mW * lh.mI;

	return result;
}

Quaternion Quaternion::scalarMultiply(const Quaternion& q, float f)
{
	return Quaternion(q.mI * f, q.mJ * f, q.mK * f, q.mW * f);
}

Quaternion Quaternion::normalized(const Quaternion& q)
{
	float norm = magnitude(q);
	return Quaternion(q.mI / norm, q.mJ / norm, q.mK / norm, q.mW / norm);
}

float Quaternion::dot(const Quaternion& lh, const Quaternion& rh)
{
	return lh.mI * rh.mI + lh.mJ * rh.mJ + lh.mK * rh.mK + lh.mW * rh.mW;
}

float Quaternion::magnitudeSquare(const Quaternion& q)
{
	return q.mI * q.mI + q.mJ * q.mJ + q.mK * q.mK + q.mW * q.mW;
}

float Quaternion::magnitude(const Quaternion& quat)
{
	return sqrt(magnitudeSquare(quat));
}

Quaternion Quaternion::getConjugate(const Quaternion& q)
{
	return Quaternion(-q.mI, -q.mJ, -q.mK, q.mW);
}

Quaternion Quaternion::getInverse(const Quaternion& q)
{
	return Quaternion(-q.mI, -q.mJ, -q.mK, -q.mW);
}

//http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
Matrix3 Quaternion::toRotMatrix(const Quaternion& q)
{
	Matrix3 mat = Matrix3_new();

	mat.el[0][0] = 1 - 2 * q.mJ * q.mJ - 2 * q.mK * q.mK;
	mat.el[0][1] =     2 * q.mI * q.mJ - 2 * q.mK * q.mW;
	mat.el[0][2] =	   2 * q.mI * q.mK + 2 * q.mJ * q.mW;
	
	mat.el[1][0] =     2 * q.mI * q.mJ + 2 * q.mK * q.mW;
	mat.el[1][1] = 1 - 2 * q.mI * q.mI - 2 * q.mK * q.mK;
	mat.el[1][2] =     2 * q.mJ * q.mK - 2 * q.mI * q.mW;
	
	mat.el[2][0] =     2 * q.mI * q.mK - 2 * q.mJ * q.mW;
	mat.el[2][1] =     2 * q.mJ * q.mK + 2 * q.mI * q.mW;
	mat.el[2][2] = 1 - 2 * q.mI * q.mI - 2 * q.mJ * q.mJ;

	return mat;
}

//http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
Quaternion Quaternion::fromRotMatrix(const Matrix3& mat)
{
	Quaternion q;

	q.mW = sqrt(1 + mat.el[0][0] + mat.el[1][1] + mat.el[2][2]) / 2;
	q.mI = (mat.el[2][1] - mat.el[1][2]) / (4 * q.mW);
	q.mJ = (mat.el[0][2] - mat.el[2][0]) / (4 * q.mW);
	q.mK = (mat.el[1][0] - mat.el[0][1]) / (4 * q.mW);

	return q;
}

Quaternion Quaternion::lerp(Quaternion& start, Quaternion& end, float time)
{
	float scale = 1.0f - time;
	return Quaternion(start * scale + end * time);
}

//http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
Quaternion Quaternion::slerp(Quaternion& start, Quaternion& end, float time)
{
	//Rotation quaternions should always be normalized
	start.normalize();
	end.normalize();

	float cosHalfTheta = dot(start, end);

	//start == end or start == -end if theta is 0. If same, just return start
	if(abs(cosHalfTheta) >= 1.0f)
		return Quaternion(start);


	float halfTheta = acos(cosHalfTheta);
	float sinHalfTheta = static_cast<float>(sqrt(1.0 - cosHalfTheta * cosHalfTheta));

	//Theta is 180 deg; result is not fully defined
	if(fabs(sinHalfTheta) < 0.001)
		return Quaternion(0.5 * start + 0.5 * end);

	float ratA = sin((1 - time) * halfTheta) / sinHalfTheta;
	float ratB = sin(time * halfTheta) / sinHalfTheta;

	return Quaternion(ratA * start + ratB * end);
}

Quaternion Quaternion::operator=(const Quaternion& other)
{
	mI = other.mI;
	mJ = other.mJ;
	mK = other.mK;
	mW = other.mW;

	return *this;
}

bool Quaternion::operator==(const Quaternion& other)
{
	return (mI == other.mI && mJ == other.mJ && mK == other.mK && mW == other.mW);
}

Quaternion Quaternion::random()
{
	Quaternion result;

	result.mI = (float)(rand() % 500) - 250;
	result.mJ = (float)(rand() % 500) - 250;
	result.mK = (float)(rand() % 500) - 250;
	result.mW = (float)(rand() % 500) - 250;

	return result;
}

void Quaternion::print(const Quaternion& quat)
{
	std::cout << " " << quat.mI << " " << quat.mJ << " "
		<< quat.mK << " " << quat.mW << std::endl;
}