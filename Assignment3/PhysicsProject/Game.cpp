#include "Game.h"
#include "GameObject.h"
#include "AssetLoader.h"

using namespace std;

//constructors
Game::Game()
{
	Initialize();
}
Game::~Game()
{
	CleanUp();
}

//initialization
void Game::Initialize()
{
	AssetLoader::LoadAssets();

	mGameObjects = vector<GameObject*>();

	//create a sphere
	GameObject* mySphere = new GameObject("Sphere", "Steel", Vector3f::zero);
	mGameObjects.push_back(mySphere);
}

//update all the mass aggregate graphics
void Game::Update(double t)
{
	unsigned int size = mGameObjects.size();
	for (unsigned int i = 0; i < size; i++)
	{
		mGameObjects[i]->LinkPositions();
	}
}

//cleanup
void Game::CleanUp()
{
	unsigned int size = mGameObjects.size();
	for (unsigned int i = 0; i < size; i++)
	{
		//delete mGameObjects[i];
	}
	mGameObjects.clear();
}

//reset the mass aggregates
void Game::Reset()
{
	
}

void Game::GetDebugInfo(std::string &info) const
{
	info = "No info yet";
}