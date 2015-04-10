/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  MaterialManager.cpp
*
*	Description:
*		This class manages materials.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "MaterialManager.h"
#include "Material.h"

//constructors
MaterialManager::MaterialManager()
{
	mMaterialMap = map<string, Material*>();
	mIDs = 0;
}
MaterialManager::~MaterialManager()
{
	RemoveAllMaterials();
}

//removing the materials
void MaterialManager::RemoveAllMaterials()
{
	map<string, Material*>::iterator iter = mMaterialMap.begin();
	map<string, Material*>::iterator back = mMaterialMap.end();

	while (iter != back)
	{
		Material* material = iter->second;
		delete material;
		iter->second = nullptr;
		iter++;
	}

	mMaterialMap.clear();
}

//adding new materials
bool MaterialManager::AddMaterial(Texture *texture) //add a single material and use the filepath as the key
{
	return AddMaterial(texture, "material" +to_string(mIDs));
	mIDs++;
}
bool MaterialManager::AddMaterial(Texture *texture, const string &customKey) //add a single material and use a custom key
{
	bool ok = true;

	Material* newMaterial = new Material(texture);
	
	std::pair<string, Material*> thePair= pair<string, Material*>(customKey, newMaterial);

	mMaterialMap.insert(thePair);
	ok = true;
	
	return ok;
}
int MaterialManager::AddMaterialMany(Texture **textures, int count) //add multiple materials with a single function and use the filepath as the key
{
	bool ok;
	int sucessfulCount = 0;
	for (int i = 0; i < count; i++)
	{
		ok = AddMaterial(textures[i]);
		if (ok)
			sucessfulCount++;
	}
	return sucessfulCount;
}

//search functions
Material* MaterialManager::FindMaterial(const string &key) const
{
	return mMaterialMap.find(key)->second;
}
bool MaterialManager::MaterialExists(const string &key) const
{
	return FindMaterial(key) != nullptr;
}

