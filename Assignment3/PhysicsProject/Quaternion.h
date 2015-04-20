/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Quaternion.h
*
*	Description:
*		This class is a math class used to represent 3D rotations.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _QUATERNION_H
#define _QUATERNION_H

class Matrix44f;

#include "Vector3f.h"
#include "GLfiles.h"
#include <string>

class Quaternion
{
private:
	Vector3f mEulerAngles;
	bool mRecalculateEuler;
	float mX;
	float mY;
	float mZ;
	float mW;

	void calculateEulerAngles();

public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	~Quaternion();	

	//accessors
	float getX() const;
	float getY() const;
	float getZ() const;
	float getW() const;
	Vector3f getEulerAngles();
	Vector3f getVectorForward() const;
	Vector3f getVectorUp() const;
	Vector3f getVectorRight() const;

	//setters
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setW(float w);
	void setValues(float x, float y, float z, float w);
	void setEuler(float x, float y, float z); //values are in radians
	void setEulerDeg(float x, float y, float z); //values are in degrees
	void setRotation(float AngleDegrees, float xAxis, float yAxis, float zAxis); //axis angle rotation

	//change
	void changeEuler(float x, float y, float z); //values are in radians
	void changeEulerDeg(float x, float y, float z); //values are in degrees
	

	//multiply
	void multiply(const Quaternion & rhs);
	void normalize();

	//operators
	Quaternion& Quaternion::operator=(const Quaternion &other);
	const Quaternion Quaternion::operator*(const Quaternion &other) const;
	bool Quaternion::operator==(const Quaternion &other) const;
	bool Quaternion::operator!=(const Quaternion &other) const;
	friend std::ostream& Quaternion::operator<<(std::ostream& stream, const Quaternion& rotation);
	float length();
	float lengthSquared();

	void toRotationMatrix(M3DMatrix44f &matrix); //convert the quaternion to a rotation matrix for graphics
	void toRotationMatrix(Matrix44f &matrix); //convert the quaternion to a rotation matrix for physics

	std::string toString();


	//static functions
	static Quaternion fromAxis(float Angle, float x, float y, float z);
	static Quaternion inverse(const Quaternion &rhs);
};

#endif