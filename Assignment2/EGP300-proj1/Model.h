/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Model.h
*
*	Description:
*		This class represents a 3D model. The class can store multiple meshes to be drawn. It also stores a material which determines what textures and shaders the model uses.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _MODEL_H
#define _MODEL_H

#include <vector>
#include "Geometry.h"
#include "GLfiles.h"

class Mesh;
class Material;

class Model
{
private:
	bool mBad;
	Material* mMaterial;

public:
	//constructors
	Model();
	Model(Material* material);
	Model(Geometry geometryType);
	Model(Material* material, Geometry geometryType);
	~Model();

	//accessors
	unsigned int getMeshCount() const;

	//setters

	//draw functions
	void Draw(GLShaderManager *shaderManager, const M3DMatrix44f &projection, M3DMatrix44f &modelView, M3DMatrix44f &mvpMatrix); //Draw all the batches
	void Draw(GLShaderManager *shaderManager, const M3DMatrix44f &projection, M3DMatrix44f &modelView, M3DMatrix44f &mvpMatrix, Material* material); //Draw all the batches using a different material

private:
	void CleanMeshData();
	void InitializeBuiltInGeometry(Geometry geometryType);

private:
	std::vector<Mesh*> mMeshArray;
};

#endif