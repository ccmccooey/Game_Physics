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

class Camera
{
	//member types
private:
	
	M3DMatrix44f mRotate;
	M3DMatrix44f mTranslate;
	float mX;
	float mY;
	float mZ;
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

	//setters
	void resetEveryPossibleThing();
	void setPosition(float x, float y, float z);
	void setRotationAxis(float xRotation, float yRotation, float zRotation); //these numbers should be either 1 or 0
	void resetRotation();
	
	//movement and manipulation
	void moveCamera(float x, float y, float z);
	void rotateCamera(float amount); //uses degrees
	void doNothing(); //this function does nothing, literally nothing

private:
	void updateView();
	void reset();
};

#endif