/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 19, 2015
*	Filename:  Transform2D.cpp
*
*	Description:
*		This class contains transform information for 2D display objects. This class handles all of the matrix calculations. 
*		The model matrix can be obtained from the class for uses in draw functions.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Transform2D.h"


//constructors
Transform2D::Transform2D()
{
	mPosition = Vector2f();
	mRotation = 0.0f;
	mScale = Vector2f::one;
	UpdateModelMatrix();
}
Transform2D::Transform2D(const Transform2D &rhs)
{
	this->CopyTransformData(rhs);
}
Transform2D::Transform2D(const Vector2f &position)
{
	mPosition = Vector2f(position);
	mRotation = 0.0f;
	mScale = Vector2f::one;
	UpdateModelMatrix();
}
Transform2D::~Transform2D()
{

}

//important update functions for the transform
void Transform2D::UpdateModelMatrix()
{
	//load the 3 matricies
	m3dRotationMatrix44(mRotationMatrix, mRotation, 0.0, 0.0, 1.0);
	m3dTranslationMatrix44(mTranslationMatrix, mPosition.x, -mPosition.y - 8, 0.0);	
	m3dScaleMatrix44(mScalingMatrix, mScale.x, mScale.y, 1.0);
	

	//matrix multiplication
	//m3dMatrixMultiply44(mModelMatrix, mTranslationMatrix, mRotationMatrix);
	//m3dMatrixMultiply44(mModelMatrix, mScalingMatrix, mModelMatrix);

	m3dMatrixMultiply44(mModelMatrix, mTranslationMatrix, mScalingMatrix);
	//m3dMatrixMultiply44(mModelMatrix, mScalingMatrix, mTranslationMatrix); //<---------- wrong order
	m3dMatrixMultiply44(mModelMatrix, mRotationMatrix, mModelMatrix);
}

//accessors
float Transform2D::GetX() const
{
	return mPosition.x;
}
float Transform2D::GetY() const
{
	return mPosition.y;
}
float Transform2D::GetWidth() const
{
	return mScale.x;
}
float Transform2D::GetHeiht() const
{
	return mScale.y;
}
Vector2f Transform2D::GetPosition() const
{
	return mPosition;
}
float Transform2D::GetRotation() const
{
	return mRotation;
}
Vector2f Transform2D::GetScale() const
{
	return mScale;
}
M3DMatrix44f& Transform2D::GetModelMatrix()
{
	return mModelMatrix;
}

//setters
void Transform2D::SetPosition(float x, float y)
{
	mPosition.x = x;
	mPosition.y = y;
	UpdateModelMatrix();
}
void Transform2D::SetPosition(const Vector2f &position)
{
	mPosition = position;
	UpdateModelMatrix();
}
void Transform2D::SetRotation(float angle)
{
	mRotation = angle;
	UpdateModelMatrix();
}
void Transform2D::SetScale(float scaleX, float scaleY)
{
	mScale.x = scaleX;
	mScale.y = scaleY;
	UpdateModelMatrix();
}
void Transform2D::SetScale(const Vector2f &scale)
{
	mScale = scale;
	UpdateModelMatrix();
}
void Transform2D::SetScale(float scale)
{
	mScale.x = scale;
	mScale.y = scale;
	UpdateModelMatrix();
}
void Transform2D::CopyTransformData(const Transform2D &rhs)
{
	mPosition = rhs.mPosition;
	mRotation = rhs.mRotation;
	mScale = rhs.mScale;

	UpdateModelMatrix();
}

//rotations translations and scaling
void Transform2D::Translate(float x, float y)
{
	mPosition.x += x;
	mPosition.y += y;
	UpdateModelMatrix();
}
void Transform2D::Translate(const Vector2f &translation)
{
	mPosition += translation;
	UpdateModelMatrix();
}
void Transform2D::Rotate(float angle)
{
	mRotation += angle;
	UpdateModelMatrix();
}
void Transform2D::Scale(float scaleX, float scaleY)
{
	mScale.x += scaleX;
	mScale.y += scaleY;
	UpdateModelMatrix();
}
void Transform2D::Scale(const Vector2f &scale)
{
	mScale += scale;
	UpdateModelMatrix();
}
void Transform2D::Scale(float scale)
{
	mScale.x += scale;
	mScale.y += scale;
	UpdateModelMatrix();
}

//operators
Transform2D& Transform2D::operator=( const Transform2D& rhs )
{
	CopyTransformData(rhs);
	return *this;
}
bool Transform2D::operator==(const Transform2D &other) const
{
	return (mPosition == other.mPosition) && (mRotation == other.mRotation) && (mScale == other.mScale);
}
bool Transform2D::operator!=(const Transform2D &other) const
{
	return (mPosition != other.mPosition) || (mRotation != other.mRotation) || (mScale != other.mScale);
}