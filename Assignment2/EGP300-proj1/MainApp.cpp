#include "MainApp.h"
#include "GuiSystem.h"
#include "CameraContainer.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "Model.h"
#include "GameObject.h"
#include "DisplayObject3DManager.h"
#include "GravityForceGenerator.h"
#include "Particle.h"
#include "InputSystem.h"
#include "Game.h"
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
}

//initialization and clean up
void MainApp::Initialize()
{
	//start off not being paused
	mPaused = false;
	mUpdateOnlyOnce = false; //this is true if the update happens only once

	//initial run speed of the simulation
	mRunSpeed = 1.0f;

	//stock shaders for basic 3D rendering
	mShaderManager.InitializeStockShaders();

	//create the renderer for displaying text
	mTextRenderer = new TextRenderer();

	//create the camera
	mCamera = new Camera();
	mCamera->setRotationAxis(0.0f, 1.0f, 0.0f);
	mCamera->moveCamera(0.0f, 5.0f, 30.0f);

	mCameraContainer = new CameraContainer(mCamera);

	mCameraRotationSpeed = 1.0f;
	mCameraMoveSpeed = 0.75f;

	//draw data
	mDrawData = new DrawData();
	mDrawData->textRenderer = mTextRenderer;
	mDrawData->shaderManager = &mShaderManager;

	//gui system
	mWindowWidth = 800;
	mWindowHeight = 600;
	mGuiSystem = new GuiSystem(mWindowWidth, mWindowHeight);

	//create the graphics
	mDisplayList = new DisplayObject3DManager();

	//create the physics
	mParticleSystem = new ParticleSystem();

	//create the skybox
	mSkybox = new Skybox("Content/OtherTextures/skybox.png");
	UpdateSkyboxPosition();

	//game
	//mGame = new Game(mParticleSystem, mDisplayList);
	mGame = new Game();
	mGame->LatchCameraToPlayer(mCameraContainer);

}
void MainApp::CleanUp()
{
	delete mGame;
	delete mSkybox;	
	delete mCameraContainer;
	delete mCamera;
	delete mDisplayList;
	delete mParticleSystem;
	delete mGuiSystem;
	delete mTextRenderer;
	delete mDrawData;
}

//fixed update
void MainApp::FixedUpdate(double t)
{
	if (!mPaused)
	{
		mGame->Update(t);
		mParticleSystem->FixedUpdate(mRunSpeed * t);

		if (mUpdateOnlyOnce)
		{
			mUpdateOnlyOnce = false;
			mPaused = true;
		}
		mGame->UpdateGraphicsObjects();

		mCameraContainer->Update();		
		UpdateDebugInformation();

	}
	
	CheckCameraMovement();
	CheckGui();

}
void MainApp::CheckCameraMovement()
{
	
	/*
	if (InputSystem::KeyDown('A') || InputSystem::KeyDown('a'))
	{
		mCameraContainer->Translate(-1.0f, 0.0f, 0.0f);
		//mCamera->moveCamera(-1.0f, 0.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	if (InputSystem::KeyDown('S') || InputSystem::KeyDown('s'))
	{
		mCameraContainer->Translate(0.0f, 0.0f, 1.0f);
		//mCamera->moveCamera(0.0f, 0.0f, -1.0f);
		UpdateSkyboxPosition();
	}
	if (InputSystem::KeyDown('D') || InputSystem::KeyDown('d'))
	{
		mCameraContainer->Translate(1.0f, 0.0f, 0.0f);
		//mCamera->moveCamera(1.0f, 0.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	if (InputSystem::KeyDown('W') || InputSystem::KeyDown('w'))
	{
		mCameraContainer->Translate(0.0f, 0.0f, -1.0f);
		//mCamera->moveCamera(0.0f, 0.0f, 1.0f);
		UpdateSkyboxPosition();
	}
	if (InputSystem::KeyDown('R') || InputSystem::KeyDown('r'))
	{
		mCameraContainer->Translate(0.0f, 1.0f, 0.0f);
		//mCamera->moveCamera(0.0f, 1.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	if (InputSystem::KeyDown('F') || InputSystem::KeyDown('f'))
	{
		mCameraContainer->Translate(0.0f, -1.0f, 0.0f);
		//mCamera->moveCamera(0.0f, -1.0f, 0.0f);
		UpdateSkyboxPosition();
	}*/

	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Left))
	{
		mCameraContainer->Translate(-1.0f, 0.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Right))
	{
		mCameraContainer->Translate(1.0f, 0.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Up))
	{
		mCameraContainer->Translate(0.0f, 1.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Down))
	{
		mCameraContainer->Translate(0.0f, -1.0f, 0.0f);
		UpdateSkyboxPosition();
	}

	/*
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Left))
	{
		mCamera->rotateCameraYaw(-mCameraRotationSpeed);
	}
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Right))
	{
		mCamera->rotateCameraYaw(mCameraRotationSpeed);
	}
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Home))
	{
		mCamera->rotateCameraPitch(mCameraRotationSpeed);
	}
	if (InputSystem::KeyDown(SpecialKeyCode::Key_End))
	{
		mCamera->rotateCameraPitch(-mCameraRotationSpeed);
	}
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Up))
	{
		mCamera->moveCamera(mCamera->getCameraForward() * mCameraMoveSpeed);
		UpdateSkyboxPosition();
	}
	if (InputSystem::KeyDown(SpecialKeyCode::Key_Arrow_Down))
	{
		float angle = mCamera->getRotationAngle();
		m3dDegToRad(angle);
		mCamera->moveCamera(mCamera->getCameraForward() * -mCameraMoveSpeed);
		UpdateSkyboxPosition();
	}*/
}
void MainApp::UpdateDebugInformation()
{
	std::string textOut = "";
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

	mViewFrustum3D.SetPerspective(35.0f, (float)(mWindowWidth / mWindowHeight), 1.0f, 1000.0f);

	mGuiSystem->UpdateWindowSize(mWindowWidth, mWindowHeight);
}

//render everything
void MainApp::RenderScene()
{
	M3DMatrix44f &view = mCamera->getView();
	const M3DMatrix44f &projection = mViewFrustum3D.GetProjectionMatrix();

	mDrawData->frustum = &mViewFrustum3D.GetProjectionMatrix();
	mDrawData->view = &view;

	mSkybox->Draw(mDrawData);

	mDisplayList->Draw(mDrawData);

	mGuiSystem->DrawGUI(&mShaderManager, mTextRenderer);
	//mGuiSystem->DrawGUI(&mShaderManager, mTextRenderer);
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
			break;
		case GuiOperationEnum::Stop:
			break;
		case GuiOperationEnum::Reset:
			mGame->Reset();
			break;
		case GuiOperationEnum::Help:
			break;
		case GuiOperationEnum::DebugInfo:
			break;
		default:
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
ParticleSystem* MainApp::GetPhysicsSystem()
{
	return msApplication->mParticleSystem;
}
DisplayObject3DManager* MainApp::GetGraphicsSystem()
{
	return msApplication->mDisplayList;
}