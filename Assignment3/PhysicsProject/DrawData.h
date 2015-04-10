#ifndef _DRAW_DATA_H
#define _DRAW_DATA_H

class ShaderManager;
class GLShaderManager;

#include "TextRenderer.h"

//data structure class contains all things necessary in draw calls, its easier because now the draw only passes a pointer to this rather than lots of parameters
struct DrawData
{
public:
	GLShaderManager *stockShaders;
	ShaderManager *shaderManager;
	const M3DMatrix44f *frustum; 
	M3DMatrix44f *view; 
	TextRenderer* textRenderer;

	DrawData();
	~DrawData();
};

#endif