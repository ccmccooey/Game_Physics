/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  GUIButton.h
*
*	Description:
*		This class is a gui button. This class has additional functionality and can store sprites that represt hovers and selected
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _GUIBUTTON_H
#define _GUIBUTTON_H

class Rectangle2D;

#include "GUIImage.h"
#include "GuiOperationEnum.h"
#include <string>

class GUIButton :public GUIImage
{
private:
	Sprite2D* mSpriteNormal;
	Sprite2D* mSpriteHover;
	Sprite2D* mSpriteSelected;
	GuiOperationEnum mType;
	bool mSelectable;
	bool mSelected;
	std::string mTooltip;

public:
	GUIButton(Sprite2D* imageNormal);
	GUIButton(Sprite2D* imageNormal, float x, float y);
	GUIButton(Sprite2D* imageNormal, Sprite2D* imageHover, Sprite2D* imageSelected);
	GUIButton(Sprite2D* imageNormal, Sprite2D* imageHover, Sprite2D* imageSelected, float x, float y);
	GUIButton(const GUIButton &rhs);
	~GUIButton();

	//accessors
	Sprite2D* getSpriteNormal() const;
	Sprite2D* getSpriteHover() const;
	Sprite2D* getSpriteSelected() const;
	bool isSelected() const;
	bool isSelectable() const;
	bool containsPoint(float x, float y) const;
	GuiOperationEnum getType() const;
	std::string getTooltip() const;
	
	//setters
	void setSelectable(bool selectable);
	void setSpriteNormal(Sprite2D* sprite);
	void setSpriteHover(Sprite2D* sprite);
	void setSpriteSelected(Sprite2D* sprite);
	void setType(GuiOperationEnum type);
	void setTooltip(const std::string &tooltip);
	bool checkForMouseHover(float mouseX, float mouseY); //returns true if the mouse is over the button

private:
	void InitializeButton(Sprite2D* imageNormal, Sprite2D* imageHover, Sprite2D* imageSelected);
};


#endif