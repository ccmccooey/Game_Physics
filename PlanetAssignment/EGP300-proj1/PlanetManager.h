#ifndef _PLANET_MANAGER_H
#define _PLANET_MANAGER_H

class Model;
class Material;
class Planet;
class TextureManager;

#include "Vector3f.h"
#include "GLfiles.h"
#include <vector>
#include <string>

//1 / earth size or 1 / sun size? IDK
#define PLANET_SIZE_SCALE 1 / 695800//6371 
#define PLANET_DISTANCE_SCALE 1 / 149500000 * 100
#define PLANET_MASS_SCALE 1 / 5.97219e24 


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

	Planet* GetPlanetAt(int index) const;
	Planet* GetPlanetByName(const std::string &name) const; //this is a search function and is slower then get planet at

	//Draw the planets
	void Draw(GLShaderManager &shaderManager, const M3DMatrix44f &frustum, M3DMatrix44f &view);
};

#endif