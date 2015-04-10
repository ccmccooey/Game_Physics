#include "ShaderTextureReplace.h"


ShaderTextureReplace::ShaderTextureReplace()
	:ShaderBase(ShaderType::SHADER_TEXTURE_REPLACE)
{

}
ShaderTextureReplace::~ShaderTextureReplace()
{

}

void ShaderTextureReplace::Initialize()
{
	mShaderID = gltLoadShaderPairWithAttributes(	"shaders/textureShader.vp", "shaders/textureShader.fp",
														2,
														GLT_ATTRIBUTE_VERTEX, "inVertex",
														GLT_ATTRIBUTE_TEXTURE0, "inUV");

	mLocTexture = glGetUniformLocation(mShaderID, "tex");
	mLocMVP = glGetUniformLocation(mShaderID, "mvpMatrix");
}
	
void ShaderTextureReplace::Use(M3DMatrix44f &mvpMatrix)
{
	glUseProgram(mShaderID);

	glUniform1i(mLocTexture, 0);
	glUniformMatrix4fv(mLocMVP, 1, GL_FALSE, *ShaderBase::msBoundMatrix);

	ShaderBase::Use(mvpMatrix);
}




