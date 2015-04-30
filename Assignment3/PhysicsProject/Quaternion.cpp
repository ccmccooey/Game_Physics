/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Quaternion.cpp
*
*	Description:
*		This class is a math class used to represent 3D rotations.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include <math.h>
#include "Quaternion.h"
#include "Matrix44f.h"
#include "GLfiles.h"
#include <sstream>

//constructors
Quaternion::Quaternion()
{	
	mW = 1.0f;
	mX = 0.0f;
	mY = 0.0f;
	mZ = 0.0f;	
	mEulerAngles = Vector3f::zero;
	mRecalculateEuler = true;
}
Quaternion::Quaternion(float w, float x, float y, float z)
{
	mW = w;
	mX = x;
	mY = y;
	mZ = z;	
	mEulerAngles = Vector3f::zero;
	mRecalculateEuler = true;
}
Quaternion::Quaternion(const Quaternion &rhs)
{
	mW = rhs.mW;
	mX = rhs.mX;
	mY = rhs.mY;
	mZ = rhs.mZ;
	mEulerAngles = rhs.mEulerAngles;
	mRecalculateEuler = false;
}

//destructor
Quaternion::~Quaternion()
{

}

//accessors
float Quaternion::getX() const
{
	return mX;
}
float Quaternion::getY() const
{
	return mY;
}
float Quaternion::getZ() const
{
	return mZ;
}
float Quaternion::getW() const
{
	return mW;
}
Vector3f Quaternion::getEulerAngles()
{	
	//calculateEulerAngles();
	return mEulerAngles;
}
void Quaternion::calculateEulerAngles()
{
	//old 1
	//heading = atan2(2*qy*qw-2*qx*qz , 1 - 2*qy2 - 2*qz2)
	//attitude = asin(2*qx*qy + 2*qz*qw) 
	//bank = atan2(2*qx*qw-2*qy*qz , 1 - 2*qx2 - 2*qz2)
	//old2
	//Vector3f angle = Vector3f();
	//return angle;

	//mEulerAngles.z = atan2f(2*mY*mW - 2*mX*mZ, 1 - 2*mY - 2 * mZ);
	//mEulerAngles.y = asinf(2*mX*mY + 2*mZ*mW); 
	//mEulerAngles.x = atan2f(2*mX*mW - 2*mY*mZ, 1 - 2*mX - 2 * mZ);

	float mult = (float)M3D_PI_DIV_180; //to radians
	//float mult = 1000.000f;
	//float mult = 1.0f;

	//FAIL 1
	//mEulerAngles.x = atan2f((2*mY*mW - 2*mX*mZ) * mult, (1 - 2*mY*mY - 2 * mZ*mZ)* mult);
	//mEulerAngles.y = asinf((2*mX*mY + 2*mZ*mW)* mult); 
	//mEulerAngles.z = atan2f((2*mX*mW - 2*mY*mZ)* mult, (1 - 2*mX*mX - 2 * mZ*mZ)* mult);

	//FAIL 2
	//mEulerAngles.x = atan2f(2 * (mY*mW + mX*mZ) * mult, (1 - 2 * (mY*mY + mZ*mZ))* mult);
	//mEulerAngles.y = asinf(2 * (mX*mY - mZ*mW) * mult);
	//mEulerAngles.z = atan2f(2 * (mX*mW + mY*mZ)* mult, (1 - 2 * (mX*mX + mZ*mZ))* mult);

	//FAIL 3
	//mEulerAngles.x = atan2f(2.0f * (mY * mW + mX * mZ) * mult, (1 - 2 * (mY*mY + mZ*mZ)) * mult);  //yaw  
	//mEulerAngles.y = asinf(2.0f * (mZ*mW - mX*mY) * mult);									  //pitch
	//mEulerAngles.z = atan2f(2.0f * (mX*mW + mY*mZ)* mult, (1 - 2 * (mX*mX + mZ*mZ)) * mult);  //roll

	mEulerAngles.x = atan2f((2*mY*mW - 2*mX*mZ) * mult, (1 - 2*mY*mY - 2 * mZ*mZ)* mult);
	mEulerAngles.y = asinf((2*mX*mY + 2*mZ*mW)* mult); 
	mEulerAngles.z = atan2f((2*mX*mW - 2*mY*mZ)* mult, (1 - 2*mX*mX - 2 * mZ*mZ)* mult);
}

