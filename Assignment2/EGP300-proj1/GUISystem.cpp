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
	int size = 5;
	mGuiButtons = vector<GUIButton*>(size);

	//declare the initial positon of the buttons
	mRowX = 0;
	mRowY = 0;

	//create all the buttons and their assets
	AddButtonAndSprite(GuiOperationEnum::Play, "PlayButton", 0, 0, 32, 32, "Play simulation");
	AddButtonAndSprite(GuiOperationEnum::Stop, "StopButton", 32, 0, 32, 32, "Pause simulation");
	AddButtonAndSprite(GuiOperationEnum::Reset, "ResetButton", 64, 0, 32, 32, "Reset simulation");
	AddButtonAndSprite(GuiOperationEnum::DebugInfo, "DebugInfoButton", 96, 0, 32, 32, "Show debug information");
	AddButtonAndSprite(GuiOperationEnum::Help, "HelpButton", 128, 0, 32, 32, "Show information about the controls and how to play");

	//debug text
	mDebugText = new TextField();
	mDebugText->SetPosition(0.0f, -400.0f, 0.0f);
	mDebugText->SetSize(12.0f);
	mDebugText->SetEolSpacing(-24.0f);
	mDrawDebugText = false;

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