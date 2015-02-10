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
	mForward = Vector3f::unitZ;

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

//accessors
Quaternion Camera::getRotation() const
{
	return mRotation;
}
Vector3f Camera::getCameraForward() const
{
	return mForward;
}
Vector3f Camera::getPosition() const
{
	return mPosition;
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
	mPosition.Set(0.0f, 0.0f, -10.0f);
	m3dLoadIdentity44(mView);
	m3dLoadIdentity44(mRotate);
	mForward = mRotation.getVectorForward();
	updateView();
}

//setters
void Camera::setPosition(float x, float y, float z)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
	mForward = mRotation.getVectorForward();
	updateView();
}
void Camera::SetRotation(float yaw, float pitch, float roll) //uses degrees
{
	mRotation.setEulerDeg(pitch, yaw, roll);
	mForward = mRotation.getVectorForward();
	updateView();
}
void Camera::SetRotation(float axisX, float axisY, float axisZ, float angle)
{
	mRotation = mRotation.fromAxis(angle, axisX, axisY, axisZ);
	mForward = mRotation.getVectorForward();
	updateView();
}
void Camera::SetRotation(const Vector3f &axis, float angle)
{
	mRotation = mRotation.fromAxis(angle, axis.x, axis.y, axis.z);
	mForward = mRotation.getVectorForward();
	updateView();
}
void Camera::setRotationAxis(float xAxis, float yAxis, float zAxis)
{
	mRotationX = xAxis;
	mRotationY = yAxis;
	mRotationZ = zAxis;
	mForward = mRotation.getVectorForward();
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
	mForward = mRotation.getVectorForward();
	updateView();
}


//movement functions
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

//rotation functions
void Camera::rotateCamera(float amount) //rotate on y axis
{
	mRotationAngle += amount;
	mRotation.setEulerDeg(0.0f, mRotationAngle, 0.0f);
	mRotation = mRotation.fromAxis(mRotationAngle * m3dDegToRad(amount), 0.0f, 1.0f, 0.0f);
	mRotation.setEulerDeg(mRotationAngle, 0.0f, 0.0f);
	mForward = mRotation.getVectorForward();
	updateView();
}
void Camera::rotateCamera(float deltaPitch, float deltaYaw, float deltaRoll) //rotate on all axis
{
	//Vector3f euler = mRotation.getEulerAngles();
	//euler.x = m3dRadToDeg(euler.x);
	//euler.y = m3dRadToDeg(euler.y);
	//euler.z = m3dRadToDeg(euler.z);
	//mRotation.setEulerDeg(euler.x + deltaPitch, euler.y + deltaYaw, euler.z + deltaRoll);
	//euler = mRotation.getEulerAngles();

	Vector3f euler = mRotation.getEulerAngles();
	mRotation.setEuler(euler.x, euler.y + m3dDegToRad(deltaYaw), euler.z);

	mForward = mRotation.getVectorForward();
	updateView();
}

void Camera::doNothing()
{
	//does nothing
}