//getting directional vectors
Vector3f Quaternion::getVectorForward() const
{
	return Vector3f(2.0f * (mX * mZ + mW * mY),
					2.0f * (mY * mX - mW * mX),
					1.0f - 2.0f * (mX * mX + mY * mY)
					);
}
Vector3f Quaternion::getVectorUp() const
{
	return Vector3f(2.0f * (mX * mY - mW * mZ),
					1.0f - 2.0f * (mX * mX + mZ * mZ),
					2.0f * (mY * mZ + mW * mX)
					);
}
Vector3f Quaternion::getVectorRight() const
{
	return Vector3f(1.0f - 2.0f * (mY * mY + mZ * mZ),
					2.0f * (mX * mY + mW * mZ),
					2.0f * (mX * mZ - mW * mY)
					);
}

//setters
void Quaternion::normalize()
{
	float d = mW * mW + mX * mX + mY * mY + mZ * mZ;
	if (d < FLT_EPSILON)
	{
		mW = 1.0f;
		return;
	}

	d = 1.0f / (sqrtf(d));
	mW *= d;
	mX *= d;
	mY *= d;
	mZ *= d;

	/*
	float length = this->length();

	//prevent division by zero
	if (length == 0.0f)
	{
		mW = 1.0f; 
		mX = mY = mZ = 0.0f;
	}
	else
	{
		mW /= length;
		mX /= length;
		mY /= length;
		mZ /= length;
	}*/
	calculateEulerAngles();
}

//set the rotation of the quaternion using Euler angles
void Quaternion::setEulerDeg(float x, float y, float z)
{
	setEuler((float)m3dDegToRad(x), (float)m3dDegToRad(y), (float)m3dDegToRad(z));
}
void Quaternion::setEuler(float x, float y, float z)
{
	//attempt1
	//mX = cos(x/2)*cos(y/2)*cos(z/2)+sin(x/2)*sin(y/2)*sin(z/2);
	//mY = sin(x/2)*cos(y/2)*cos(z/2)-cos(x/2)*sin(y/2)*sin(z/2);
	//mZ = cos(x/2)*sin(y/2)*cos(z/2)+sin(x/2)*cos(y/2)*sin(z/2);
	//mW = cos(x/2)*cos(y/2)*sin(z/2)-sin(x/2)*sin(y/2)*cos(z/2);

	//attempt2
	//mW = cos(x/2)*cos(y/2)*cos(z/2)+sin(x/2)*sin(y/2)*sin(z/2);
	//mX = sin(x/2)*cos(y/2)*cos(z/2)-cos(x/2)*sin(y/2)*sin(z/2);
	//mY = cos(x/2)*sin(y/2)*cos(z/2)+sin(x/2)*cos(y/2)*sin(z/2);
	//mZ = cos(x/2)*cos(y/2)*sin(z/2)-sin(x/2)*sin(y/2)*cos(z/2);

	//attempt3 (DOESNT WORK)
	/*
	Quaternion localX = Quaternion(1.0f, 0.0f, 0.0f, x);
	Quaternion localY = Quaternion(0.0f, 1.0f, 0.0f, y);
	Quaternion localZ = Quaternion(0.0f, 0.0f, 1.0f, z);
	Quaternion thiS = *this;
	thiS = thiS * localX;
	thiS = thiS * localY;
	thiS = thiS * localZ;
	setValues(thiS.getX(), thiS.getY(), thiS.getZ(), thiS.getW());
	*/

	float cos_z_2 = cosf(0.5f * z);
	float cos_y_2 = cosf(0.5f * y);
	float cos_x_2 = cosf(0.5f * x);

	float sin_z_2 = sinf(0.5f * z);
	float sin_y_2 = sinf(0.5f * y);
	float sin_x_2 = sinf(0.5f * x);

	// and now compute quaternion
	mW = cos_z_2 * cos_y_2 * cos_x_2 + sin_z_2 * sin_y_2 * sin_x_2;
	mX = cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_y_2 * cos_x_2;
	mY = cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_y_2 * sin_x_2;
	mZ = sin_z_2 * cos_y_2 * cos_x_2 - cos_z_2 * sin_y_2 * sin_x_2;

	//mEulerAngles.x = x;
	//mEulerAngles.y = y;
	//mEulerAngles.z = z;
	this->calculateEulerAngles();
}
void Quaternion::setX(float x)
{
	mX = x;
	calculateEulerAngles();
}
void Quaternion::setY(float y)
{
	mY = y;
	calculateEulerAngles();
}
void Quaternion::setZ(float z)
{
	mZ = z;
	calculateEulerAngles();
}
void Quaternion::setW(float w)
{
	mW = w;
	calculateEulerAngles();
}
void Quaternion::setValues(float x, float y, float z, float w)
{
	mX = x;
	mY = y;
	mZ = z;
	mW = w;
	calculateEulerAngles();
}

