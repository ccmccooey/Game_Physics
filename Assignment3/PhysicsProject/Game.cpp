#include "Game.h"
#include "MainApp.h"
#include "PhysicsSystem.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "AssetLoader.h"
#include "GroundForceGenerator.h"
#include "Ground.h"
#include "ObjectMaterial.h"
#include "DisplayPointer.h"
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
	mObjectMaterial->SetObjectType("Plastic", MASS_OBJECT_PLASTIC, SIZE_OBJECT_SMALL);

	//create intial scene
	CreateInitialScene();

	//create the force generators
	GroundForceGenerator* gfg = new GroundForceGenerator(10.0f);
	MainApp::GetPhysicsSystem()->AddForceGenerator(gfg);

	//create the display pointer
	mDisplayPointer = new DisplayPointer();
	mDisplayPointerIndex = 0;
}
void Game::CreateInitialScene()
{
	//change the ground
	mGround->SetMaterial("GrassTerrain");

	//create the buildings
	std::string name = "BuildingSide";

	Vector3f pos1 = Vector3f(-20.0f, -10.0f, 0.0f);
	Vector3f pos2 = Vector3f(0.0f, -15.0f, 0.0f);
	Vector3f pos3 = Vector3f(20.0f, -10.0f, 0.0f);

	Vector3f scale1 = Vector3f(5.0f, 10.0f, 5.0f);
	Vector3f scale2 = Vector3f(5.0f, 15.0f, 5.0f);
	Vector3f scale3 = Vector3f(5.0f, 10.0f, 5.0f);

	CreateObjectStaticBox(pos1, scale1, name);
	CreateObjectStaticBox(pos2, scale1, name);
	CreateObjectStaticBox(pos3, scale1, name);

	//create the spheres
	unsigned int countX = 5;
	unsigned int countZ = 5;
	Vector3f sphereSpacing = Vector3f(2.0f, 2.0f, 2.0f);
	Vector3f sphereBegin = Vector3f(- ((float)countX * 0.5f), 25.0f, - ((float)countZ * 0.5f));
	unsigned int i, j;
	for (i = 0; i < countX; i++)
	{
		for (j = 0; j < countZ; j++)
		{
			CreateObjectSphere(sphereBegin + Vector3f(sphereSpacing.x * (float)i, 0.0f, sphereSpacing.z * (float)j));
		}
	}
}

//creating new objects
void Game::CreateObjectSphere(const Vector3f &position)
{
	GameObject* sphere = new GameObject("Sphere", mObjectMaterial->GetName(), position, GameObject::Sphere, mObjectMaterial->GetMass(), mObjectMaterial->GetSize() );
	mGameObjects.push_back(sphere);
}
void Game::CreateObjectBox(const Vector3f &position)
{
	GameObject* box = new GameObject("Cube", mObjectMaterial->GetName(), position, GameObject::Box, mObjectMaterial->GetMass(), mObjectMaterial->GetSize());
	mGameObjects.push_back(box);
}
void Game::CreateObjectStaticBox(const Vector3f &position, const Vector3f &scale, const std::string &materialName)
{
	GameObject* box = new GameObject("Cube", materialName, position, GameObject::Box, 10000, scale.x);
	box->SetStatic(true);
	box->SetScale(scale);
	mGameObjects.push_back(box);
	box->LinkPositions();
}

//update all the mass aggregate graphics
void Game::Update(double t)
{
	unsigned int size = mGameObjects.size();
	for (unsigned int i = 0; i < size; i++)
	{
		mGameObjects[i]->LinkPositions();
	}

	mDisplayPointer->UpdatePosition();
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

	delete mDisplayPointer;
	delete mObjectMaterial;
	delete mGround;
}

//reset the mass aggregates
void Game::Reset()
{
	mDisplayPointer->UnLatch();

	unsigned int size = mGameObjects.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete mGameObjects[i];
	}
	mGameObjects.clear();

	//recreate the initial scene
	CreateInitialScene();
}

