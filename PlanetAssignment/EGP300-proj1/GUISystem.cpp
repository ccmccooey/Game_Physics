/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  GUISystem.cpp
*
*	Description:
*		This class manages all the gui and camera associated with the gui.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "GUISystem.h"
#include "GUIButton.h"
#include "Sprite2DManager.h"
#include "Sprite2D.h"

using namespace std;

GuiSystem::GuiSystem(int windowWidth, int windowHeight)
{
	this->Initialize(windowWidth, windowHeight);
}
GuiSystem::~GuiSystem()
{
	this->Cleanup();
}

void GuiSystem::Initialize(int windowWidth, int windowHeight)
{
	//create the frustum
	mViewFrustum2D = GLFrustum();
	mViewFrustum2D.SetOrthographic((GLfloat)(0), (GLfloat)(windowWidth), (GLfloat)(0), (GLfloat)(windowHeight), -10.0f, 10.0f);
	//viewFrustum2D.SetOrthographic((GLfloat)(0), (GLfloat)(width), (GLfloat)(0), (GLfloat)(height), -10.0f, 10.0f);

	//m3dTranslationMatrix44(guiViewMatrix, (double)(-width / 2), (double)(height / 2), 0.0);
	

	//create the gui view
	m3dTranslationMatrix44(mGuiViewMatrix, (double)(-windowWidth / 2.1), (double)(windowHeight / 2.2), 0.0);
	//m3dTranslationMatrix44(guiViewMatrix, (double)(-width / 2.1), (double)(height / 2.2), 0.0);

	//create the sprite manager and add the images
	mGuiImageDirectory = "../GuiButtons/";

	mGuiSpriteManager = new Sprite2DManager();
	mGuiSpriteManager->AddSprite(mGuiImageDirectory + "PlayButton.png", "PlayButtonNormal");
	mGuiSpriteManager->AddSprite(mGuiImageDirectory + "StopButton.png", "StopButtonNormal");
	mGuiSpriteManager->AddSprite(mGuiImageDirectory + "PlayButtonHover.png", "PlayButtonHover");
	mGuiSpriteManager->AddSprite(mGuiImageDirectory + "StopButtonHover.png", "StopButtonHover");

	//create the buttons
	int size = 2;
	mGuiButtons = vector<GUIButton*>(size);
	
	

	this->AddButton(GuiButtonTypes::Play, "PlayButtonNormal", "PlayButtonHover");
	this->AddButton(GuiButtonTypes::Stop, "StopButtonNormal", "StopButtonHover");

	//mySprite = new Sprite2D("../GuiButtons/StopButton.png");

	//myMaterial = new Material(myTexture);

	//myGUIImage = new GUIImage(mySprite, 0.0f, 0.0f);
	//myGUIImage->getTransform()->SetScale(32.0f);
}

void GuiSystem::AddButton(GuiSystem::GuiButtonTypes type, const string &spriteKey)
{
	AddButton(type, spriteKey, spriteKey, spriteKey);
}
void GuiSystem::AddButton(GuiSystem::GuiButtonTypes type, const std::string &spriteNormalKey, const std::string &spriteHoverKey)
{
	AddButton(type, spriteNormalKey, spriteHoverKey, spriteNormalKey);
}
void GuiSystem::AddButton(GuiSystem::GuiButtonTypes type, const std::string &spriteNormalKey, const std::string &spriteHoverKey, const std::string &spriteSelectedKey)
{
	float startX = 0;
	float startY = 0;
	Sprite2D* spriteNormal = mGuiSpriteManager->FindSprite(spriteNormalKey);
	Sprite2D* spriteHover = mGuiSpriteManager->FindSprite(spriteHoverKey);
	Sprite2D* spriteSelected = mGuiSpriteManager->FindSprite(spriteSelectedKey);

	int index = (int)type;
	mGuiButtons[index] = new GUIButton(spriteNormal, spriteHover, spriteSelected, startX + index * 32, startY);
	//mGuiButtons[index] = new GUIImage(sprite, 2, 34);
}
void GuiSystem::Cleanup()
{
	//remove the gui buttons
	for (unsigned int i = 0; i < mGuiButtons.size(); i++)
	{
		delete mGuiButtons[i];
		mGuiButtons[i] = nullptr;
	}
	mGuiButtons.clear();

	//remove the gui sprite manager
	delete mGuiSpriteManager;
	mGuiSpriteManager = nullptr;
}

//called in main
void GuiSystem::CheckMouse(int x, int y, bool mouseDown)
{
	for (unsigned int i = 0; i < mGuiButtons.size(); i++)
	{
		mGuiButtons[i]->checkForMouseHover((float)x, (float)y);
	}
}
void GuiSystem::UpdateWindowSize(int width, int height)
{
	mViewFrustum2D.SetOrthographic((GLfloat)(-width / 2), (GLfloat)(width / 2), (GLfloat)(-height / 2), (GLfloat)(height / 2), -10.0f, 10.0f);

	//create the gui view
	m3dTranslationMatrix44(mGuiViewMatrix, (double)(-width / 2), (double)(height / 2), 0.0);
}
void GuiSystem::DrawGUI(GLShaderManager* shaderManager)
{
	const M3DMatrix44f& projection = mViewFrustum2D.GetProjectionMatrix();

	for (unsigned int i = 0; i < mGuiButtons.size(); i++)
	{
		mGuiButtons[i]->Draw(shaderManager, mGuiViewMatrix, projection);
	}
}
void GuiSystem::DrawGUI(GLShaderManager* shaderManager, M3DMatrix44f &view, const M3DMatrix44f &projection)
{
	for (unsigned int i = 0; i < mGuiButtons.size(); i++)
	{
		mGuiButtons[i]->Draw(shaderManager, view, projection);
	}
}

GuiOperationEnum GuiSystem::ReceiveOperation()
{
	GuiOperationEnum tmp = mOperation;
	mOperation = GuiOperationEnum::INVALID_OPERATION;
	return tmp;
}