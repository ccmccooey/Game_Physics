/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Transform.h
*
*	Description:
*		This class contains transform information for 3D display objects. This class handles all of the matrix calculations. 
*		The model matrix can be obtained from the class for uses in draw functions.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Vector3f.h"
#include "Quaternion.h"
#include "GLfiles.h"

class Transform
{
private:

	//member types
	Vector3f mPosition;
	Quaternion mRotation;
	Vector3f mScale;

	M3DMatrix44f mRotationMatrix;
	M3DMatrix44f mTranslationMatrix;
	M3DMatrix44f mScalingMatrix;
	M3DMatrix44f mModelMatrix;

	//constructors
public:

	Transform();
	Transform(const Transform &rhs);
	Transform(const Vector3f &position);

	~Transform();

	//accessors
	Vector3f GetPosition() const;
	Quaternion GetRotation() const;
	Vector3f GetScale() const;
	M3DMatrix44f& GetModelMatrix();

	//setters
	void SetPosition(float x, float y, float z); //set the position to position xyz
	void SetPosition(const Vector3f &position);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetRotationRadians(float axisX, float axisY, float axisZ, float angle);
	void SetRotationRadians(const Vector3f &axis, float angle);
	void SetRotationDegrees(float axisX, float axisY, float axisZ, float angle);
	void SetRotationDegrees(const Vector3f &axis, float angle);
	void SetRotationRadians(float eulerX, float eulerY, float eulerZ);
	void SetRotationRadians(const Vector3f &eulerAngles);
	void SetRotationDegrees(float eulerX, float eulerY, float eulerZ);
	void SetRotationDegrees(const Vector3f &eulerAngles);
	void SetRotationIdentity();
	void SetScale(float scaleX, float scaleY, float scaleZ);
	void SetScale(const Vector3f &scale);
	void SetScale(float scale);
	void CopyTransformData(const Transform &rhs);

	//rotations translations and scaling
	void Translate(float x, float y, float z);
	void Translate(const Vector3f &translation);
	void Rotate(float axisX, float axisY, float axisZ, float angle);
	void Rotate(const Vector3f &rotation, float angle);
	void Scale(float scaleX, float scaleY, float scaleZ);
	void Scale(const Vector3f &scale);
	void Scale(float scale);

	//operators
	Transform& operator = ( const Transform& rhs );

	bool operator==(const Transform &other) const;
	bool operator!=(const Transform &other) const;

private:	
	void UpdateModelMatrix();
};

#endif