//accessors
void Game::GetDebugInfo(std::string &info) const
{
	unsigned int checksNeeded = 0;
	unsigned int totalObjects = mGameObjects.size();
	unsigned int totalColliders = totalObjects + 1;

	for (unsigned int i = 1; i < totalColliders; i++)
		checksNeeded += (totalColliders - i);

	info = "Number of rigid bodies: " +to_string(totalObjects)
		+ "\nNumber of collision checks needed: " +to_string(checksNeeded);

	if (mDisplayPointer->IsLatched())
	{
		RigidBody* rb = mGameObjects[mDisplayPointerIndex]->GetPhysicsObject();
		info +=
			"\nMass: " + to_string(rb->GetMass()) +
			"\nPosition: " + rb->GetPosition().ToString() +
			"\nOrientation: " + rb->GetOrientation().toString() +
			"\nLinear Velocity: " + rb->GetVelocity().ToString() +
			"\nAngular Velocity: " + rb->GetAngularVelocity().ToString() +
			"\nLinear Acceleration: " + rb->GetAcceleration().ToString() +
			"\nAngular Acceleration: " + rb->GetAngularAcceleration().ToString();
	}
}
float Game::GetObjectMass() const
{
	return mObjectMaterial->GetMass();
}
float Game::GetObjectSize() const
{
	return mObjectMaterial->GetSize();
}
void Game::GetObjectInfoString(std::string &info) const
{
	info = "Material: " + mObjectMaterial->GetName() + ", Mass: " + to_string(mObjectMaterial->GetMass()) + ", Size: " + to_string(mObjectMaterial->GetSize());
}

//send gui events from the main app to the game
void Game::SendGuiEvent(GuiOperationEnum ev)
{
	switch(ev)
	{
	case GuiOperationEnum::DebugNext:
		if (mGameObjects.size() > 0)
		{
			mDisplayPointerIndex++;
			if (mDisplayPointerIndex >= mGameObjects.size())
				mDisplayPointerIndex = 0;
			mDisplayPointer->LatchTo(mGameObjects[mDisplayPointerIndex]);
			mDisplayPointer->UpdatePosition();
		}
		break;
	case GuiOperationEnum::Set_Size_Small:
		mObjectMaterial->SetSize(SIZE_OBJECT_SMALL);
		break;
	case GuiOperationEnum::Set_Size_Medium:
		mObjectMaterial->SetSize(SIZE_OBJECT_MEDIUM);
		break;
	case GuiOperationEnum::Set_Size_Large:
		mObjectMaterial->SetSize(SIZE_OBJECT_LARGE);
		break;
	case GuiOperationEnum::Set_Material_Airfilled:
		mObjectMaterial->SetMassPerUnit(MASS_OBJECT_AIRFILLED);
		mObjectMaterial->SetName("AirFilled");
		break;
	case GuiOperationEnum::Set_Material_Plastic:
		mObjectMaterial->SetMassPerUnit(MASS_OBJECT_PLASTIC);
		mObjectMaterial->SetName("Plastic");
		break;
	case GuiOperationEnum::Set_Material_Wood:
		mObjectMaterial->SetMassPerUnit(MASS_OBJECT_WOOD);
		mObjectMaterial->SetName("Wood");
		break;
	case GuiOperationEnum::Set_Material_Steel:
		mObjectMaterial->SetMassPerUnit(MASS_OBJECT_STEEL);
		mObjectMaterial->SetName("Steel");
		break;
	case GuiOperationEnum::Set_Material_Iron:
		mObjectMaterial->SetMassPerUnit(MASS_OBJECT_IRON);
		mObjectMaterial->SetName("Iron");
		break;
	case GuiOperationEnum::Create_Sphere:
		this->CreateObjectSphere(Vector3f::unitY * 20.0f +Vector3f(Random::ArithmeticFloat(), 0.0f, Random::ArithmeticFloat()));
		break;
	case GuiOperationEnum::Create_Box:
		this->CreateObjectBox(Vector3f::unitY * 20.0f);
		break;
	}
}