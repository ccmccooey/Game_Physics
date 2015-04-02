#include "ShaderManager.h"
#include "ShaderTextureReplace.h"

ShaderManager::ShaderManager()
{

}
ShaderManager::~ShaderManager()
{
	for (int i = 0; i < mShaderCount; i++)
	{
		delete mShaders[i];
	}
	delete [] mShaders;
}

void ShaderManager::CreateShaders()
{
	//create shader data structure
	mShaderCount = (int)ShaderType::TOTAL_SHADERS;
	mShaders = new ShaderBase*[mShaderCount];

	//create all the shaders

	//texture replace shader
	ShaderTextureReplace* shaderTextureReplace = new ShaderTextureReplace();
	mShaders[(unsigned int)shaderTextureReplace->GetType()] = shaderTextureReplace;
}

ShaderBase* ShaderManager::GetShaderPtr(ShaderType type) const
{
	return mShaders[(unsigned int)type];
}