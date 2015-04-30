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

	//default material
	Material* newMaterial = new Material();	
	newMaterial->SetShader(ShaderType::SHADER_GREY_SOLID);
	InsertMaterial("Default", newMaterial);

	//null material
	mNullMaterial = new Material();
	newMaterial->SetShader(ShaderType::SHADER_COLOR_SOLID);
	newMaterial->SetColor(1.0f, 0.125f, 1.0f);
}
MaterialManager::~MaterialManager()
{
	RemoveAllMaterials();

	delete mNullMaterial;
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
void MaterialManager::InsertMaterial(const std::string &key, Material* material)
{
	std::pair<string, Material*> thePair= pair<string, Material*>(key, material);
	mMaterialMap.insert(thePair);
}
bool MaterialManager::AddMaterial(Texture *texture, const string &customKey) //add a single material and use a custom key
{
	bool ok = true;
	
	Material* newMaterial = new Material(texture);	
	newMaterial->SetShader(ShaderType::SHADER_TEXTURE_REPLACE);
	InsertMaterial(customKey, newMaterial);
	
	ok = true;	
	return ok;
}
bool MaterialManager::AddMaterial(Texture *texture, const Color &color, const string &customKey) //add a single material and use a custom key, returns if it is successful
{
	bool ok = true;

	Material* newMaterial = new Material(texture);	
	newMaterial->SetShader(ShaderType::SHADER_TEXTURE_COLOR);
	newMaterial->SetColor(color);
	InsertMaterial(customKey, newMaterial);

	ok = true;	
	return ok;
}
bool MaterialManager::AddMaterial(Texture *texture, const Color &color, ShaderType shader, const string &customKey)
{
	bool ok = true;

	Material* newMaterial = new Material(texture);	
	newMaterial->SetShader(shader);
	newMaterial->SetColor(color);
	InsertMaterial(customKey, newMaterial);

	ok = true;	
	return ok;
}
bool MaterialManager::AddMaterial(const Color &color, const string &customKey) //add a single material and use a custom key, returns if it is successful
{
	bool ok = true;

	Material* newMaterial = new Material();	
	newMaterial->SetShader(ShaderType::SHADER_COLOR_SHADED);
	newMaterial->SetColor(color);
	InsertMaterial(customKey, newMaterial);

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
	std::map<string, Material*>::const_iterator iter = mMaterialMap.find(key);
	if (iter != mMaterialMap.end())
	{
		return iter->second;
	}
	else
	{
		return mNullMaterial;
	}
}
bool MaterialManager::MaterialExists(const string &key) const
{
	return FindMaterial(key) != nullptr;
}

