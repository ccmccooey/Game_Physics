#ifndef _SHADER_TEXTURE_COLOR
#define _SHADER_TEXTYRE_COLOR

#include "ShaderBase.h"

class ShaderTextureColor :public ShaderBase
{
private:
	GLint mLocTexture; //location of remote location "tex"	
	GLint mLocMVP; //location of remote "mvpMatrix"
	GLint mLocColor;  //location of remote "color"

public:
	ShaderTextureColor();
	~ShaderTextureColor();

	virtual void Initialize();

	virtual void Use(M3DMatrix44f &mvpMatrix);	
};

#endif