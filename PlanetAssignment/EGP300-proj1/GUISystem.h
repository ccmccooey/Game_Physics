/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  GUISystem.h
*
*	Description:
*		This class manages all the gui and camera associated with the gui.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _GUI_SYSTEM_H
#define _GUI_SYSTEM_H

class Sprite2DManager;
class GUIButton;
class Texture;

#include "GLfiles.h"
#include "GuiOperationEnum.h"
#include <vector>
#include <string>

class GuiSystem
{
private:

private:
	GuiOperationEnum mOperation; //the current operation that was received if a player clicks a button ect...
	GLFrustum mViewFrustum2D; //using orthagraphic camera for displaying gui
	M3DMatrix44f mGuiViewMatrix; //the viewing matrix for gui

	Sprite2DManager* mGuiSpriteManager; //all the sprites for the gui are stored here
	std::string mGuiImageDirectory; //the directory of all the sprites that are associated with the gui are stored here
	std::vector<GUIButton*> mGuiButtons; //all the gui image buttons are stored here
	Texture* mSpriteSheet; //this texture is the texture for all the gui buttons
	int mRowX; //indicates the current row of the gui sprites
	int mRowY; //indicates the current column of the gui sprites

public:
	GuiSystem(int windowWidth, int windowHeight);
	~GuiSystem();

	//called in main
	void CheckMouse(int x, int y, bool mouseDown);
	void UpdateWindowSize(int windowWidth, int windowHeight);
	void DrawGUI(GLShaderManager* shaderManager);
	void DrawGUI(GLShaderManager* shaderManager, M3DMatrix44f &view, const M3DMatrix44f &projecion);

	GuiOperationEnum ReceiveOperation();

private:
	void Initialize(int windowWidth, int windowHeight);
	void AddButtonAndSprite(GuiOperationEnum type, const std::string &spriteKey, int sX, int sY, int sW, int sH); //add the button sprite asset to the sprite manager AND create the button display object, the function automatically includes the hover version of the sprite by adding 32 to the source Y data
	void AddButton(GuiOperationEnum type, const std::string &spriteKey);
	void AddButton(GuiOperationEnum type, const std::string &spriteNormalKey, const std::string &spriteHoverKey);
	void AddButton(GuiOperationEnum type, const std::string &spriteNormalKey, const std::string &spriteHoverKey, const std::string &spriteSelectedKey);
	void Cleanup();
};

#endif