//sets the quaternion using a rotation matrix
void Quaternion::setUsingRotationMatrix(const M3DMatrix44f &matrix44)
{
	//math that is used
	//qw= sqrt(1 + m00 + m11 + m22) /2
	//qx = (m21 - m12)/( 4 *qw)
	//qy = (m02 - m20)/( 4 *qw)
	//qz = (m10 - m01)/( 4 *qw)

	float sqVal = 1.0f + matrix44[0] + matrix44[5] + matrix44[10];
	if (sqVal < 0)
	{
		throw; //shouldn't get here!
	}

	mW = sqrtf(sqVal) * 0.5f;
	mX = (matrix44[6] - matrix44[9]) / (mW * 4.0f);
	mY = (matrix44[8] - matrix44[2]) / (mW * 4.0f);
	mZ = (matrix44[1] - matrix44[4]) / (mW * 4.0f);
}

//rotations
void Quaternion::rotateByVector(const Vector3f& vector)
{
    Quaternion q(0, vector.x, vector.y, vector.z);
    (*this) *= q;
}
void Quaternion::addScaledVector(const Vector3f& vector, float scale)
{
    Quaternion q(0.0f, vector.x * scale, vector.y * scale, vector.z * scale);
    q *= (*this);

    mW += q.mW * 0.5f; //r
    mX += q.mX * 0.5f; //i
    mY += q.mY * 0.5f; //j
    mZ += q.mZ * 0.5f; //k
}

//assignment operator
Quaternion& Quaternion::operator=(const Quaternion &rhs)
{
	mW = rhs.mW;
	mX = rhs.mX;
	mY = rhs.mY;
	mZ = rhs.mZ;	
	mEulerAngles = rhs.mEulerAngles;
	return *this;
}

//math operators
const Quaternion Quaternion::operator*(const Quaternion &other) const
{
	/* //notes
	(Q1 * Q2).w = (w1w2 - x1x2 - y1y2 - z1z2)
	(Q1 * Q2).x = (w1x2 + x1w2 + y1z2 - z1y2)
	(Q1 * Q2).y = (w1y2 - x1z2 + y1w2 + z1x2)
	(Q1 * Q2).z = (w1z2 + x1y2 - y1x2 + z1w2

	float w = W*q.W - (X*q.X + Y*q.Y + Z*q.Z);
    float x = W*q.X + q.W*X + Y*q.Z - Z*q.Y;
    float y = W*q.Y + q.W*Y + Z*q.X - X*q.Z;
    float z = W*q.Z + q.W*Z + X*q.Y - Y*q.X;
	*/

	Quaternion result = Quaternion();
	result.mW = (mW * other.mW - mX * other.mX - mY * other.mY - mZ * other.mZ);
	result.mX = (mW * other.mX + mX * other.mW + mY * other.mZ - mZ * other.mY);
	result.mY = (mW * other.mY - mX * other.mZ + mY * other.mW + mZ * other.mX);
	result.mZ = (mW * other.mZ + mX * other.mY - mY * other.mX + mZ * other.mW);
	return result;
}
Quaternion& Quaternion::operator*=(const Quaternion &other)
{
	Quaternion q = *this;
    mW = q.mW * other.mW - q.mX * other.mX - q.mY * other.mY - q.mZ * other.mZ;
    mX = q.mW * other.mX + q.mX * other.mW + q.mY * other.mZ - q.mZ * other.mY;
    mY = q.mW * other.mY + q.mY * other.mW + q.mZ * other.mX - q.mX * other.mZ;
    mZ = q.mW * other.mZ + q.mZ * other.mW + q.mX * other.mY - q.mY * other.mX;
	return *this;
	
	//(*this) = (*this) * other;
	//return (*this);
}

