#include "ShaderBase.h"


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