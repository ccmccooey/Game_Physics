#include "ShaderColorShaded.h"


ShaderColorShaded::ShaderColorShaded()
	:ShaderBase(ShaderType::SHADER_COLOR_SHADED)
{

}
ShaderColorShaded::~ShaderColorShaded()
{

}

void ShaderColorShaded::Initialize()
{
	mShaderID = gltLoadShaderPairWithAttributes(	"shaders/colorShadedShader.vp", "shaders/colorShadedShader.fp",
														2,
														GLT_ATTRIBUTE_VERTEX, "inVertex",
														GLT_ATTRIBUTE_TEXTURE0, "inUV");

	mLocMVP = glGetUniformLocation(mShaderID, "mvpMatrix");
	mLocColor = glGetUniformLocation(mShaderID, "color");
}
	
void ShaderColorShaded::Use(M3DMatrix44f &mvpMatrix)
{
	glUseProgram(mShaderID);

	glUniform4f(mLocColor, ShaderBase::msBoundColor->R(), ShaderBase::msBoundColor->G(), ShaderBase::msBoundColor->B(), ShaderBase::msBoundColor->A());	
	glUniformMatrix4fv(mLocMVP, 1, GL_FALSE, *ShaderBase::msBoundMatrix);

	ShaderBase::Use(mvpMatrix);
}