//comparison operators
bool Quaternion::operator==(const Quaternion &other) const
{
	return (mX == other.mX && mY == other.mY && mZ == other.mZ && mW == other.mW);
}
bool Quaternion::operator!=(const Quaternion &other) const
{
	return (mX != other.mX || mY != other.mY || mZ != other.mZ || mW != other.mW);
}

//stream operator
std::ostream& operator<<(std::ostream& stream, const Quaternion& rotation)
{
	stream << ")(w " << rotation.mW << ")(y " << rotation.mY  << ")(z " << rotation.mZ << "(x " << rotation.mX << ")";
	return stream;
}
std::string Quaternion::toString() const
{
	std::ostringstream ss;
	ss << (*this);
	return ss.str();
}

//math stuff
float Quaternion::length() const
{
	return sqrt(mW * mW + mX * mX + mY * mY + mZ * mZ);
}
float Quaternion::lengthSquared() const
{
	return mW * mW + mX * mX + mY * mY + mZ * mZ;
}

//convert the quaternion to a rotation matrix for the glm graphics
void Quaternion::toRotationMatrix(M3DMatrix44f &mat) const
{
	mat[0] = 1.0f - 2.0f * mY * mY - 2.0f * mZ * mZ;
	mat[1] = 2.0f * mX * mY + 2.0f * mZ * mW;
	mat[2] = 2.0f * mX * mZ - 2.0f * mY * mW;
	mat[3] = 0.0f;
	mat[4] = 2.0f * mX * mY - 2.0f * mZ * mW;
	mat[5] = 1.0f - 2.0f * mX * mX - 2.0f * mZ * mZ;
	mat[6] = 2.0f * mZ * mY + 2.0f * mX * mW;
	mat[7] = 0.0f;
	mat[8] = 2.0f * mX * mZ + 2.0f * mY * mW;
	mat[9] = 2.0f * mZ * mY - 2.0f * mX * mW;
	mat[10] = 1.0f - 2.0f * mX * mX - 2.0f * mY * mY;
	mat[11] = 0.0f;
	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
}

//convert the quaternion to a rotation matrix for physics
void Quaternion::toRotationMatrix(Matrix44f &matrix) const
{
	matrix[0] = 1.0f - (2.0f * mY * mY + 2.0f * mZ * mZ);
	matrix[1] = 2.0f * mX * mY + 2.0f * mZ * mW;
	matrix[2] = 2.0f * mX * mZ - 2.0f * mY * mW;
	matrix[3] = 0.0f;
	matrix[4] = 2.0f * mX * mY - 2.0f * mZ * mW;
	matrix[5] = 1.0f - (2.0f * mX * mX + 2.0f * mZ * mZ);
	matrix[6] = 2.0f * mZ * mY + 2.0f * mX * mW;
	matrix[7] = 0.0f;
	matrix[8] = 2.0f * mX * mZ + 2.0f * mY * mW;
	matrix[9] = 2.0f * mZ * mY - 2.0f * mX * mW;
	matrix[10] = 1.0f - (2.0f * mX * mX + 2.0f * mY * mY);
	matrix[11] = 0.0f;
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

//these functions create a quaternion from an axis angle representation
void Quaternion::setRotation(float angle, float x, float y, float z)
{
	float s = sinf(angle * 0.5f);
	mX = x * s;
	mY = y * s;
	mZ = z * s;
	mW = cosf( angle * 0.5f );
	mRecalculateEuler = true;
}

Quaternion Quaternion::fromAxis(float Angle, float x, float y, float z) 
{ 
    float omega, s, c;
	Quaternion quat = Quaternion();
    s = sqrt(x*x + y*y + z*z);

	if (abs(s) > FLT_MIN)
    {
		c = 1.0f/s;

		x *= c;
		y *= c;
		z *= c;

		// Note: Previously was negative angle, which was incorrect.
		omega = 0.5f * Angle;
		s = sinf(omega);
	  
		quat.mX = s*x;
		quat.mY = s*y;
		quat.mZ = s*z;
		quat.mW = cosf(omega);
    }
    else
    {
		quat.mX = 0.0f;
		quat.mY = 0.0f;
		quat.mZ = 0.0f;
		quat.mW = 1.0f;
    }
    quat.normalize();
    return quat;

}
Quaternion Quaternion::inverse(const Quaternion &rhs)
{
	Quaternion inv = Quaternion();
	return inv;
}
