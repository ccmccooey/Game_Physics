#include "ShaderTextureColor.h"


ShaderTextureColor::ShaderTextureColor()
	:ShaderBase(ShaderType::SHADER_TEXTURE_COLOR)
{

}
ShaderTextureColor::~ShaderTextureColor()
{

}

void ShaderTextureColor::Initialize()
{
	mShaderID = gltLoadShaderPairWithAttributes(	"shaders/textureColorShader.vp", "shaders/textureColorShader.fp",
														2,
														GLT_ATTRIBUTE_VERTEX, "inVertex",
														GLT_ATTRIBUTE_TEXTURE0, "inUV");

	mLocTexture = glGetUniformLocation(mShaderID, "tex");
	mLocMVP = glGetUniformLocation(mShaderID, "mvpMatrix");
	mLocColor = glGetUniformLocation(mShaderID, "color");
}
	
void ShaderTextureColor::Use(M3DMatrix44f &mvpMatrix)
{
	glUseProgram(mShaderID);

	glUniform1i(mLocTexture, 0);
	glUniform4f(mLocColor, ShaderBase::msBoundColor->R(), ShaderBase::msBoundColor->G(), ShaderBase::msBoundColor->B(), ShaderBase::msBoundColor->A());	
	glUniformMatrix4fv(mLocMVP, 1, GL_FALSE, *ShaderBase::msBoundMatrix);

	ShaderBase::Use(mvpMatrix);
}