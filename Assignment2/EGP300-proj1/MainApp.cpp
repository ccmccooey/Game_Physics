#include "MainApp.h"
#include "GuiSystem.h"
#include "CameraContainer.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "GravityForceGenerator.h"
#include "Particle.h"
#include "Skybox.h"

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
	mCamera->moveCamera(0.0f, 5.0f, 30.0f);
	//mCamera->moveCamera(0.0f, 0, 0);
	//mCamera->setPosition(0.0f, 0.0f, 0.0f);

	mCameraContainer = new CameraContainer(mCamera);

	mCameraRotationSpeed = 1.0f;
	mCameraMoveSpeed = 0.75f;

	

	//gui system
	mWindowWidth = 800;
	mWindowHeight = 600;
	mGuiSystem = new GuiSystem(mWindowWidth, mWindowHeight);

	//create the physics
	mParticleSystem = new ParticleSystem();

	//create the skybox
	mSkybox = new Skybox("../OtherTextures/skybox.png");
	UpdateSkyboxPosition();

	//debug text
	mPlanetIndex = 0;
}
void MainApp::CleanUp()
{
	delete mSkybox;	
	delete mCameraContainer;
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
		if (mUpdateOnlyOnce)
		{
			mUpdateOnlyOnce = false;
			mPaused = true;
		}
		mCameraContainer->Update();
		
		
		UpdateDebugInformation();
	}
	CheckGui();

}
void MainApp::UpdateDebugInformation()
{
	std::string textOut = "";
	mGuiSystem->SetDebugText(textOut);
}

//keyboard input
void MainApp::CheckKeyboardInput(unsigned char key)
{
	if (key == 'A' || key == 'a')
	{
		mCameraContainer->Translate(-1.0f, 0.0f, 0.0f);
		//mCamera->moveCamera(-1.0f, 0.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	if (key == 'S' || key == 's')
	{
		mCameraContainer->Translate(0.0f, 0.0f, 1.0f);
		//mCamera->moveCamera(0.0f, 0.0f, -1.0f);
		UpdateSkyboxPosition();
	}
	if (key == 'D' || key == 'd')
	{
		mCameraContainer->Translate(1.0f, 0.0f, 0.0f);
		//mCamera->moveCamera(1.0f, 0.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	if (key == 'W' || key == 'w')
	{
		mCameraContainer->Translate(0.0f, 0.0f, -1.0f);
		//mCamera->moveCamera(0.0f, 0.0f, 1.0f);
		UpdateSkyboxPosition();
	}
	if (key == 'R' || key == 'r')
	{
		mCameraContainer->Translate(0.0f, 1.0f, 0.0f);
		//mCamera->moveCamera(0.0f, 1.0f, 0.0f);
		UpdateSkyboxPosition();
	}
	if (key == 'F' || key == 'f')
	{
		mCameraContainer->Translate(0.0f, -1.0f, 0.0f);
		//mCamera->moveCamera(0.0f, -1.0f, 0.0f);
		UpdateSkyboxPosition();
	}
}
void MainApp::CheckSpecialKeyboardInput(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		mCamera->rotateCameraYaw(-mCameraRotationSpeed);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		mCamera->rotateCameraYaw(mCameraRotationSpeed);
	}
	if (key == GLUT_KEY_HOME)
	{
		mCamera->rotateCameraPitch(mCameraRotationSpeed);
	}
	if (key == GLUT_KEY_END)
	{
		mCamera->rotateCameraPitch(-mCameraRotationSpeed);
	}
	if (key == GLUT_KEY_UP)
	{
		mCamera->moveCamera(mCamera->getCameraForward() * mCameraMoveSpeed);
		UpdateSkyboxPosition();
	}
	if (key == GLUT_KEY_DOWN)
	{
		float angle = mCamera->getRotationAngle();
		m3dDegToRad(angle);
		mCamera->moveCamera(mCamera->getCameraForward() * -mCameraMoveSpeed);
		UpdateSkyboxPosition();
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

	mSkybox->Draw(mDrawData);

	mGuiSystem->DrawGUI(&mShaderManager, mTextRenderer);
}

//perform operations for the gui
void MainApp::CheckGui()
{
	GuiOperationEnum operation = mGuiSystem->ReceiveOperation();

	if (operation != GuiOperationEnum::INVALID_OPERATION)
	{
		switch(operation)
		{
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