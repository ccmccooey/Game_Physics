/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  March 3, 2015
*	Filename:  ModelManager.cpp
*
*	Description:
*		This class manages models.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "ModelManager.h"
#include "Model.h"

//constructors
ModelManager::ModelManager()
{
	mModelMap = map<string, Model*>();
	CreateStandardModels();
	mIDs = 0;
}
ModelManager::~ModelManager()
{
	RemoveAllModels();

	//delete mStandard[0];
	//delete mStandard[1];
	//delete mStandard[2];
}
void ModelManager::CreateStandardModels()
{
	mStandard[0] = new Model(Geometry::CUBE);
	mStandard[1] = new Model(Geometry::QUAD);
	mStandard[2] = new Model(Geometry::SPHERE);
	AddModel(mStandard[0], "Cube");
	AddModel(mStandard[1], "Quad");
	AddModel(mStandard[2], "Sphere");
}

//removing the models
void ModelManager::RemoveAllModels()
{
	map<string, Model*>::iterator iter = mModelMap.begin();
	map<string, Model*>::iterator back = mModelMap.end();

	while (iter != back)
	{
		Model* model = iter->second;
		delete model;
		iter->second = nullptr;
		iter++;
	}

	mModelMap.clear();
}

//adding new models
bool ModelManager::AddModel(Model *model) //add a single model and use the filepath as the key
{
	return AddModel(model, "model" +to_string(mIDs));
	mIDs++;
}
bool ModelManager::AddModel(Model *model, const string &customKey) //add a single model and use a custom key
{
	bool ok = true;

	
	std::pair<string, Model*> thePair= pair<string, Model*>(customKey, model);

	mModelMap.insert(thePair);
	ok = true;
	
	return ok;
}

//search functions
Model* ModelManager::FindModel(const string &key) const
{
	return mModelMap.find(key)->second;
}
bool ModelManager::ModelExists(const string &key) const
{
	return FindModel(key) != nullptr;
}
Model* ModelManager::FindCube() const
{
	return mStandard[0];
}
Model* ModelManager::FindQuad() const
{
	return mStandard[1];
}
Model* ModelManager::FindSphere() const
{
	return mStandard[2];
}

