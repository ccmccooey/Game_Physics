#ifndef _SHADER_BASE_H
#define _SHADER_BASE_H

#include "GLFiles.h"
#include "ShaderType.h"

class ShaderBase
{
protected:
	const ShaderType mType;
	GLint mShaderID;

protected:
	ShaderBase(ShaderType type);

	virtual void Initialize();

public:
	virtual ~ShaderBase();

	virtual void Use(M3DMatrix44f &mvpMatrix)=0;

	ShaderType GetType() const;

};

#endif