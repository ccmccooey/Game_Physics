/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 14, 2015
*	Filename:  Vector3f.cpp
*
*	Description:
*		This is a simple math class for 3d points in space. This class uses floats. This class contains many math functions that are commonly used for 3d vectors.
*		WARNING, contains some pointless functions I added for fun of it.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Vector3f.h"
#include <sstream>
#include <math.h>
#include <string.h>

//static vectors
const Vector3f Vector3f::zero = Vector3f(0.0f, 0.0f, 0.0f);
const Vector3f Vector3f::one = Vector3f(1.0f, 1.0f, 1.0f);
const Vector3f Vector3f::unitX = Vector3f(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::unitY = Vector3f(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::unitZ = Vector3f(0.0f, 0.0f, 1.0f);
const float Vector3f::EPSILON = 0.00000001f;

//constructors
Vector3f::Vector3f()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
Vector3f::Vector3f(float X)
{
	x = X;
	y = 0.0f;
	z = 0.0f;
}
Vector3f::Vector3f(float X, float Y)
{
	x = X;
	y = Y;
	z = 0.0f;
}
Vector3f::Vector3f(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}
Vector3f::Vector3f(const Vector3f &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}
Vector3f::Vector3f(const Vector3f *rhs)
{
	x = rhs->x;
	y = rhs->y;
	z = rhs->z;
}
Vector3f::Vector3f(const float xyz[])
{
	x = xyz[0];
	y = xyz[1];
	z = xyz[2];
}

//destructor
Vector3f::~Vector3f()
{
}

//setters
void Vector3f::Set(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

//assignment operator
Vector3f& Vector3f::operator=( const Vector3f& rhs )
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

//relative operators
Vector3f& Vector3f::operator += ( const Vector3f& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}
Vector3f& Vector3f::operator -= ( const Vector3f& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
Vector3f& Vector3f::operator *= ( const Vector3f& rhs )
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}
Vector3f& Vector3f::operator /= ( const Vector3f& rhs )
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
	return *this;
}
Vector3f& Vector3f::operator *= ( float scalar )
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}
Vector3f& Vector3f::operator /= ( float scalar )
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

//math operators
const Vector3f Vector3f::operator+(const Vector3f &other) const
{
	return Vector3f(x + other.x, y + other.y, z + other.z);
}
const Vector3f Vector3f::operator-(const Vector3f &other) const
{
	return Vector3f(x - other.x, y - other.y, z - other.z);
}
const Vector3f Vector3f::operator*(const Vector3f &other) const
{
	return Vector3f(x * other.x, y * other.y, z * other.z);
}
const Vector3f Vector3f::operator/(const Vector3f &other) const
{
	return Vector3f(x / other.x, y / other.y, z / other.z);
}
const Vector3f Vector3f::operator-() const
{
	return Vector3f(x * -1, y * -1, z * -1);
}
const Vector3f Vector3f::operator*(float mult) const
{
	return Vector3f(x * mult, y * mult, z * mult);
}
const Vector3f Vector3f::operator/(float div) const
{
	return Vector3f(x / div, y / div, z / div);
}
const Vector3f Vector3f::operator*(const M3DMatrix44f &other) const
{
	//it MIGHT be this
	return Vector3f
		(
		x * other[0] + y * other[4] + z * other[8], 
		x * other[1] + y * other[5] + z * other[9],
		x * other[2] + y * other[6] + z * other[10]
		);

	//OR THIS
	return Vector3f
		(
		x * other[0] + y * other[1] + z * other[2],
		x * other[4] + y * other[5] + z * other[6],
		x * other[8] + y * other[9] + z * other[10]
		);
}

//comparison operators
bool Vector3f::operator==(const Vector3f& rhs) const
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}
bool Vector3f::operator!=(const Vector3f& rhs) const
{
	return (x != rhs.x || y != rhs.y || z != rhs.z);
}

//streaming operators
std::ostream& operator<<(std::ostream& stream, const Vector3f& vector)
{
	stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}

//to string
std::string Vector3f::ToString() const
{
	std::ostringstream ss;
	ss << (*this);
	return ss.str();
}
void Vector3f::ToArray(float floatArray[3])
{
	floatArray[0] = x;
	floatArray[1] = y;
	floatArray[2] = z;
}


