/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  MaterialManager3D.h
*
*	Description:
*		This class manages materials.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _MATERIAL_MANAGER_3D_H
#define _MATERIAL_MANAGER_3D_H

class Material;
class Texture;

#include <string>
#include "Color.h"
#include <map>

using namespace std;

class MaterialManager
{
private:
	map<string, Material*> mMaterialMap;
	unsigned int mIDs;

public:
	//constructors
	MaterialManager();
	~MaterialManager();

	//adding and removing materials
	bool AddMaterial(Texture *texture); //add a single material and use the filepath as the key, returns if it is successful
	bool AddMaterial(Texture *texture, const string &customKey); //add a single material and use a custom key, returns if it is successful
	bool AddMaterial(Texture *texture, const Color &color, const string &customKey); //add a single material and use a custom key, returns if it is successful
	bool AddMaterial(const Color &color, const string &customKey); //add a single material and use a custom key, returns if it is successful
	int AddMaterialMany(Texture **texture, int count); //add multiple materials with a single function and use the filepath as the key, returns the number of materials that were successful loaded


	//search functions
	Material* FindMaterial(const string &key) const;
	bool MaterialExists(const string &key) const;

private:
	void InsertMaterial(const std::string &key, Material* material);
	void RemoveAllMaterials();

};


#endif

