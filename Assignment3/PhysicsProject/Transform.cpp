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
#include "Matrix44f.h"

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

	//m3dMatrixMultiply44(mModelMatrix, mScalingMatrix ,mRotationMatrix);
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

//rotation euler angles
void Transform::SetRotationRadians(float eulerX, float eulerY, float eulerZ)
{
	mRotation.setEuler(eulerX, eulerY, eulerZ);
	UpdateModelMatrix();
}
void Transform::SetRotationRadians(const Vector3f &eulerAngles)
{
	mRotation.setEuler(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	UpdateModelMatrix();
}
void Transform::SetRotationDegrees(float eulerX, float eulerY, float eulerZ)
{
	mRotation.setEulerDeg(eulerX, eulerY, eulerZ);
	UpdateModelMatrix();
}
void Transform::SetRotationDegrees(const Vector3f &eulerAngles)
{
	mRotation.setEulerDeg(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	UpdateModelMatrix();
}

//rotation axis angle
void Transform::SetRotationRadians(float axisX, float axisY, float axisZ, float angle)
{
	mRotation = mRotation.fromAxis(angle, axisX, axisY, axisZ);
	UpdateModelMatrix();
}
void Transform::SetRotationRadians(const Vector3f &axis, float angle)
{
	mRotation = mRotation.fromAxis(angle, axis.x, axis.y, axis.z);
	UpdateModelMatrix();
}
void Transform::SetRotationDegrees(float axisX, float axisY, float axisZ, float angle)
{
	mRotation = mRotation.fromAxis(angle * 0.0174532925199432957f, axisX, axisY, axisZ);
	UpdateModelMatrix();
}
void Transform::SetRotationDegrees(const Vector3f &axis, float angle)
{
	mRotation = mRotation.fromAxis(angle * 0.0174532925199432957f, axis.x, axis.y, axis.z);
	UpdateModelMatrix();
}

//reset rotation
void Transform::SetRotationIdentity()
{
	mRotation.setEuler(0, 0, 0);
	UpdateModelMatrix();
}

//scaling
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
void Transform::SetTransformRT(const Matrix44f &matrix)
{
	mModelMatrix[0] = matrix[0]; mModelMatrix[1] = matrix[1]; mModelMatrix[2] = matrix[2]; mModelMatrix[3] = matrix[3];
	mModelMatrix[4] = matrix[4]; mModelMatrix[5] = matrix[5]; mModelMatrix[6] = matrix[6]; mModelMatrix[7] = matrix[7];
	mModelMatrix[8] = matrix[8]; mModelMatrix[9] = matrix[9]; mModelMatrix[10] = matrix[10]; mModelMatrix[11] = matrix[11];
	mModelMatrix[12] = matrix[12]; mModelMatrix[13] = matrix[13]; mModelMatrix[14] = matrix[14]; mModelMatrix[15] = matrix[15];

	mPosition.x = mModelMatrix[3];
	mPosition.y = mModelMatrix[7];
	mPosition.z = mModelMatrix[11];

	mRotation.setUsingRotationMatrix(mModelMatrix);

	mScale = Vector3f::one;

	UpdateModelMatrix();
}
void Transform::SetTransformData(const Vector3f &position, const Quaternion &rotation, const Vector3f &scale)
{
	mPosition = position;
	mRotation = rotation;
	mScale = scale;
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