#include "ShaderGreyShaded.h"


ShaderGreyShaded::ShaderGreyShaded()
	:ShaderBase(ShaderType::SHADER_GREY_SHADED)
{

}
ShaderGreyShaded::~ShaderGreyShaded()
{

}

void ShaderGreyShaded::Initialize()
{
	mShaderID = gltLoadShaderPairWithAttributes(	"shaders/greyShadedShader.vp", "shaders/greyShadedShader.fp",
														2,
														GLT_ATTRIBUTE_VERTEX, "inVertex",
														GLT_ATTRIBUTE_TEXTURE0, "inUV");

	mLocMVP = glGetUniformLocation(mShaderID, "mvpMatrix");
}
	
void ShaderGreyShaded::Use(M3DMatrix44f &mvpMatrix)
{
	glUseProgram(mShaderID);
	glUniformMatrix4fv(mLocMVP, 1, GL_FALSE, *ShaderBase::msBoundMatrix);

	ShaderBase::Use(mvpMatrix);
}