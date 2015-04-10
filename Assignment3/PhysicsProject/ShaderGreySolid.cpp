#include "ShaderGreySolid.h"


ShaderGreySolid::ShaderGreySolid()
	:ShaderBase(ShaderType::SHADER_GREY_SOLID)
{

}
ShaderGreySolid::~ShaderGreySolid()
{

}

void ShaderGreySolid::Initialize()
{
	mShaderID = gltLoadShaderPairWithAttributes(	"shaders/greySolidShader.vp", "shaders/greySolidShader.fp",
														1,
														GLT_ATTRIBUTE_VERTEX, "inVertex");												

	mLocMVP = glGetUniformLocation(mShaderID, "mvpMatrix");
}
	
void ShaderGreySolid::Use(M3DMatrix44f &mvpMatrix)
{
	glUseProgram(mShaderID);
	glUniformMatrix4fv(mLocMVP, 1, GL_FALSE, *ShaderBase::msBoundMatrix);

	ShaderBase::Use(mvpMatrix);
}