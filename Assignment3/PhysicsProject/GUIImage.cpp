/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  GUIImage.cpp
*
*	Description:
*		This class defines a gui image with a 2D transform.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/


#include "GUIImage.h"

//constructors
GUIImage::GUIImage(Sprite2D* image)
{
	this->Initialize(image, 0.0f, 0.0f);
}
GUIImage::GUIImage(Sprite2D* image, float x, float y)
{
	this->Initialize(image, x, y);
}
GUIImage::GUIImage(Sprite2D* image, const Vector2f &position)
{
	this->Initialize(image, position.x, position.y);
}
GUIImage::GUIImage(const GUIImage &rhs)
{
	this->Initialize(rhs.mSprite, rhs.getX(), rhs.getY());
}
GUIImage::~GUIImage()
{
	delete mTransform;
}
void GUIImage::Initialize(Sprite2D* image, float x, float y)
{
	Vector2f position = Vector2f(x,y);
	mTransform = new Transform2D(position);
	mTransform->SetScale((float)image->getWidth(), (float)image->getHeight());
	mVisible = true;
	mSprite = image;
}

//accessors
float GUIImage::getX() const
{
	return mTransform->GetX();
}
float GUIImage::getY() const
{
	return mTransform->GetY();
}
Transform2D* GUIImage::getTransform() const
{
	return mTransform;
}
Sprite2D* GUIImage::getSprite() const
{
	return mSprite;
}
bool GUIImage::isVisible() const
{
	return mVisible;
}

//setters
void GUIImage::setSprite(Sprite2D* sprite)
{
	mSprite = sprite;
}
void GUIImage::setVisible(bool visible)
{
	mVisible = visible;
}
void GUIImage::toggleVisible()
{
	mVisible = !mVisible;
}

//draw the gui image to the frustum matrix
void GUIImage::Draw(GLShaderManager* shaderManager, const M3DMatrix44f &frustum)
{
	M3DMatrix44f view;
	m3dTranslationMatrix44(view, 0, 0, -1);
	m3dMatrixMultiply44(mSpriteViewMatrix, view, mTransform->GetModelMatrix());
	m3dMatrixMultiply44(mDrawMatrix, frustum, mSpriteViewMatrix);
	//m3dMatrixMultiply44(mDrawMatrix, frustum, mDrawMatrix);
	mSprite->Draw(shaderManager, mDrawMatrix);
}
void GUIImage::Draw(GLShaderManager* shaderManager, M3DMatrix44f &view, const M3DMatrix44f &frustum)
{
	m3dMatrixMultiply44(mSpriteViewMatrix, view, mTransform->GetModelMatrix());
	m3dMatrixMultiply44(mDrawMatrix, frustum, mSpriteViewMatrix);

	/*
	m3dMatrixMultiply44(mDrawMatrix, view, mTransform->GetModelMatrix());
	m3dMatrixMultiply44(mDrawMatrix, frustum, mDrawMatrix);*/
	mSprite->Draw(shaderManager, mDrawMatrix);

}