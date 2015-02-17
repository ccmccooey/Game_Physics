#include "PlanetManager.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Material.h"
#include "Planet.h"
#include "Model.h"
#include "Random.h"
#include <queue>
#include <fstream>
#include <iostream>

using namespace std;


PlanetManager::PlanetManager()
{
	mOrigin = Vector3f::zero;
}
PlanetManager::~PlanetManager()
{
	CleanUp();
}

void PlanetManager::IntializeAssets()
{
	//create the planet model
	//mPlanetModel = new Model(Geometry::CUBE);
	mPlanetModel = new Model(Geometry::SPHERE); //Doesnt work for sphere, the math for calculating all the geometry has problems

	mPlanetTextures = new TextureManager();

	mCustomPlanetVector = vector<Planet*>();
}
void PlanetManager::CleanUp()
{
	unsigned int i;

	//delete the planets
	for (i = 0; i < mPlanetVector.size(); i++)
	{
		delete mPlanetVector[i];
	}
	mPlanetVector.clear();

	for (i = 0; i < mCustomPlanetVector.size(); i++)
	{
		delete mCustomPlanetVector[i];
	}
	mCustomPlanetVector.clear();

	//delete the planet model
	delete mPlanetModel;
	mPlanetModel = nullptr;

	//delete the material vector
	for (i = 0; i < mMaterialVector.size(); i++)
	{
		delete mMaterialVector[i];
	}
	mMaterialVector.clear();

	//delete the textures
	delete mPlanetTextures;
	mPlanetTextures = nullptr;
}

//adding new planets
bool PlanetManager::AddPlanetList(const std::string &dataFilePath)
{
	bool ok = false;

	ifstream reader = ifstream();

	reader.open(dataFilePath);
	string line;

	if (!reader.fail())
	{
		queue<string> mPaths = queue<string>();

		while (!reader.eof())
		{
			getline(reader, line);
			if (line != "")
			{
				mPaths.push(line);
			}
		}

		string path;
		while (!mPaths.empty())
		{
			path = mPaths.front();
			this->AddPlanet(path);
			mPaths.pop();
		}
		ok = true;
	}
	return ok;
}
bool PlanetManager::AddPlanet(const std::string &dataFilePath)
{
	bool ok = false;

	ifstream reader = ifstream();

	reader.open(dataFilePath);
	string line;
	
	/* format goes as follows
	name
	texture file path
	mass
	radius
	distance from sun
	velocity
	gravitational force
	rotation speed
	*/

	if (!reader.fail())
	{
		Planet* planet = new Planet(mPlanetModel);

		//name
		getline(reader, line);
		planet->SetName(line);

		//texture
		getline(reader, line);
		mPlanetTextures->AddTexture(line);
		Texture* texture = mPlanetTextures->FindTexture(line);
		Material* material = new Material(texture);
		mMaterialVector.push_back(material);
		planet->SetMaterial(material);

		//mass
		getline(reader, line);
		Rigidbody* rb = planet->GetRigidBody();
		long double mass = stold(line);
		//mass = mass * PLANET_MASS_SCALE;
		rb->SetMass((float)mass);

		//radius
		getline(reader, line);
		double radius = stod(line);
		radius = radius * PLANET_SIZE_SCALE;
		radius = 1.0f; //Comment this out for scaling
		planet->getTransform()->SetScale((float)radius);

		//distance from the sun
		getline(reader, line);
		float distance = stof(line);
		//distance = distance * PLANET_DISTANCE_SCALE;
		rb->SetPosition(mOrigin.x + distance, mOrigin.y, mOrigin.z);

		//velocity
		getline(reader, line);
		rb = planet->GetRigidBody();
		float velocity = stof(line);
		velocity = velocity;// *PLANET_VELOCITY_CONVERT; //get it out of km/s
		rb->SetVelocity(Vector3f(0.0f, 0.0f, velocity));

		//rotation speed (dont care right now)
		getline(reader, line);
		
		//gravity, this should be calculated but the numbers are too large to be calculated with long doubles
		getline(reader, line);
		double g = stod(line);
		g = g * PLANET_GRAVITY_FACTOR;
		planet->SetGravity((float)g);


		if (planet->GetName() == "Moon")
		{
			planet->getTransform()->SetScale(0.125f);
		}

		planet->SetOriginalDataToCurrent();

		//add the planet to the vector of planets
		mPlanetVector.push_back(planet);

		ok = true;
		
	}
	else
	{
		std::cerr << "Planet file load FAIL: (" << dataFilePath << ") was not found" << endl;
		ok = false;
	}

	reader.close();
	return ok;
}
Planet* PlanetManager::AddPlanetRandom(const Vector3f &graphicsPosition)
{
	Planet* planet = new Planet(mPlanetModel);

	bool huge = Random::Bool(1, 5);

	//material
	int index = Random::Range((int)mMaterialVector.size() - 1);
	planet->SetMaterial(mMaterialVector[index]);

	//mass
	Rigidbody* rb = planet->GetRigidBody();
	double d = Random::ArithmeticDouble();
	double mass = 1e10 + d * 1e14;
	if (huge)
		mass += 1.5e30;
	rb->SetMass((float)mass);

	//velocity
	float velocity = 20.0f + Random::ArithmeticFloat() * 75.0f;
	rb->SetVelocity(velocity);

	//position
	Vector3f physicsPosition = mOrigin + (graphicsPosition / PLANET_DISTANCE_SCALE);
	physicsPosition.y = mOrigin.y;
	rb->SetPosition(physicsPosition);

	//scale
	float radius = 1.0f + Random::ArithmeticFloat() * 2.0f;
	if (huge)
		radius += 5.0f;
	planet->getTransform()->SetScale((float)radius);

	//name
	string name = "";
	name += Random::RandomLetter();
	for (int i = 0; i < 9; i++)
		name += Random::RandomLetterOrDigit();
	planet->SetName(name);

	mCustomPlanetVector.push_back(planet);
	return planet;
}
void PlanetManager::RemoveLastRandomPlanet()
{
	Planet* last = mCustomPlanetVector.back();
	mCustomPlanetVector.pop_back();
	delete last;
}
int PlanetManager::RemoveAllRandomPlanets()
{
	unsigned int size = (int)mCustomPlanetVector.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete mCustomPlanetVector[i];
	}
	mCustomPlanetVector.clear();
	return (int)size;
}

