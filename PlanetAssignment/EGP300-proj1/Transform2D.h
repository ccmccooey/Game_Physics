/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 19, 2015
*	Filename:  Transform2D.h
*
*	Description:
*		This class contains transform information for 2D display objects. This class handles all of the matrix calculations. 
*		The model matrix can be obtained from the class for uses in draw functions.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _TRANSFORM2D_H
#define _TRANSFORM2D_H

#include "Vector2f.h"
#include "GLfiles.h"

class Transform2D
{
private:

	//member types
	Vector2f mPosition;
	float mRotation;
	Vector2f mScale;

	M3DMatrix44f mRotationMatrix;
	M3DMatrix44f mTranslationMatrix;
	M3DMatrix44f mScalingMatrix;
	M3DMatrix44f mModelMatrix;

	//constructors
public:

	Transform2D();
	Transform2D(const Transform2D &rhs);
	Transform2D(const Vector2f &position);

	~Transform2D();

	//accessors
	float GetX() const;
	float GetY() const;
	float GetWidth() const;
	float GetHeight() const;
	Vector2f GetPosition() const;
	float GetRotation() const;
	Vector2f GetScale() const;
	M3DMatrix44f& GetModelMatrix();

	//setters
	void SetPosition(float x, float y); //set the position to position xyz
	void SetPosition(const Vector2f &position);
	void SetRotation(float angle);
	void SetScale(float scaleX, float scaleY);
	void SetScale(const Vector2f &scale);
	void SetScale(float scale);
	void CopyTransformData(const Transform2D &rhs);

	//rotations translations and scaling
	void Translate(float x, float y);
	void Translate(const Vector2f &translation);
	void Rotate(float angle);
	void Scale(float scaleX, float scaleY);
	void Scale(const Vector2f &scale);
	void Scale(float scale);

	//operators
	Transform2D& operator = ( const Transform2D& rhs );

	bool operator==(const Transform2D &other) const;
	bool operator!=(const Transform2D &other) const;

private:	
	void UpdateModelMatrix();
};

#endif