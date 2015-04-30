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
#include "TextRenderer.h"
#include "TextField.h"

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
	mGuiImageDirectory = "Content/GuiButtons/";

	//create the texture
	mSpriteSheet = new Texture(mGuiImageDirectory + "GuiButtonSheet.png");

	//create the sprite manager
	mGuiSpriteManager = new Sprite2DManager();

	//allocate space for the buttons
	mGuiButtons = vector<GUIButton*>((unsigned int)GuiOperationEnum::TOTAL_OPERATIONS);
	
	//declare the initial positon of the buttons
	mRowX = 0;
	mRowY = 0;

	//create all the buttons and their assetss
	AddButtonAndSprite(GuiOperationEnum::Play, "PlayButton", 0, 0, 32, 32, "Play simulation");
	AddButtonAndSprite(GuiOperationEnum::Stop, "StopButton", 32, 0, 32, 32, "Pause simulation");
	AddButtonAndSprite(GuiOperationEnum::SingleStep, "SingleStep", 64, 0, 32, 32, "Take one single physics update");
	AddButtonAndSprite(GuiOperationEnum::Reset, "ResetButton", 96, 0, 32, 32, "Reset simulation");
	AddButtonAndSprite(GuiOperationEnum::DebugNext, "DebugNextButton", 128, 0, 32, 32, "Debug the next rigid body");
	AddButtonAndSprite(GuiOperationEnum::DebugInfo, "DebugInfoButton", 160, 0, 32, 32, "Show debug information");
	AddButtonAndSprite(GuiOperationEnum::Help, "HelpButton", 192, 0, 32, 32, "Move the camera with the arrow keys.\nRotate the camera by holding the left mouse button on the sides of the screen.");

	//create all the simulation specific buttons and their assets
	AddButtonAndSprite(GuiOperationEnum::Create_Sphere, "CreateSphere", 0, 64, 32, 32, "Create a sphere in front of the camera");
	AddButtonAndSprite(GuiOperationEnum::Create_Box, "CreateBox", 32, 64, 32, 32, "Create a box in front of the camera");
	AddButtonAndSprite(GuiOperationEnum::Set_Size_Small, "SetSizeSmall", 64, 64, 32, 32, "Set object size to small");
	AddButtonAndSprite(GuiOperationEnum::Set_Size_Medium, "SetSizeMedium", 96, 64, 32, 32, "Set object size to medium");
	AddButtonAndSprite(GuiOperationEnum::Set_Size_Large, "SetSizeLarge", 128, 64, 32, 32, "Set object size to large");
	AddButtonAndSprite(GuiOperationEnum::Set_Material_Airfilled, "SetMaterialAirfilled", 160, 64, 32, 32, "Set material to be air filled object");
	AddButtonAndSprite(GuiOperationEnum::Set_Material_Plastic, "SetMaterialPlastic", 192, 64, 32, 32, "Set material to be a plastic object");
	AddButtonAndSprite(GuiOperationEnum::Set_Material_Wood, "SetMaterialWood", 224, 64, 32, 32, "Set material to be a wooden object");
	AddButtonAndSprite(GuiOperationEnum::Set_Material_Steel, "SetMaterialSteel", 256, 64, 32, 32, "Set material to be a steel object");
	AddButtonAndSprite(GuiOperationEnum::Set_Material_Iron, "SetMaterialIron", 288, 64, 32, 32, "Set material to be an iron object");

	//debug text
	mDebugText = new TextField();
	mDebugText->SetPosition(0.0f, -300.0f, 0.0f);
	mDebugText->SetSize(8.0f);
	mDebugText->SetEolSpacing(-16.0f);
	mDrawDebugText = false;

	//hud text
	mHudText = new TextField();
	mHudText->SetPosition(0.0f, -40.0f, 0.0f);
	mHudText->SetSize(8.0f);
	mHudText->SetEolSpacing(-16.0f);

	//tooltip text
	mTooltip = new TextField();
	mTooltip->SetPosition(0.0f, -72.0f, 0.0f);
	mTooltip->SetSize(8.0f);
	mTooltip->SetEolSpacing(-16.0f);
}

