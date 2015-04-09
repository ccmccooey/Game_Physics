#include "ShaderManager.h"
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

	//texture replace shader
	ShaderTextureReplace* shaderTextureReplace = new ShaderTextureReplace();
	shaderTextureReplace->Initialize();
	mShaders[(unsigned int)shaderTextureReplace->GetType()] = shaderTextureReplace;

	//texture replace shader
	ShaderTextureColor* shaderTextureColor = new ShaderTextureColor();
	shaderTextureColor->Initialize();
	mShaders[(unsigned int)shaderTextureColor->GetType()] = shaderTextureColor;
}

ShaderBase* ShaderManager::GetShaderPtr(ShaderType type) const
{
	return mShaders[(unsigned int)type];
}