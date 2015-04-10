#include "ShaderColorSolid.h"


ShaderColorSolid::ShaderColorSolid()
	:ShaderBase(ShaderType::SHADER_COLOR_SOLID)
{

}
ShaderColorSolid::~ShaderColorSolid()
{

}

void ShaderColorSolid::Initialize()
{
	mShaderID = gltLoadShaderPairWithAttributes(	"shaders/colorSolidShader.vp", "shaders/colorSolidShader.fp",
														1,
														GLT_ATTRIBUTE_VERTEX, "inVertex");												

	mLocMVP = glGetUniformLocation(mShaderID, "mvpMatrix");
	mLocColor = glGetUniformLocation(mShaderID, "color");
}
	
void ShaderColorSolid::Use(M3DMatrix44f &mvpMatrix)
{
	glUseProgram(mShaderID);

	glUniform4f(mLocColor, ShaderBase::msBoundColor->R(), ShaderBase::msBoundColor->G(), ShaderBase::msBoundColor->B(), ShaderBase::msBoundColor->A());	
	glUniformMatrix4fv(mLocMVP, 1, GL_FALSE, *ShaderBase::msBoundMatrix);

	ShaderBase::Use(mvpMatrix);
}