//math functions
void Vector3f::Normalize()
{
	float length = this->Length();
	x /= length;
	y /= length;
	z /= length;
}
void Vector3f::Lengthinize(float value)
{
	float length = this->Length();
	x /= length * value;
	y /= length * value;
	z /= length * value;
}
float Vector3f::Length() const
{
	return sqrtf(powf(x, 2.0f) + powf(y, 2.0) + powf(z, 2.0));
}
float Vector3f::LengthSquared() const
{
	return (x * x) + (y * y) + (z * z);
}
void Vector3f::Power(float power)
{
	x = powf(x, power);
	y = powf(y, power);
	z = powf(z, power);
}
float Vector3f::Average() const
{
	return (x + y + z) / 3.0f;
}
void Vector3f::Abs()
{
	if (x < 0)
		x *= -1.0f;
	if (y < 0)
		y *= -1.0f;
	if (z < 0)
		z *= -1.0f;
}

//static math functions
float Vector3f::DotProduct(const Vector3f &first, const Vector3f &second)
{
	return first.x * second.x + first.y * second.y + first.z * second.z;
}
float Vector3f::CrossProductF(const Vector3f &first, const Vector3f &second)
{
	return (first.y * second.z - first.z - second.y) + (first.z * second.x - first.x - second.z) + (first.x * second.y - first.y - second.x);
}
Vector3f Vector3f::CrossProduct(const Vector3f &first, const Vector3f &second)
{
	return Vector3f( (first.y * second.z - first.z - second.y), (first.z * second.x - first.x - second.z), (first.x * second.y - first.y - second.x) );
}
bool Vector3f::AlmostEqual(const Vector3f &first, const Vector3f &second)
{
	return abs((first - second).LengthSquared()) <= (Vector3f::EPSILON * Vector3f::EPSILON);
}
float Vector3f::AngleBetween(const Vector3f &first, const Vector3f &second)
{
	//dot(X, Y)=|X||Y|cos(theta)
	return acosf(DotProduct(first, second) / (first.Length() * second.Length()));
}
float Vector3f::Distance(const Vector3f &first, const Vector3f &second)
{
	return sqrtf( (powf(second.x - first.x, 2.0f)) + (powf(second.y - first.y, 2.0f)) + (powf(second.z - first.z, 2.0f)));	
}
float Vector3f::DistanceSquared(const Vector3f &first, const Vector3f &second)
{
	return (powf(second.x - first.x, 2.0f)) + (powf(second.y - first.y, 2.0f)) + (powf(second.z - first.z, 2.0f));
}
Vector3f Vector3f::DirectionTo(const Vector3f &from, const Vector3f &to)
{
	Vector3f vec = from - to;
	vec.Normalize();
	return vec;
}
Vector3f Vector3f::Midpoint(const Vector3f &first, const Vector3f &second)
{
	return Vector3f((first.x + second.x) * 0.5f, (first.y + second.y) * 0.5f, (first.z + second.z) * 0.5f);
}
Vector3f Vector3f::Quaterpoint(const Vector3f &first, const Vector3f &second)
{
	return Vector3f((first.x + second.x) * 0.25f, (first.y + second.y) * 0.25f, (first.z + second.z) * 0.25f);
}
Vector3f Vector3f::ThreeQuaterpoint(const Vector3f &first, const Vector3f &second)
{
	return Vector3f((first.x + second.x) * 0.75f, (first.y + second.y) * 0.75f, (first.z + second.z) * 0.75f);
}
Vector3f Vector3f::Betweenpoint(const Vector3f &first, const Vector3f &second, float value)
{
	return Vector3f((first.x + second.x) * value, (first.y + second.y) * value, (first.z + second.z) * value);
}
Vector3f Vector3f::Reciprical(const Vector3f &vector)
{
	return Vector3f( 1.0f / vector.x, 1.0f / vector.y, 1.0f / vector.z);
}
Vector3f Vector3f::Normalized(const Vector3f &vector)
{
	Vector3f vec = Vector3f(vector);
	vec.Normalize();
	return vec;
}

void Vector3f::VectorArrayToFloatArray(float floatArray[], const Vector3f *vectorArray, int vectorArraySize)
{
	int n = 0;
	for (int i = 0; i < vectorArraySize; i++)
	{
		floatArray[n] = vectorArray[i].x;
		floatArray[n + 1] = vectorArray[i].y;
		floatArray[n + 2] = vectorArray[i].z;
		n += 3;
	}
}

//Forward vector stuff
Vector3f Vector3f::EulerForward(float pitch, float yaw, float roll)
{
	Vector3f forward = Vector3f();
	forward.z = cosf(yaw)*cosf(pitch);
	forward.x = sinf(yaw)*cosf(pitch);
	forward.y = sinf(pitch);
	return forward;
}
Vector3f Vector3f::EulerForward(const Vector3f &vector)
{
	return Vector3f::EulerForward(vector.x, vector.y, vector.z);
}