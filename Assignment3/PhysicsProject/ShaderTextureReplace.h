#ifndef _SHADER_TEXTURE_REPLACE
#define _SHADER_TEXTYRE_REPLACE

#include "ShaderBase.h"

class ShaderTextureReplace :public ShaderBase
{
private:
	GLint mLocTexture; //location of remote location "tex"	
	GLint mLocMVP; //location of remote "mvpMatrix"

public:
	ShaderTextureReplace();
	~ShaderTextureReplace();

	virtual void Initialize();

	virtual void Use(M3DMatrix44f &mvpMatrix);	
};

#endif