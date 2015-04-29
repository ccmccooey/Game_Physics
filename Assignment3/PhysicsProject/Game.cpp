#include "Game.h"
#include "MainApp.h"
#include "PhysicsSystem.h"
#include "GameObject.h"
#include "AssetLoader.h"
#include "GroundForceGenerator.h"
#include "Ground.h"
#include "ObjectMaterial.h"
#include "Random.h"

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

	//create the ground
	mGround = new Ground();

	//create the object material
	mObjectMaterial = new ObjectMaterial();
	mObjectMaterial->mSize = SIZE_OBJECT_SMALL;
	mObjectMaterial->mMass = MASS_OBJECT_PLASTIC;
	mObjectMaterial->mName = "Plastic";

	//create intial objects
	//CreateObjectSphere(Vector3f::unitY * 10.0f);
	//CreateObjectSphere(Vector3f::unitY * 25.0f);

	//create the force generators
	GroundForceGenerator* gfg = new GroundForceGenerator(5.0f);
	MainApp::GetPhysicsSystem()->AddForceGenerator(gfg);
}

//creating new objects
void Game::CreateObjectSphere(const Vector3f &position)
{
	GameObject* sphere = new GameObject("Sphere", mObjectMaterial->mName, position, GameObject::Sphere, mObjectMaterial->mMass, mObjectMaterial->mSize );
	mGameObjects.push_back(sphere);
}
void Game::CreateObjectBox(const Vector3f &position)
{
	GameObject* box = new GameObject("Cube", mObjectMaterial->mName, position, GameObject::Box, mObjectMaterial->mMass, mObjectMaterial->mSize );
	mGameObjects.push_back(box);
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

	delete mObjectMaterial;
	delete mGround;
}

//reset the mass aggregates
void Game::Reset()
{
	
}

//accessors
void Game::GetDebugInfo(std::string &info) const
{
	info = "No info yet";
}
float Game::GetObjectMass() const
{
	return mObjectMaterial->mMass;
}
float Game::GetObjectSize() const
{
	return mObjectMaterial->mSize;
}
void Game::GetObjectInfoString(std::string &info) const
{
	info = "Material: " +mObjectMaterial->mName + ", Mass: " +to_string(mObjectMaterial->mMass) + ", Size: " +to_string(mObjectMaterial->mSize);
}

//send gui events from the main app to the game
void Game::SendGuiEvent(GuiOperationEnum ev)
{
	switch(ev)
	{
	case GuiOperationEnum::Set_Size_Small:
		mObjectMaterial->mSize = SIZE_OBJECT_SMALL;
		break;
	case GuiOperationEnum::Set_Size_Medium:
		mObjectMaterial->mSize = SIZE_OBJECT_MEDIUM;
		break;
	case GuiOperationEnum::Set_Size_Large:
		mObjectMaterial->mSize = SIZE_OBJECT_LARGE;
		break;
	case GuiOperationEnum::Set_Material_Airfilled:
		mObjectMaterial->mMass = MASS_OBJECT_AIRFILLED;
		mObjectMaterial->mName = "AirFilled";
		break;
	case GuiOperationEnum::Set_Material_Plastic:
		mObjectMaterial->mMass = MASS_OBJECT_PLASTIC;
		mObjectMaterial->mName = "Plastic";
		break;
	case GuiOperationEnum::Set_Material_Wood:
		mObjectMaterial->mMass = MASS_OBJECT_WOOD;
		mObjectMaterial->mName = "Wood";
		break;
	case GuiOperationEnum::Set_Material_Steel:
		mObjectMaterial->mMass = MASS_OBJECT_STEEL;
		mObjectMaterial->mName = "Steel";
		break;
	case GuiOperationEnum::Set_Material_Iron:
		mObjectMaterial->mMass = MASS_OBJECT_IRON;
		mObjectMaterial->mName = "Iron";
		break;
	case GuiOperationEnum::Create_Sphere:
		this->CreateObjectSphere(Vector3f::unitY * 20.0f + (Vector3f::unitZ * Random::ArithmeticFloat()));
		break;
	case GuiOperationEnum::Create_Box:
		this->CreateObjectBox(Vector3f::unitY * 20.0f);
		break;
	}
}