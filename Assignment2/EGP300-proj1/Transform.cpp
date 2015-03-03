/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Transform.cpp
*
*	Description:
*		This class contains transform information for 3D display objects. This class handles all of the matrix calculations. 
*		The model matrix can be obtained from the class for uses in draw functions.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Transform.h"


//constructors
Transform::Transform()
{
	mPosition = Vector3f();
	mRotation = Quaternion();
	mScale = Vector3f::one;
	UpdateModelMatrix();
}
Transform::Transform(const Transform &rhs)
{
	this->CopyTransformData(rhs);
}
Transform::Transform(const Vector3f &position)
{
	mPosition = Vector3f(position);
	mRotation = Quaternion();
	mScale = Vector3f::one;
	UpdateModelMatrix();
}
Transform::~Transform()
{

}

//important update functions for the transform
void Transform::UpdateModelMatrix()
{
	//load the 3 matricies
	mRotation.toRotationMatrix(mRotationMatrix);
	m3dScaleMatrix44(mScalingMatrix, mScale.x, mScale.y, mScale.z);
	m3dTranslationMatrix44(mTranslationMatrix, mPosition.x, mPosition.y, mPosition.z);	

	//matrix multiplication
	//m3dMatrixMultiply44(mModelMatrix, mTranslationMatrix, mRotationMatrix);
	//m3dMatrixMultiply44(mModelMatrix, mScalingMatrix, mModelMatrix);
	m3dMatrixMultiply44(mModelMatrix, mRotationMatrix, mScalingMatrix);
	m3dMatrixMultiply44(mModelMatrix, mTranslationMatrix, mModelMatrix);
}

//accessors
Vector3f Transform::GetPosition() const
{
	return mPosition;
}
Quaternion Transform::GetRotation() const
{
	return mRotation;
}
Vector3f Transform::GetScale() const
{
	return mScale;
}
M3DMatrix44f& Transform::GetModelMatrix()
{
	return mModelMatrix;
}

//setters
void Transform::SetPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
	UpdateModelMatrix();
}
void Transform::SetX(float x)
{
	mPosition.x = x;
	UpdateModelMatrix();
}
void Transform::SetY(float y)
{
	mPosition.y = y;
	UpdateModelMatrix();
}
void Transform::SetZ(float z)
{
	mPosition.z = z;
	UpdateModelMatrix();
}
void Transform::SetPosition(const Vector3f &position)
{
	mPosition = position;
	UpdateModelMatrix();
}
void Transform::SetRotation(float axisX, float axisY, float axisZ, float angle)
{
	mRotation.fromAxis(angle, axisX, axisY, axisZ);
	UpdateModelMatrix();
}
void Transform::SetRotation(const Vector3f &axis, float angle)
{
	mRotation.fromAxis(angle, axis.x, axis.y, axis.z);
	UpdateModelMatrix();
}
void Transform::SetRotationIdentity()
{
	mRotation.setEulerDeg(0, 0, 0);
	UpdateModelMatrix();
}
void Transform::SetScale(float scaleX, float scaleY, float scaleZ)
{
	mScale.x = scaleX;
	mScale.y = scaleY;
	mScale.z = scaleZ;
	UpdateModelMatrix();
}
void Transform::SetScale(const Vector3f &scale)
{
	mScale = scale;
	UpdateModelMatrix();
}
void Transform::SetScale(float scale)
{
	mScale.x = scale;
	mScale.y = scale;
	mScale.z = scale;
	UpdateModelMatrix();
}
void Transform::CopyTransformData(const Transform &rhs)
{
	mPosition = rhs.mPosition;
	mRotation = rhs.mRotation;
	mScale = rhs.mScale;

	UpdateModelMatrix();
}

//rotations translations and scaling
void Transform::Translate(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
	UpdateModelMatrix();
}
void Transform::Translate(const Vector3f &translation)
{
	mPosition += translation;
	UpdateModelMatrix();
}
void Transform::Rotate(float axisX, float axisY, float axisZ, float angle)
{
	//mRotation.fromAxis(angle, axisX, axisY, axisZ);
	UpdateModelMatrix();
}
void Transform::Rotate(const Vector3f &rotation, float angle)
{
	UpdateModelMatrix();
}
void Transform::Scale(float scaleX, float scaleY, float scaleZ)
{
	mScale.x += scaleX;
	mScale.y += scaleY;
	mScale.z += scaleZ;
	UpdateModelMatrix();
}
void Transform::Scale(const Vector3f &scale)
{
	mScale += scale;
	UpdateModelMatrix();
}
void Transform::Scale(float scale)
{
	mScale.x += scale;
	mScale.y += scale;
	mScale.z += scale;
	UpdateModelMatrix();
}

//operators
Transform& Transform::operator=( const Transform& rhs )
{
	CopyTransformData(rhs);
	return *this;
}
bool Transform::operator==(const Transform &other) const
{
	return (mPosition == other.mPosition) && (mRotation == other.mRotation) && (mScale == other.mScale);
}
bool Transform::operator!=(const Transform &other) const
{
	return (mPosition != other.mPosition) || (mRotation != other.mRotation) || (mScale != other.mScale);
}