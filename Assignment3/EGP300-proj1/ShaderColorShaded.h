#ifndef _SHADER_COLOR_SHADED
#define _SHADER_COLOR_SHADED

#include "ShaderBase.h"

class ShaderColorShaded :public ShaderBase
{
private:
	GLint mLocMVP; //location of remote "mvpMatrix"
	GLint mLocColor;  //location of remote "color"

public:
	ShaderColorShaded();
	~ShaderColorShaded();

	virtual void Initialize();

	virtual void Use(M3DMatrix44f &mvpMatrix);	
};

#endif