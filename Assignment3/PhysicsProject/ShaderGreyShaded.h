#ifndef _SHADER_GREY_SHADED
#define _SHADER_GREY_SHADED

#include "ShaderBase.h"

class ShaderGreyShaded :public ShaderBase
{
private:
	GLint mLocMVP; //location of remote "mvpMatrix"

public:
	ShaderGreyShaded();
	~ShaderGreyShaded();

	virtual void Initialize();

	virtual void Use(M3DMatrix44f &mvpMatrix);	
};

#endif