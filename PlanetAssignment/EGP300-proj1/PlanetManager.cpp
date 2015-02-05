#include "PlanetManager.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Material.h"
#include "Planet.h"
#include "Model.h"
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
	mPlanetModel = new Model(Geometry::CUBE);
	//mPlanetModel = new Model(Geometry::SPHERE); //Doesnt work the math is too fucking complicated

	mPlanetTextures = new TextureManager();
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
		mass = mass * PLANET_MASS_SCALE;
		rb->SetMass((float)mass);

		//radius
		getline(reader, line);
		double radius = stod(line);
		radius = radius * PLANET_SIZE_SCALE;
		planet->getTransform()->SetScale((float)radius);

		//distance from the sun
		getline(reader, line);
		float distance = stof(line);
		distance = distance * PLANET_DISTANCE_SCALE;
		planet->getTransform()->SetPosition(mOrigin.x + distance, mOrigin.y, mOrigin.z);

		//velocity
		getline(reader, line);
		rb = planet->GetRigidBody();
		float velocity = stof(line);
		rb->SetVelocity(Vector3f(0.0f, 0.0f, velocity));

		//rotation speed (dont care right now)
		getline(reader, line);

		mPlanetVector.push_back(planet);
		
	}
	else
	{
		std::cerr << "Planet file load FAIL: (" << dataFilePath << ") was not found" << endl;
		ok = false;
	}

	reader.close();
	return ok;
}

//search functions
Planet* PlanetManager::GetPlanetAt(int index) const
{
	if (index > 0 && index < mPlanetVector.size())
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

//update
void PlanetManager::FixedUpdate(double t)
{
	for (unsigned int i = 0; i < mPlanetVector.size(); i++)
	{
		mPlanetVector[i]->FixedUpdate(t);
	}
}

//draw
void PlanetManager::Draw(GLShaderManager &shaderManager, const M3DMatrix44f &frustum, M3DMatrix44f &view)
{
	for (unsigned int i = 0; i < mPlanetVector.size(); i++)
	{
		mPlanetVector[i]->Draw(shaderManager, frustum, view);
	}
}
