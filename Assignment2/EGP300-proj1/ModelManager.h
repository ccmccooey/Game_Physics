/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 20, 2015
*	Filename:  ModelManager.h
*
*	Description:
*		This class manages models.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _MODEL_MANAGER_H
#define _MODEL_MANAGER_H

class Model;
class Texture;

#include <string>
#include <map>

using namespace std;

class ModelManager
{
private:
	map<string, Model*> mModelMap;
	unsigned int mIDs;
	Model* mStandard[3];

public:
	//constructors
	ModelManager();
	~ModelManager();

	//adding and removing models
	bool AddModel(Model* model); //add a single model and use the filepath as the key, returns if it is successful
	bool AddModel(Model* model, const string &customKey); //add a single model and use a custom key, returns if it is successful

	//search functions
	Model* FindModel(const string &key) const;
	Model* FindCube() const;
	Model* FindQuad() const;
	Model* FindSphere() const;
	bool ModelExists(const string &key) const;

private:
	void RemoveAllModels();
	void CreateStandardModels();

};


#endif

