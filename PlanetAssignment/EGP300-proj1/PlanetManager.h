#ifndef _PLANET_MANAGER_H
#define _PLANET_MANAGER_H

class Model;
class Material;
class Planet;
class TextureManager;

#include "Vector3f.h"
#include <vector>
#include <string>

#define PLANET_SIZE_SCALE 0.000001
#define PLANET_MASS_SCALE 0.0001

class PlanetManager
{
private:
	std::vector<Planet*> mPlanetVector; //the vector of all the planets
	TextureManager* mPlanetTextures; //the textures that are loaded for each planet are stored here
	std::vector<Material*> mMaterialVector; // the materials for each planet are stored here
	Model* mPlanetModel; //the model geometry that all the planets will use
	Vector3f mOrigin; //the center of the solar system (the position of the sun)

public:
	PlanetManager();
	~PlanetManager();

	void FixedUpdate(double t);
	void IntializeAssets();
	void CleanUp();
	bool AddPlanet(const std::string &dataFilePath);
};

#endif