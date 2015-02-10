#include "MainApp.h"
#include "GuiSystem.h"
#include "PlanetManager.h"
#include "Camera.h"
#include "ParticleSystem.h"

//constructor
MainApp::MainApp()
{

}
MainApp::~MainApp()
{

}

//initialization and clean up
void MainApp::Initialize()
{

}
void MainApp::CleanUp()
{

}

//keyboard input
void MainApp::CheckKeyboardInput(unsigned char key)
{

}
void MainApp::CheckSpecialKeyboardInput(int key, int x, int y)
{

}

//mouse input
void MainApp::CheckMouseInput(int x, int y, bool mouseDown, bool mouseClicked)
{

}

//update window size when the user resizes the window
void MainApp::UpdateWindowSize(int w, int h)
{

}

//render everything
void MainApp::RenderScene()
{
	//create the physics
	particleSystem = new ParticleSystem();

	//create the planet manager
	planetManager = new PlanetManager();
	planetManager->IntializeAssets();

	textRenderer = new TextRenderer();

	drawData = new DrawData();
	drawData->textRenderer = textRenderer;
	drawData->shaderManager = &shaderManager;

	bool ok;
	ok = planetManager->AddPlanetList("../PlanetData/solar_system.txt");
	//ok = planetManager->AddPlanet("../PlanetData/sun.txt");
	//ok = planetManager->AddPlanet("../PlanetData/earth.txt");

	//add a force generator to the particle system
	if (ok)
	{
		particleSystem->AddGravityForceGenerator(planetManager->GetPlanetAt(0)->GetRigidBody());
		//particleSystem->AddGravityForceGenerator(planetManager->GetPlanetAt(1)->GetRigidBody());
		int size = planetManager->GetPlanetCount();
		for (int i = 0; i < size; i++)
		{
			particleSystem->AddRigidBody(planetManager->GetPlanetAt(i)->GetRigidBody());
		}
	}
}