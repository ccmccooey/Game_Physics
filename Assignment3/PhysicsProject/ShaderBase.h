#ifndef _SHADER_BASE_H
#define _SHADER_BASE_H

#include "GLFiles.h"
#include "ShaderType.h"
#include "Color.h"

class ShaderBase
{
protected:
	const ShaderType mType;
	GLint mShaderID;

	static const Color* msBoundColor;
	static M3DMatrix44f* msBoundMatrix;

protected:
	ShaderBase(ShaderType type);

public:
	virtual void Initialize()=0;

public:
	virtual ~ShaderBase();

	virtual void Use(M3DMatrix44f &mvpMatrix)=0;

	ShaderType GetType() const;

	static void BindMVPMatrix(M3DMatrix44f &mvpMatrix);
	static void BindColor(const Color &color);
};

#endif