#include "ShaderTextureTileReplace.h"


ShaderTextureTileReplace::ShaderTextureTileReplace()
	:ShaderBase(ShaderType::SHADER_TEXTURE_TILE_REPLACE)
{

}
ShaderTextureTileReplace::~ShaderTextureTileReplace()
{

}

void ShaderTextureTileReplace::Initialize()
{
	mShaderID = gltLoadShaderPairWithAttributes(	"shaders/textureShaderTile.vp", "shaders/textureShaderTile.fp",
														2,
														GLT_ATTRIBUTE_VERTEX, "inVertex",
														GLT_ATTRIBUTE_TEXTURE0, "inUV");

	mLocTexture = glGetUniformLocation(mShaderID, "tex");
	mLocMVP = glGetUniformLocation(mShaderID, "mvpMatrix");
}
	
void ShaderTextureTileReplace::Use(M3DMatrix44f &mvpMatrix)
{
	glUseProgram(mShaderID);

	glUniform1i(mLocTexture, 0);
	glUniformMatrix4fv(mLocMVP, 1, GL_FALSE, *ShaderBase::msBoundMatrix);

	ShaderBase::Use(mvpMatrix);
}