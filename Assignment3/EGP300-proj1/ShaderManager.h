#ifndef _SHADER_MANAGER_H
#define _SHADER_MANAGER_H

#include "ShaderType.h"

class ShaderBase;

class ShaderManager
{
private:
	ShaderBase** mShaders;
	int mShaderCount;

public:
	ShaderManager();
	~ShaderManager();

	void CreateShaders();

	ShaderBase* GetShaderPtr(ShaderType type) const;

private:
	void AddShader(ShaderBase* shader);
};

#endif