//Add a button and a sprite using the sprite button texture, create the hover version as well by adding 32 to the sourceY
void GuiSystem::AddButtonAndSprite(GuiOperationEnum type, const std::string &spriteKey, int sX, int sY, int sW, int sH)
{
	AddButtonAndSprite(type, spriteKey, sX, sY, sW, sH, "");
}
void GuiSystem::AddButtonAndSprite(GuiOperationEnum type, const std::string &spriteKey, int sX, int sY, int sW, int sH, const std::string &tooltip)
{
	mGuiSpriteManager->AddSprite(mSpriteSheet, sX, sY, sW, sH, spriteKey + "Normal");
	mGuiSpriteManager->AddSprite(mSpriteSheet, sX, sY + sH, sW, sH, spriteKey + "Hover");
	this->AddButton(type, spriteKey + "Normal", spriteKey + "Hover");

	GUIButton* button = mGuiButtons[(int)type];
	button->setTooltip(tooltip);
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
	mGuiButtons[index] = new GUIButton(spriteNormal, spriteHover, spriteSelected, (float)mRowX, (float)mRowY);
	mGuiButtons[index]->setType(type);
	mRowX += 32;
}
void GuiSystem::Cleanup()
{
	//delete the tooltip text
	delete mTooltip;
	mTooltip = nullptr;

	//delete the hud text
	delete mHudText;
	mHudText = nullptr;

	//delete the debug text
	delete mDebugText;
	mDebugText = nullptr;

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
	bool somethingHovered = false;
	for (unsigned int i = 0; i < mGuiButtons.size(); i++)
	{
		hover = mGuiButtons[i]->checkForMouseHover((float)x, (float)y);
		if (hover)
		{
			if (clicked)
			{
				mOperation = mGuiButtons[i]->getType();
			}
			mTooltip->SetText(mGuiButtons[i]->getTooltip());
			somethingHovered = true;
		}
		else if (!somethingHovered)
		{
			mTooltip->ClearText();
		}
	}
}
void GuiSystem::UpdateWindowSize(int width, int height)
{
	mViewFrustum2D.SetOrthographic((GLfloat)(-width / 2), (GLfloat)(width / 2), (GLfloat)(-height / 2), (GLfloat)(height / 2), -10.0f, 10.0f);

	//create the gui view
	m3dTranslationMatrix44(mGuiViewMatrix, ((float)-width / 2.0f), ((float)height / 2.0f), 0.0f);
}
void GuiSystem::DrawGUI(GLShaderManager* shaderManager, TextRenderer* textRenderer)
{
	const M3DMatrix44f& projection = mViewFrustum2D.GetProjectionMatrix();

	for (unsigned int i = 0; i < mGuiButtons.size(); i++)
	{
		mGuiButtons[i]->Draw(shaderManager, mGuiViewMatrix, projection);
	}

	if (mDrawDebugText)
	{
		textRenderer->DrawTextField(mDebugText, projection, mGuiViewMatrix);
	}
	textRenderer->DrawTextField(mHudText, projection, mGuiViewMatrix);

	if (!mTooltip->IsEmptyText())
	{
		textRenderer->DrawTextField(mTooltip, projection, mGuiViewMatrix);
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



//accesors
std::string GuiSystem::GetDebugText() const
{
	return mDebugText->GetText();
}
bool GuiSystem::IsDebugTextEnabled() const
{
	return mDrawDebugText;
}

//setters
void GuiSystem::SetDebugText(const std::string &text)
{
	mDebugText->SetText(text);
}
void GuiSystem::SetHudText(const std::string &text)
{
	mHudText->SetText(text);
}
void GuiSystem::EnableDebugText()
{
	mDrawDebugText = true;
}
void GuiSystem::DisableDebugText()
{
	mDrawDebugText = false;
}
void GuiSystem::ToggleDebugText()
{
	mDrawDebugText = !mDrawDebugText;
}