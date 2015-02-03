/**********************************************************************
*	Author:  Christopher McCooey
*	Last Update:  January 16, 2015
*	Filename:  Material.cpp
*
*	Description:
*		This class represents a material to be used for 3D models. The material can store a texture and stores what shader is used.
*
*	Certification of Authenticity:
*		I certify that this assignment is entirely my own work.
**********************************************************************/

#include "Material.h"

GLfloat Material::msPointLight[4] = {1.0f, 1.0f, 1.0f, 1.0f};

//constructor
Material::Material()
{
	mColor = Color::White;
}
Material::Material(Texture* texture)
{
	mTexture = texture;
	mColor = Color::White;
}
Material::~Material()
{

}

//accessors
Texture* Material::getTexture() const
{
	return mTexture;
}
Color Material::getColor() const
{
	return mColor;
}

//setters
void Material::SetTexture(Texture* texture)
{
	if (texture != nullptr)
		mTexture = texture;
}
void Material::SetColor(const Color &color)
{
	mColor = color;
}
void Material::SetColor(float r, float g, float b, float a)
{
	mColor.Set(r, g, b, a);
}
void Material::SetColor(float r, float g, float b)
{
	mColor.Set(r, g, b, 1.0f);
}

void Material::Use(GLShaderManager* shaderManager, const M3DMatrix44f &projectionMatrix, M3DMatrix44f &modelViewMatrix, M3DMatrix44f &mvpMatrix)
{
	mTexture->BindTexture();

	//Solid Color
	//shaderManager->UseStockShader(GLT_SHADER_SHADED, mvpMatrix); 

	//Textures
	shaderManager->UseStockShader(GLT_SHADER_TEXTURE_REPLACE, mvpMatrix, 0);

	//Textures with Lighting
	/*
	GLfloat* vColor = NULL;
	mMaterial->getColor().ToColorArrayRGBA(vColor);
	
	shaderManager->UseStockShader(GLT_SHADER_TEXTURE_REPLACE, modelView, projection, Material::msPointLight, vColor, mMaterial->getTexture()->GetTextureInt());
	*/
}