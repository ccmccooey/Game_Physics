#ifndef _SHADER_GREY_SOLID
#define _SHADER_GREY_SOLID

#include "ShaderBase.h"

class ShaderGreySolid :public ShaderBase
{
private:
	GLint mLocMVP; //location of remote "mvpMatrix"

public:
	ShaderGreySolid();
	~ShaderGreySolid();

	virtual void Initialize();

	virtual void Use(M3DMatrix44f &mvpMatrix);	
};

#endif