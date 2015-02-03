/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Material.h
*
*	Description:
*		This class represents a material to be used for 3D models. The material can store a texture and stores what shader is used.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Color.h"
#include "Texture.h"
#include "GLfiles.h"

class Material
{
private:
	Texture *mTexture;
	Color mColor;

public:
	static GLfloat msPointLight[4];

public:
	Material();
	Material(Texture* texture);
	~Material();

	//accessors
	Texture* getTexture() const;
	Color getColor() const;

	//setters
	void SetColor(const Color &color);
	void SetColor(float r, float g, float b, float a);
	void SetColor(float r, float g, float b);

	void SetTexture(Texture* texture);

	//use the material, this is called in the draw function
	void Use(GLShaderManager* shaderManager, const M3DMatrix44f &projectionMatrix, M3DMatrix44f &modelViewMatrix, M3DMatrix44f &mvpMatrix);
};


#endif