//search functions
Planet* PlanetManager::GetPlanetAt(int index) const
{
	if (index >= 0 && index < (int)mPlanetVector.size())
	{
		return mPlanetVector[index];
	}
	return nullptr;
}
Planet* PlanetManager::GetPlanetByName(const std::string &name) const
{
	Planet* planet = nullptr;
	for (unsigned int i = 0; i < mPlanetVector.size(); i++)
	{
		if (mPlanetVector[i]->GetName() == name)
		{
			planet = mPlanetVector[i];
			break;
		}
	}
	return planet;
}
Model* PlanetManager::GetPlanetModel() const
{
	return mPlanetModel;
}
int PlanetManager::GetPlanetCount() const
{
	return (int)mPlanetVector.size();
}

//update
void PlanetManager::FixedUpdate(double t)
{
	unsigned int i;
	for (i = 0; i < mPlanetVector.size(); i++)
	{
		mPlanetVector[i]->FixedUpdate(t);
	}
	for (i = 0; i < mPlanetVector.size(); i++)
	{
		mPlanetVector[i]->FinishUpdate();
	}	

	for (i = 0; i < mCustomPlanetVector.size(); i++)
	{
		mCustomPlanetVector[i]->FixedUpdate(t);
	}
	for (i = 0; i < mCustomPlanetVector.size(); i++)
	{
		mCustomPlanetVector[i]->FinishUpdate();
	}	
}

void PlanetManager::ResetAllPlanets()
{
	for (unsigned int i = 0; i < mPlanetVector.size(); i++)
	{
		mPlanetVector[i]->Reset();
	}
}

//draw
void PlanetManager::Draw(DrawData* drawData)
{
	for (unsigned int i = 0; i < mPlanetVector.size(); i++)
	{
		mPlanetVector[i]->DrawAll(drawData);
	}
	for (unsigned int i = 0; i < mCustomPlanetVector.size(); i++)
	{
		mCustomPlanetVector[i]->DrawAll(drawData);
	}
}

//for debugging purposes only
void PlanetManager::BreakPoint()
{
	int putBreakPointHere = 0;
}
