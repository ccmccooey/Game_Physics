#include "ShaderManager.h"
#include "ShaderGreySolid.h"
#include "ShaderGreyShaded.h"
#include "ShaderColorSolid.h"
#include "ShaderColorShaded.h"
#include "ShaderTextureReplace.h"
#include "ShaderTextureColor.h"

ShaderManager::ShaderManager()
{
	CreateShaders();
}
ShaderManager::~ShaderManager()
{
	for (int i = 0; i < mShaderCount; i++)
	{
		if (mShaders[i] != nullptr)
		{
			delete mShaders[i];
			mShaders[i] = nullptr;
		}
	}
	delete [] mShaders;
}

void ShaderManager::CreateShaders()
{
	//create shader data structure
	mShaderCount = (int)ShaderType::TOTAL_SHADERS;
	mShaders = new ShaderBase*[mShaderCount];

	//set all shaders to null first
	for (int i = 0; i < mShaderCount; i++)
		mShaders[i] = nullptr;

	//create all the shaders
	
	//grey solid shader
	ShaderGreySolid* shaderGreySolid = new ShaderGreySolid();
	AddShader(shaderGreySolid);

	//grey shaded shader
	ShaderGreyShaded* shaderGreyShaded = new ShaderGreyShaded();
	AddShader(shaderGreyShaded);

	//color solid shader
	ShaderColorSolid* shaderColorSolid = new ShaderColorSolid();
	AddShader(shaderColorSolid);

	//color shaded shader
	ShaderColorShaded* shaderColorShaded = new ShaderColorShaded();
	AddShader(shaderColorShaded);

	//texture replace shader
	ShaderTextureReplace* shaderTextureReplace = new ShaderTextureReplace();
	AddShader(shaderTextureReplace);

	//texture replace shader
	ShaderTextureColor* shaderTextureColor = new ShaderTextureColor();
	AddShader(shaderTextureColor);
}
void ShaderManager::AddShader(ShaderBase* shader)
{
	shader->Initialize();
	mShaders[(unsigned int)shader->GetType()] = shader;
}

ShaderBase* ShaderManager::GetShaderPtr(ShaderType type) const
{
	return mShaders[(unsigned int)type];
}