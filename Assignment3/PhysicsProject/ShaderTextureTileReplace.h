#ifndef _SHADER_TEXTURE_TILE_REPLACE
#define _SHADER_TEXTYRE_TILE_REPLACE

#include "ShaderBase.h"

class ShaderTextureTileReplace :public ShaderBase
{
private:
	GLint mLocTexture; //location of remote location "tex"	
	GLint mLocMVP; //location of remote "mvpMatrix"

public:
	ShaderTextureTileReplace();
	~ShaderTextureTileReplace();

	virtual void Initialize();

	virtual void Use(M3DMatrix44f &mvpMatrix);	
};

#endif