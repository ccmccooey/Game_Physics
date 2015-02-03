/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Camera.cpp
*
*	Description:
*		This class contains information about a camera.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Camera.h"

Camera::Camera()
{
	resetEveryPossibleThing();
}

void Camera::resetEveryPossibleThing()
{
	mX = 0.0f;
	mY = -2.0f;
	mZ = -100.0f;

	//gl
	m3dLoadIdentity44(mView);
	//m3dRotationMatrix44(mRotate, m3dDegToRad(rotateAroundViewZaxis), 0.0f, 0.0f, 1.0f);
	m3dLoadIdentity44(mRotate);
//	m3dTranslationMatrix44(mTranslate, 0.0f, -2.0f, -200.0f);
//	m3dMatrixMultiply44(mView, mRotate, mTranslate);
	mRotationAngle = 0.0f;
	mRotationX = 0.0;
	mRotationY = 1.0;
	mRotationZ = 0.0;
}

Camera::~Camera()
{

}

void Camera::updateView()
{
	m3dRotationMatrix44(mRotate, m3dDegToRad(mRotationAngle), mRotationX, mRotationY, mRotationZ);
	//m3dLoadIdentity44(mRotate);
	m3dTranslationMatrix44(mTranslate, mX, mY, mZ);
	m3dMatrixMultiply44(mView, mRotate, mTranslate);
}
void Camera::reset()
{
	mX = 0.0f;
	mY = -2.0f;
	mZ = -10.0f;
	m3dLoadIdentity44(mView);
	m3dLoadIdentity44(mRotate);
	updateView();
}

//setters
void Camera::setPosition(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
	updateView();
}

void Camera::setRotationAxis(float xAxis, float yAxis, float zAxis)
{
	mRotationX = xAxis;
	mRotationY = yAxis;
	mRotationZ = zAxis;
	updateView();
}

void Camera::resetRotation()
{
	m3dLoadIdentity44(mRotate);
	mRotationAngle = 0.0f;
	mRotationX = 0.0f;
	mRotationY = 0.0f;
	mRotationZ = 0.0f;
	updateView();
}


//movement and manipulation
void Camera::moveCamera(float x, float y, float z)
{
	mX += x;
	mY += y;
	mZ += z;
	updateView();
}
void Camera::rotateCamera(float amount)
{
	mRotationAngle += amount;
	updateView();
}

void Camera::doNothing()
{
	//does nothing
}