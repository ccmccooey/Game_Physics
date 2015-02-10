/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  GUIButton.cpp
*
*	Description:
*		This class is a gui button. This class has additional functionality and can store sprites that represt hovers and selected
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/


#include "GUIButton.h"

//constructors
GUIButton::GUIButton(Sprite2D* imageNormal)
	:GUIImage(imageNormal)
{
	InitializeButton(imageNormal, imageNormal, imageNormal);
}
GUIButton::GUIButton(Sprite2D* imageNormal, float x, float y)
	:GUIImage(imageNormal, x, y)
{
	InitializeButton(imageNormal, imageNormal, imageNormal);
}
GUIButton::GUIButton(Sprite2D* imageNormal, Sprite2D* imageHover, Sprite2D* imageSelected)
	:GUIImage(imageNormal)
{
	InitializeButton(imageNormal, imageHover, imageSelected);
}
GUIButton::GUIButton(Sprite2D* imageNormal, Sprite2D* imageHover, Sprite2D* imageSelected, float x, float y)
	:GUIImage(imageNormal, x, y)
{
	InitializeButton(imageNormal, imageHover, imageSelected);
}
GUIButton::GUIButton(const GUIButton &rhs)
	:GUIImage(rhs.mSprite, rhs.mTransform->GetX(), rhs.mTransform->GetY())
{
	InitializeButton(rhs.mSpriteNormal, rhs.mSpriteHover, rhs.mSpriteSelected);
	mSelectable = rhs.mSelectable;
}
GUIButton::~GUIButton()
{
	
}
void GUIButton::InitializeButton(Sprite2D* imageNormal, Sprite2D* imageHover, Sprite2D* imageSelected)
{
	mSpriteNormal = imageNormal;
	mSpriteHover = imageHover;
	mSpriteSelected = imageSelected;

	mSelected = false;
	mSelectable = false;
	mType = GuiOperationEnum::INVALID_OPERATION;
}

//accessors
Sprite2D* GUIButton::getSpriteNormal() const
{
	return mSpriteNormal;
}
Sprite2D* GUIButton::getSpriteHover() const
{
	return mSpriteHover;
}
Sprite2D* GUIButton::getSpriteSelected() const
{
	return mSpriteSelected;
}
bool GUIButton::isSelected() const
{
	return mSelected;
}
bool GUIButton::isSelectable() const
{
	return mSelectable;
}
bool GUIButton::containsPoint(float x, float y) const
{
	return 
		(
		x > mTransform->GetX() && x < mTransform->GetWidth() + mTransform->GetX() &&
		y > mTransform->GetY() && y < mTransform->GetWidth() + mTransform->GetY()
		);
}
GuiOperationEnum GUIButton::getType() const
{
	return mType;
}
	
//setters
void GUIButton::setSelectable(bool selectable)
{
	mSelectable = selectable;
}
void GUIButton::setSpriteNormal(Sprite2D* sprite)
{
	mSpriteNormal = sprite;
}
void GUIButton::setSpriteHover(Sprite2D* sprite)
{
	mSpriteHover = sprite;
}
void GUIButton::setSpriteSelected(Sprite2D* sprite)
{
	mSpriteSelected = sprite;
}
bool GUIButton::checkForMouseHover(float mouseX, float mouseY)
{
	bool hover = false;
	if (!mSelected)
	{
		hover = containsPoint(mouseX, mouseY);
		if (hover)
			mSprite = mSpriteHover;					
		else
			mSprite = mSpriteNormal;
	}
	return hover;
}
void GUIButton::setType(GuiOperationEnum type)
{
	mType = type;
}