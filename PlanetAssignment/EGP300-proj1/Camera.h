/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Camera.h
*
*	Description:
*		This class contains information about a camera.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _CAMERA_H
#define _CAMERA_H

#include "GLfiles.h"
#include "Vector3f.h"
#include "Quaternion.h"

class Camera
{
	//member types
private:
	
	M3DMatrix44f mRotate;
	M3DMatrix44f mTranslate;
	Vector3f mPosition;
	Vector3f mForward;
	Quaternion mRotation;
	float mRotationX;
	float mRotationY;
	float mRotationZ;
	float mRotationAngle;

public:
	M3DMatrix44f mView;
	Camera();
	~Camera();
	//accessors
	M3DMatrix44f &getView(){return mView;};
	float getRotationAngle(){return mRotationAngle;};
	Quaternion getRotation() const;
	Vector3f getCameraForward() const;

	//setters
	void resetEveryPossibleThing();
	void setPosition(float x, float y, float z);
	void setRotationAxis(float xRotation, float yRotation, float zRotation); //these numbers should be either 1 or 0
	void SetRotation(float yaw, float pitch, float roll); //uses degrees
	void SetRotation(float axisX, float axisY, float axisZ, float angle);
	void SetRotation(const Vector3f &axis, float angle);
	void resetRotation();
	
	//movement and manipulation
	void moveCamera(float x, float y, float z);
	void moveCamera(const Vector3f &translation);
	void rotateCamera(float yawRotation); //uses degrees
	void rotateCamera(float deltaPitch, float deltaYaw, float deltaRoll);
	
	void doNothing(); //this function does nothing, literally nothing

private:
	void updateView();
	void reset();
};

#endif