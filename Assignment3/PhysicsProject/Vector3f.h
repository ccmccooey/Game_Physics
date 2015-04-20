/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 14, 2015
*	Filename:  Vector3f.h
*
*	Description:
*		This is a simple math class for 3d points in space. This class uses floats. This class contains many math functions that are commonly used for 3d vectors.
*		WARNING, contains some pointless functions I added for fun of it.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _VECTOR3F_H
#define _VECTOR3F_H

class Matrix44f;

#include "GLfiles.h"
#include <ostream>

class Vector3f
{
public:
	float x;
	float y;
	float z;

public:
	Vector3f();
	Vector3f(float x);
	Vector3f(float x, float y);
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f &rhs);
	Vector3f(const Vector3f *rhs);
	Vector3f(const float xyz[3]);
	~Vector3f();

	//setters
	void Set(float x, float y, float z); //set all the values of the vector in a single line of a code

	//getters
	float getAngleY( const Vector3f& toVector );

	//operators overloads
	Vector3f& operator = ( const Vector3f& rhs );
	Vector3f& operator += ( const Vector3f& rhs );
	Vector3f& operator -= ( const Vector3f& rhs );
	Vector3f& operator *= ( const Vector3f& rhs );
	Vector3f& operator /= ( const Vector3f& rhs );
	Vector3f& operator *= ( float mult );
	Vector3f& operator /= ( float div );
	
	const Vector3f Vector3f::operator+(const Vector3f &other) const;
	const Vector3f Vector3f::operator-(const Vector3f &other) const;	
	const Vector3f Vector3f::operator*(const Vector3f &other) const;
	const Vector3f Vector3f::operator/(const Vector3f &other) const;
	const Vector3f Vector3f::operator*(float mult) const;
	const Vector3f Vector3f::operator/(float div) const;
	const Vector3f operator-() const;

	const Vector3f Vector3f::operator*(const M3DMatrix44f &matrix) const;

	bool Vector3f::operator==(const Vector3f &other) const;
	bool Vector3f::operator!=(const Vector3f &other) const;

	friend std::ostream& Vector3f::operator<<(std::ostream& stream, const Vector3f& vector);
	std::string ToString() const;
	void ToArray(float floatArray[3]);

	//math functions
	float Length() const;
	float LengthSquared() const;
	void Normalize(); //make the vector length 1
	void Lengthinize(float length); //make the vector length a specific value
	void Power(float power);
	float Average() const;
	void Abs();

	//static math functions
	static float DotProduct(const Vector3f &first, const Vector3f &second);
	static Vector3f CrossProduct(const Vector3f &first, const Vector3f &second);
	static bool AlmostEqual(const Vector3f &first, const Vector3f &second);
	static float AngleBetween(const Vector3f &firstNormal, const Vector3f &secondNormal);
	static float Distance(const Vector3f &first, const Vector3f &second);
	static float DistanceSquared(const Vector3f &first, const Vector3f &second);
	static Vector3f DirectionTo(const Vector3f &from, const Vector3f &to);
	static Vector3f Midpoint(const Vector3f &first, const Vector3f &second);
	static Vector3f Quaterpoint(const Vector3f &first, const Vector3f &second);
	static Vector3f ThreeQuaterpoint(const Vector3f &first, const Vector3f &second);
	static Vector3f Betweenpoint(const Vector3f &first, const Vector3f &second, float value); //value between 0 and 1
	static Vector3f Reciprical(const Vector3f &vector);
	static Vector3f EulerForward(float pitch, float yaw, float roll);
	static Vector3f EulerForward(const Vector3f &vector);
	static void VectorArrayToFloatArray(float floatArray[], const Vector3f *vectorArray, int vectorArraySize); //fill a float array from an array of vector3s
	static Vector3f Normalized(const Vector3f &vector);
	static Vector3f ProjectOntoVector(const Vector3f &u, const Vector3f &v);

	static Vector3f LocalToWorld(const Vector3f &local, const Matrix44f* transform);
	static Vector3f WorldToWorld(const Vector3f &world, const Matrix44f* transform);

public:
	//constant vectors
	const static Vector3f zero;
	const static Vector3f one;
	const static Vector3f unitX;
	const static Vector3f unitY;
	const static Vector3f unitZ;
	const static float EPSILON;
};

#endif

