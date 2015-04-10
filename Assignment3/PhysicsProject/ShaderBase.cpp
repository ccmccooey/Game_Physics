#include "ShaderBase.h"

M3DMatrix44f* ShaderBase::msBoundMatrix = nullptr;
const Color* ShaderBase::msBoundColor = &Color::White;

ShaderBase::ShaderBase(ShaderType type)
	:mType(type)
{
	
}
ShaderBase::~ShaderBase()
{

}

void ShaderBase::Use(M3DMatrix44f &mvpMatrix)
{
	
}


ShaderType ShaderBase::GetType() const
{
	return mType;
}

//binding colors
void ShaderBase::BindMVPMatrix(M3DMatrix44f &mvpMatrix)
{
	ShaderBase::msBoundMatrix = &mvpMatrix;
}
void ShaderBase::BindColor(const Color &color)
{
	ShaderBase::msBoundColor = &color;
}