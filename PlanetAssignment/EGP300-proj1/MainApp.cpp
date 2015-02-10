#include "MainApp.h"
#include "GuiSystem.h"
#include "PlanetManager.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "Planet.h"
#include "GravityForceGenerator.h"
#include "RigidBody.h"

//constructor
MainApp::MainApp()
{
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
	mRunSpeed = 3.0e5;

	//stock shaders for basic 3D rendering
	mShaderManager.InitializeStockShaders();

	//create the renderer for displaying text
	mTextRenderer = new TextRenderer();

	//create the camera
	mCamera = new Camera();
	mCamera->setRotationAxis(0.0f, 1.0f, 0.0f);
	mCamera->moveCamera(0.0f, -5.0f, -20.0f);
	mCameraRotationSpeed = 1.0f;
	mCameraMoveSpeed = 0.75f;

	//gui system
	mWindowWidth = 800;
	mWindowHeight = 600;
	mGuiSystem = new GuiSystem(mWindowWidth, mWindowHeight);

	//create the physics
	mParticleSystem = new ParticleSystem();

	//create the planet manager
	mPlanetManager = new PlanetManager();
	mPlanetManager->IntializeAssets();	

	//create the draw data that is used as a parameter for most draw calls
	mDrawData = new DrawData();
	mDrawData->textRenderer = mTextRenderer;
	mDrawData->shaderManager = &mShaderManager;

	//read all the planets from a data file and add them to the manager
	bool ok;
	ok = mPlanetManager->AddPlanetList("../PlanetData/solar_system.txt");

	//add a force generator to the particle system for each planet
	if (ok)
	{
		int i;

		//add force generators for each planet
		mParticleSystem->AddGravityForceGenerator(mPlanetManager->GetPlanetAt(0)->GetRigidBody());

		//add all the rigid bodies that will be affected by physics
		int size = mPlanetManager->GetPlanetCount();
		for (i = 0; i < size; i++)
		{
			mParticleSystem->AddRigidBody(mPlanetManager->GetPlanetAt(i)->GetRigidBody());
		}
	}
}
void MainApp::CleanUp()
{
	delete mCamera;
	delete mParticleSystem;
	delete mGuiSystem;
	delete mPlanetManager;
	delete mTextRenderer;
	delete mDrawData;
}

//fixed update
void MainApp::FixedUpdate(double t)
{
	if (!mPaused)
	{
		mParticleSystem->FixedUpdate(mRunSpeed * t);
		mPlanetManager->FixedUpdate(mRunSpeed * t);
		if (mUpdateOnlyOnce)
		{
			mUpdateOnlyOnce = false;
			mPaused = true;
		}
	}
	CheckGui();
}

//keyboard input
void MainApp::CheckKeyboardInput(unsigned char key)
{
	if (key == 'A' || key == 'a')
	{
		mCamera->moveCamera(-1.0f, 0.0f, 0.0f);
	}
	if (key == 'S' || key == 's')
	{
		mCamera->moveCamera(0.0f, 0.0f, -1.0f);
	}
	if (key == 'D' || key == 'd')
	{
		mCamera->moveCamera(1.0f, 0.0f, 0.0f);
	}
	if (key == 'W' || key == 'w')
	{
		mCamera->moveCamera(0.0f, 0.0f, 1.0f);
	}
	if (key == 'R' || key == 'r')
	{
		mCamera->moveCamera(0.0f, 1.0f, 0.0f);
	}
	if (key == 'F' || key == 'f')
	{
		mCamera->moveCamera(0.0f, -1.0f, 0.0f);
	}
}
void MainApp::CheckSpecialKeyboardInput(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		mCamera->rotateCamera(-mCameraRotationSpeed);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		mCamera->rotateCamera(mCameraRotationSpeed);
	}
	if (key == GLUT_KEY_UP)
	{
		mCamera->moveCamera(mCamera->getCameraForward() * mCameraMoveSpeed);
	}
	if (key == GLUT_KEY_DOWN)
	{
		float angle = mCamera->getRotationAngle();
		m3dDegToRad(angle);
		mCamera->moveCamera(mCamera->getCameraForward() * -mCameraMoveSpeed);
	}
	if (key == GLUT_KEY_PAGE_DOWN)
	{
		mPlanetManager->BreakPoint();
	}
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

	mPlanetManager->Draw(mDrawData);

	mGuiSystem->DrawGUI(&mShaderManager);
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
			mPlanetManager->ResetAllPlanets();
			break;
		case GuiOperationEnum::SingleStep:
			mUpdateOnlyOnce = true;
			mPaused = false;
			break;
		case GuiOperationEnum::IncreaseSpeed:
			IncreaseRunSpeed(100000.0);
			break;
		case GuiOperationEnum::DecreaseSpeed:
			DecreaseRunSpeed(100000.0);
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