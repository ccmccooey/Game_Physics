#ifndef _SHADER_COLOR_SOLID
#define _SHADER_COLOR_SOLID

#include "ShaderBase.h"

class ShaderColorSolid :public ShaderBase
{
private:
	GLint mLocMVP; //location of remote "mvpMatrix"
	GLint mLocColor;  //location of remote "color"

public:
	ShaderColorSolid();
	~ShaderColorSolid();

	virtual void Initialize();

	virtual void Use(M3DMatrix44f &mvpMatrix);	
};

#endif