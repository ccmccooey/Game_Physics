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

#include "GraphicsSystem.h"
#include "Material.h"
#include "ShaderBase.h"

GLfloat Material::msPointLight[4] = {1.0f, 1.0f, 1.0f, 1.0f};

//constructors
Material::Material()
{
	Initialize(ShaderType::SHADER_GREY_SHADED, nullptr, Color::White);
}
Material::Material(Texture* texture)
{
	Initialize(ShaderType::SHADER_TEXTURE_REPLACE, texture, Color::White);
}
Material::Material(const Color &color)
{
	Initialize(ShaderType::SHADER_COLOR_SHADED, nullptr, color);
}
Material::Material(Texture* texture, const Color &color)
{
	Initialize(ShaderType::SHADER_TEXTURE_COLOR, texture, color);
}
Material::Material(Texture* texture, ShaderType type, const Color &color)
{
	Initialize(type, texture, color);
}
Material::Material(const Material &rhs)
{
	Initialize(rhs.getShaderType(), rhs.mTexture, rhs.mColor);
}
Material::~Material()
{

}
void Material::Initialize(ShaderType type, Texture* texture, const Color &color)
{
	mTexture = texture;
	mColor = color;
	SetShader(type);
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
ShaderBase* Material::getShader() const
{
	return mShader;
}
ShaderType Material::getShaderType() const
{
	return mShader->GetType();
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
void Material::SetShader(ShaderType type)
{
	mShader = GraphicsSystem::GetShader(type);
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
void Material::Use(const M3DMatrix44f &projectionMatrix, M3DMatrix44f &modelViewMatrix, M3DMatrix44f &mvpMatrix)
{
	if (mTexture != nullptr)
		mTexture->BindTexture();

	mShader->Use(mvpMatrix);
}