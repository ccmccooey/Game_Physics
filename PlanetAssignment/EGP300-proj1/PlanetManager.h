#ifndef _PLANET_MANAGER_H
#define _PLANET_MANAGER_H

class Model;
class Material;
class Planet;
class TextureManager;
class TextRenderer;

#include "Vector3f.h"
#include "DrawData.h"
#include <vector>
#include <string>
#include "PlanetScaleFactor.h"



class PlanetManager
{
public:
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
	bool AddPlanetList(const std::string &dataFilePath);

	//accessors
	Planet* GetPlanetAt(int index) const;
	Planet* GetPlanetByName(const std::string &name) const; //this is a search function and is slower then get planet at
	int GetPlanetCount() const;
	Model* GetPlanetModel() const;

	void ResetAllPlanets();

	//Draw the planets
	void Draw(DrawData* drawData);

	//this function is just a place for me to insert a breakpoint to check properies, its called via keyboard input
	void BreakPoint();
};

#endif