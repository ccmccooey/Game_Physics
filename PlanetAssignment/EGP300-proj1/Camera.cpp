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
	//mX = 0.0f;
	//mY = -2.0f;
	//mZ = -100.0f;
	mPosition = Vector3f(0.0f, 0.0f, -10.0f);
	mRotation = Quaternion();

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

//The math is wrong HELP!
void Camera::updateView()
{
	//m3dRotationMatrix44(mRotate, m3dDegToRad(mRotationAngle), mRotationX, mRotationY, mRotationZ);
	mRotation.toRotationMatrix(mRotate);
	
	//m3dLoadIdentity44(mRotate);
	m3dTranslationMatrix44(mTranslate, mPosition.x, mPosition.y, mPosition.z);
	m3dMatrixMultiply44(mView, mRotate, mTranslate);
	//m3dMatrixMultiply44(mView, mTranslate, mRotate);
	//m3dInvertMatrix44(mView, mView);
	//gluLookAt()
}
void Camera::reset()
{
	mPosition.Set(0.0f, -2.0f, -10.0f);
	m3dLoadIdentity44(mView);
	m3dLoadIdentity44(mRotate);
	updateView();
}

//setters
void Camera::setPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
	updateView();
}
void Camera::SetRotation(float yaw, float pitch, float roll) //uses degrees
{
	mRotation.setEulerDeg(pitch, yaw, roll);
	updateView();
}
void Camera::SetRotation(float axisX, float axisY, float axisZ, float angle)
{
	mRotation = mRotation.fromAxis(angle, axisX, axisY, axisZ);
	updateView();
}
void Camera::SetRotation(const Vector3f &axis, float angle)
{
	mRotation = mRotation.fromAxis(angle, axis.x, axis.y, axis.z);
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
	mRotation = Quaternion();
	mRotationAngle = 0.0f;
	mRotationX = 0.0f;
	mRotationY = 0.0f;
	mRotationZ = 0.0f;
	updateView();
	
}


//movement and manipulation
void Camera::moveCamera(float x, float y, float z)
{
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
	updateView();
}
void Camera::moveCamera(const Vector3f &translation)
{
	mPosition += translation;
	updateView();
}
void Camera::rotateCamera(float amount)
{
	mRotationAngle += amount;
	mRotation.setEulerDeg(0.0f, mRotationAngle, 0.0f);
	updateView();
}
void Camera::rotateCamera(float deltaYaw, float deltaPitch, float deltaRoll)
{
	Vector3f euler = mRotation.getEulerAngles();
	mRotation.setEulerDeg(euler.x + deltaPitch, euler.y + deltaYaw, euler.z + deltaRoll);
	updateView();
}

void Camera::doNothing()
{
	//does nothing
}