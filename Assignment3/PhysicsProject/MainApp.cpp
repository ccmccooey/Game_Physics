#include "MainApp.h"
#include "Game.h"
#include "GuiSystem.h"
#include "CameraContainer.h"
#include "Camera.h"
#include "PhysicsSystem.h"
#include "GraphicsSystem.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Skybox.h"

MainApp* MainApp::msApplication = nullptr;

//constructor
MainApp::MainApp()
{
	if (msApplication != nullptr)
	{
		throw;
	}
	msApplication = this;

	Initialize();
}
MainApp::~MainApp()
{	
	CleanUp();

	if (msApplication == this)
		msApplication = nullptr;
}

//initialization and clean up
void MainApp::Initialize()
{
	//start off not being paused
	mPaused = false;
	mUpdateOnlyOnce = false; //this is true if the update happens only once

	//initial run speed of the simulation
	mRunSpeed = 1.0f;

	//create the camera
	mCamera = new Camera();
	mCamera->setRotationAxis(0.0f, 1.0f, 0.0f);
	mCamera->moveCamera(0.0f, 20.0f, 40.0f);

	mCameraContainer = new CameraContainer(mCamera);

	mCameraRotationSpeed = 1.0f;
	mCameraMoveSpeed = 0.75f;

	//gui system
	mWindowWidth = 800;
	mWindowHeight = 600;
	mGuiSystem = new GuiSystem(mWindowWidth, mWindowHeight);

	//create the graphics
	GraphicsSystem::CreateSystem();
	mGraphicsSystem = GraphicsSystem::Instance();

	//create the physics
	mPhysicsSystem = new PhysicsSystem();

	//create the skybox
	mSkybox = new Skybox("Content/OtherTextures/skybox.png");
	UpdateSkyboxPosition();

	//game
	mGame = new Game();
	//mGame->LatchCameraToPlayer(mCameraContainer);

	mDebugInfo = false;

}
void MainApp::CleanUp()
{
	delete mGame;
	delete mSkybox;	
	delete mCameraContainer;
	delete mCamera;
	delete mGuiSystem;
	delete mPhysicsSystem;
	GraphicsSystem::DestroySystem();	
}

//fixed update
void MainApp::FixedUpdate(double t)
{
	if (!mPaused)
	{
		mGame->Update(t);
		mPhysicsSystem->FixedUpdate(mRunSpeed * t);

		if (mUpdateOnlyOnce)
		{
			mUpdateOnlyOnce = false;
			mPaused = true;
		}

		mCameraContainer->Update();

		if (mDebugInfo)
			UpdateDebugInformation();

	}
	
	CheckCameraMovement();
	CheckGui();

}
void MainApp::CheckCameraMovement()
{
	//move camera left and right
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Left))
	{
		mCameraContainer->Translate(-1.0f, 0.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	else if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Right))
	{
		mCameraContainer->Translate(1.0f, 0.0f, 0.0f);
		UpdateSkyboxPosition();
	}

	//move camera forward and back
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Up))
	{
		mCameraContainer->Translate(0.0f, 0.0f, -1.0f);
		UpdateSkyboxPosition();
	}
	else if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Down))
	{
		mCameraContainer->Translate(0.0f, 0.0f, 1.0f);
		UpdateSkyboxPosition();
	}

	//move camera down and up
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Page_Down))
	{
		mCameraContainer->Translate(0.0f, -1.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	else if (InputSystem::KeyDown(SpecialKeyCode::Key_Page_Up))
	{
		mCameraContainer->Translate(0.0f, 1.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	
	//rotate the camera if desired
	if (InputSystem::MouseButtonDown(MouseButtons::Mouse_Left))
	{
		if (InputSystem::MouseY() >= 48)
		{
			int mouseX = InputSystem::MouseX();
			if (mouseX <= (int)((float)mWindowWidth * 0.25f))
				mCamera->rotateCameraYaw(-mCameraRotationSpeed);
			else if (mouseX >= (int)((float)mWindowWidth * 0.75f))
				mCamera->rotateCameraYaw(mCameraRotationSpeed);
		}
	}
}
void MainApp::UpdateDebugInformation()
{
	std::string textOut;
	mGame->GetDebugInfo(textOut);
	mGuiSystem->SetDebugText(textOut);
}

//mouse input
void MainApp::CheckMouseInput(int x, int y, bool mouseDown, bool mouseClicked)
{
	mGuiSystem->CheckMouse(x, y, mouseDown, mouseClicked);
}

//update window size when the user resizes the window
void MainApp::UpdateWindowSize(int w, int h)
{
	mWindowWidth = w;
	mWindowHeight = h;

	mGraphicsSystem->UpdateWindowSize(mWindowWidth, mWindowHeight);

	mGuiSystem->UpdateWindowSize(mWindowWidth, mWindowHeight);
}

//render everything
void MainApp::RenderScene()
{


	mSkybox->Draw(mGraphicsSystem->GetDrawData());

	GraphicsSystem::RenderScene(mCamera);


	mGuiSystem->DrawGUI(mGraphicsSystem->GetStockShaders(), mGraphicsSystem->GetTextRenderer());
	
}

//perform operations for the gui
void MainApp::CheckGui()
{
	GuiOperationEnum operation = mGuiSystem->ReceiveOperation();

	if (operation != GuiOperationEnum::INVALID_OPERATION)
	{
		switch(operation)
		{
		case GuiOperationEnum::Play:
			mPaused = false;
			break;
		case GuiOperationEnum::Stop:
			mPaused = true;
			break;
		case GuiOperationEnum::Reset:
			mGame->Reset();
			break;
		case GuiOperationEnum::Help:
			//button does nothing, its displayed from the tooltip instead
			break;
		case GuiOperationEnum::DebugInfo:
			mGuiSystem->ToggleDebugText();
			mDebugInfo = !mDebugInfo;
			break;
		default:
			mGame->SendGuiEvent(operation);
			break;
		}
	}
}

//change the run speed of the application
void MainApp::IncreaseRunSpeed(double amount)
{
	if (amount < 0)
		amount *= -1;
	mRunSpeed += amount;
	if (mRunSpeed > 3.0e15)
	{
		mRunSpeed = 3.0e15;
	}
}
void MainApp::DecreaseRunSpeed(double amount)
{
	if (amount < 0)
		amount *= -1;
	mRunSpeed -= amount;
	if (mRunSpeed < 1000.0)
	{
		mRunSpeed = 1000.0;
	}
}

void MainApp::UpdateSkyboxPosition()
{
	mSkybox->SetPostion(Vector3f::zero);
}


//singleton accessors
MainApp* MainApp::GetApp()
{
	return msApplication;
}
PhysicsSystem* MainApp::GetPhysicsSystem()
{
	return msApplication->mPhysicsSystem;
}