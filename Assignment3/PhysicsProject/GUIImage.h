/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  GUIImage.h
*
*	Description:
*		This class defines a gui image with a 2D transform.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _GUI_IMAGE_H
#define _GUI_IMAGE_H

#include "Sprite2D.h"
#include "Transform2D.h"
#include "GLfiles.h"

class GUIImage
{
protected:
	Transform2D* mTransform;
	Sprite2D* mSprite;
	bool mVisible;
	M3DMatrix44f mSpriteViewMatrix;
	M3DMatrix44f mDrawMatrix;

private:
	void Initialize(Sprite2D* image, float x, float y);

public:
	GUIImage(Sprite2D* image);
	GUIImage(Sprite2D* image, float x, float y);
	GUIImage(Sprite2D* image, const Vector2f &position);
	GUIImage(const GUIImage &rhs);
	virtual ~GUIImage();

	//accessors
	float getX() const;
	float getY() const;
	Transform2D* getTransform() const;
	Sprite2D* getSprite() const;
	bool isVisible() const;

	//setters
	void setSprite(Sprite2D* sprite);
	void setVisible(bool visible);
	void toggleVisible();

	void Draw(GLShaderManager* shaderManager, const M3DMatrix44f &furstum);
	void Draw(GLShaderManager* shaderManager, M3DMatrix44f &view, const M3DMatrix44f &frustum);
};

#endif