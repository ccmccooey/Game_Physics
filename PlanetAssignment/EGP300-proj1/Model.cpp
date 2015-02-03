/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Model.cpp
*
*	Description:
*		This class represents a 3D model. The class can store multiple meshes to be drawn. It also stores a material which determines what textures and shaders the model uses.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Model.h"
#include "Mesh.h"
#include "Material.h"

using namespace std;

//constructors
Model::Model()
{
	mMeshArray = vector<Mesh*>();
	mBad = true;
}
Model::Model(Geometry geometryType)
{
	mMeshArray = vector<Mesh*>();
	this->InitializeBuiltInGeometry(geometryType);
}
Model::Model(Material* material)
{
	mMeshArray = vector<Mesh*>();
	mMaterial = material;
	mBad = true;
}
Model::Model(Material* material, Geometry geometryType)
{
	mMaterial = material;
	mMeshArray = vector<Mesh*>();
	this->InitializeBuiltInGeometry(geometryType);
}
Model::~Model()
{
	this->CleanMeshData();
}

//initialize meshes that use custom geometry
void Model::InitializeBuiltInGeometry(Geometry geometryType)
{
	Mesh* mesh;
	mesh = new Mesh(geometryType);
	mMeshArray.push_back(mesh);
}

//clear the meshes
void Model::CleanMeshData()
{
	for (unsigned int i = 0; i < mMeshArray.size(); i++)
	{
		delete mMeshArray[i];
	}
	mMeshArray.clear();
}

//draw the meshes using the model's material
void Model::Draw(GLShaderManager *shaderManager, const M3DMatrix44f &projection, M3DMatrix44f &modelView, M3DMatrix44f &mvpMatrix)
{
	if (mMaterial != nullptr)
		mMaterial->Use(shaderManager, projection, modelView, mvpMatrix);
	
	for (unsigned int i = 0; i < mMeshArray.size(); i++)
	{
		mMeshArray[i]->Draw();
	}
}

//draw the meshes using a different material
void Model::Draw(GLShaderManager *shaderManager, const M3DMatrix44f &projection, M3DMatrix44f &modelView, M3DMatrix44f &mvpMatrix, Material* material) //Draw all the batches using a different material
{
	material->Use(shaderManager, projection, modelView, mvpMatrix);


	for (unsigned int i = 0; i < mMeshArray.size(); i++)
	{
		mMeshArray[i]->Draw();
	}
}