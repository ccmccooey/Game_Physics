/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  DisplayObject3D.h
*
*	Description:
*		This class represents a 3D display object.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _DISPLAY_OBJECT_3D_H
#define _DISPLAY_OBJECT_3D_H

#include "GLfiles.h"
#include "Transform.h"

class Material;
class Model;

class DisplayObject3D
{
		//member types
private:
	Model* mModel;
	Material* mMaterial;

protected:
	Transform* mTransform;
	
public:
	
	DisplayObject3D(Model* model);
	DisplayObject3D(const DisplayObject3D &rhs);
	~DisplayObject3D();

	//setters
	void SetMaterial(Material* material);
	void RemoveMaterial();

	//accessors
	Transform* getTransform();
	
	//Draw the object
	void Draw(GLShaderManager &shaderManager, const M3DMatrix44f &frustum, M3DMatrix44f &view);

};

#endif