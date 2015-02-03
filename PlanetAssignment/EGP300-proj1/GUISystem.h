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

#include "GLfiles.h"
#include "GuiOperationEnum.h"
#include <vector>
#include <string>

class GuiSystem
{
private:
	//indicates how the buttons are defined
	enum GuiButtonTypes
	{
		Play = 0,
		Stop,
		Pause,
		Resume,
		Create_Cube,
		Create_Quad,
	};

private:
	GuiOperationEnum mOperation; //the current operation that was received if a player clicks a button ect...
	GLFrustum mViewFrustum2D; //using orthagraphic camera for displaying gui
	M3DMatrix44f mGuiViewMatrix; //the viewing matrix for gui

	Sprite2DManager* mGuiSpriteManager; //all the sprites for the gui are stored here
	std::string mGuiImageDirectory; //the directory of all the sprites that are associated with the gui are stored here
	std::vector<GUIButton*> mGuiButtons; //all the gui image buttons are stored here


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
	void AddButton(GuiButtonTypes type, const std::string &spriteKey);
	void AddButton(GuiButtonTypes type, const std::string &spriteNormalKey, const std::string &spriteHoverKey);
	void AddButton(GuiButtonTypes type, const std::string &spriteNormalKey, const std::string &spriteHoverKey, const std::string &spriteSelectedKey);
	void Cleanup();
};

#endif