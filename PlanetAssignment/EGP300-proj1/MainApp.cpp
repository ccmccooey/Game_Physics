#include "MainApp.h"
#include "GuiSystem.h"
#include "PlanetManager.h"
#include "CameraContainer.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "Planet.h"
#include "GravityForceGenerator.h"
#include "RigidBody.h"
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
		//mParticleSystem->AddGravityForceGenerator(mPlanetManager->GetPlanetAt(0)->GetRigidBody());

		//add all the rigid bodies that will be affected by physics
		int size = mPlanetManager->GetPlanetCount();
		for (i = 0; i < size; i++)
		{
			mParticleSystem->AddGravityForceGenerator(mPlanetManager->GetPlanetAt(i)->GetRigidBody());
			mParticleSystem->AddRigidBody(mPlanetManager->GetPlanetAt(i)->GetRigidBody());
		}
	}

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
		mPlanetManager->FixedUpdate(mRunSpeed * t);
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
	mPlanetManager->GetPlanetAt(mPlanetIndex)->GetDebugInfo(textOut);
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
		case GuiOperationEnum::ToggleDebugInformation:
			mGuiSystem->ToggleDebugText();
			break;
		case GuiOperationEnum::AddCustomPlanet:
			{
				Planet* planet = mPlanetManager->AddPlanetRandom(mCameraContainer->GetCamera()->getPosition() - (Vector3f::unitZ * 10.0f));
				mParticleSystem->AddGravityForceGenerator(planet->GetRigidBody());
				mParticleSystem->AddRigidBody(planet->GetRigidBody());
				break;
			}
		case GuiOperationEnum::RemoveCustomPlanet:
			mParticleSystem->RemoveLast();
			mPlanetManager->RemoveLastRandomPlanet();
			break;
		case GuiOperationEnum::RemoveAllCustomPlanets:
			{
				int total = mPlanetManager->RemoveAllRandomPlanets();
				for (int i = 0; i < total; i++)
				{
					mParticleSystem->RemoveLast();
				}
				break;
			}
		case GuiOperationEnum::ViewSolarSystem:
			mCameraContainer->UnLatch();
			mPlanetIndex = 0;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewMercury:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(1));
			mPlanetIndex = 1;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewVenus:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(2));
			mPlanetIndex = 2;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewEarth:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(3));
			mPlanetIndex = 3;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewMars:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(4));
			mPlanetIndex = 4;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewJupiter:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(5));
			mPlanetIndex = 5;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewSaturn:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(6));
			mPlanetIndex = 6;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewUranus:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(7));
			mPlanetIndex = 7;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewNeptune:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(8));
			mPlanetIndex = 8;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewPluto:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(9));
			mPlanetIndex = 9;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewEris:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(10));
			mPlanetIndex = 10;
			UpdateDebugInformation();
			break;
		case GuiOperationEnum::ViewMoon:
			mCameraContainer->Latch(mPlanetManager->GetPlanetAt(11));
			mPlanetIndex = 11;
			UpdateDebugInformation();
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
	//Vector3f cameraPosition = mCamera->getPosition();
	//Vector3f position = cameraPosition + Vector3f(0.0f, 5.0f, 30.0f);
	mSkybox->SetPostion(Vector3f::zero);
	//mSkybox->SetPostion(position);
}