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
	//set the operation to invalid
	mOperation = GuiOperationEnum::INVALID_OPERATION;

	//create the frustum
	mViewFrustum2D = GLFrustum();
	mViewFrustum2D.SetOrthographic((GLfloat)(0), (GLfloat)(windowWidth), (GLfloat)(0), (GLfloat)(windowHeight), -10.0f, 10.0f);

	//create the gui view
	m3dTranslationMatrix44(mGuiViewMatrix, ((float)-windowWidth / 2.1f), ((float)windowHeight / 2.2f), 0.0f);

	//create the image directory
	mGuiImageDirectory = "../GuiButtons/";

	//create the texture
	mSpriteSheet = new Texture(mGuiImageDirectory + "ButtonSpriteSheet.png");

	//create the sprite manager
	mGuiSpriteManager = new Sprite2DManager();

	//allocate space for the buttons
	int size = 20;
	mGuiButtons = vector<GUIButton*>(size);

	//declare the initial positon of the buttons
	mRowX = 0;
	mRowY = 0;

	//create all the buttons and their assets

	//main buttons
	AddButtonAndSprite(GuiOperationEnum::Play, "PlayButton", 0, 0, 32, 32);
	AddButtonAndSprite(GuiOperationEnum::Stop, "StopButton", 32, 0, 32, 32);
	AddButtonAndSprite(GuiOperationEnum::Reset, "ResetButton", 64, 0, 32, 32);
	AddButtonAndSprite(GuiOperationEnum::SingleStep, "SingleStepButton", 96, 0, 32, 32);
	AddButtonAndSprite(GuiOperationEnum::IncreaseSpeed, "IncreaseSpeedButton", 128, 0, 32, 32);
	AddButtonAndSprite(GuiOperationEnum::DecreaseSpeed, "DecreaseSpeedButton", 160, 0, 32, 32);
	AddButtonAndSprite(GuiOperationEnum::AddCustomPlanet, "AddCustomButton", 192, 0, 32, 32);
	AddButtonAndSprite(GuiOperationEnum::RemoveCustomPlanet, "RemoveCustomPlanetButton", 224, 0, 32, 32);
	AddButtonAndSprite(GuiOperationEnum::RemoveAllCustomPlanets, "RemoveAllCustomPlanetsButton", 256, 0, 32, 32);

	//planet buttons
	int y = 64;
	int s = 32;

	mRowX = 0;
	mRowY = 32;

	AddButtonAndSprite(GuiOperationEnum::ViewSolarSystem, "ViewSolarSystem", 32, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewMercury, "ViewMercury", 64, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewVenus, "ViewVenus", 96, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewEarth, "ViewEarth", 128, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewMars, "ViewMars", 160, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewJupiter, "ViewJupiter", 192, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewSaturn, "ViewSaturn", 224, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewUranus, "ViewUranus", 256, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewNeptune, "ViewNeptune", 288, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewPluto, "ViewPluto", 320, y, s, s);
	AddButtonAndSprite(GuiOperationEnum::ViewEris, "ViewEris", 352, y, s, s);
}

//Add a button and a sprite using the sprite button texture, create the hover version as well by adding 32 to the sourceY
void GuiSystem::AddButtonAndSprite(GuiOperationEnum type, const std::string &spriteKey, int sX, int sY, int sW, int sH)
{
	mGuiSpriteManager->AddSprite(mSpriteSheet, sX, sY, sW, sH, spriteKey + "Normal");
	mGuiSpriteManager->AddSprite(mSpriteSheet, sX, sY + sH, sW, sH, spriteKey + "Hover");
	this->AddButton(type, spriteKey + "Normal", spriteKey + "Hover");
}

//Add button display objects
void GuiSystem::AddButton(GuiOperationEnum type, const string &spriteKey)
{
	AddButton(type, spriteKey, spriteKey, spriteKey);
}
void GuiSystem::AddButton(GuiOperationEnum type, const std::string &spriteNormalKey, const std::string &spriteHoverKey)
{
	AddButton(type, spriteNormalKey, spriteHoverKey, spriteNormalKey);
}
void GuiSystem::AddButton(GuiOperationEnum type, const std::string &spriteNormalKey, const std::string &spriteHoverKey, const std::string &spriteSelectedKey)
{
	float startX = 0;
	float startY = 0;
	Sprite2D* spriteNormal = mGuiSpriteManager->FindSprite(spriteNormalKey);
	Sprite2D* spriteHover = mGuiSpriteManager->FindSprite(spriteHoverKey);
	Sprite2D* spriteSelected = mGuiSpriteManager->FindSprite(spriteSelectedKey);

	int index = (int)type;
	mGuiButtons[index] = new GUIButton(spriteNormal, spriteHover, spriteSelected, mRowX, mRowY);
	mGuiButtons[index]->setType(type);
	mRowX += 32;
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

	//remove the texture spritesheet
	delete mSpriteSheet;
	mSpriteSheet = nullptr;
}

//called in main
void GuiSystem::CheckMouse(int x, int y, bool mouseDown, bool clicked)
{
	bool hover;
	for (unsigned int i = 0; i < mGuiButtons.size(); i++)
	{
		hover = mGuiButtons[i]->checkForMouseHover((float)x, (float)y);
		if (clicked && hover)
		{
			mOperation = mGuiButtons[i]->getType();
		}
	}
}
void GuiSystem::UpdateWindowSize(int width, int height)
{
	mViewFrustum2D.SetOrthographic((GLfloat)(-width / 2), (GLfloat)(width / 2), (GLfloat)(-height / 2), (GLfloat)(height / 2), -10.0f, 10.0f);

	//create the gui view
	m3dTranslationMatrix44(mGuiViewMatrix, ((float)-width / 2.0f), ((float)height / 2.0f), 0.0f);
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