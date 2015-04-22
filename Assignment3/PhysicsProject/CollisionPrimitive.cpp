#include "CollisionPrimitive.h"


Vector3f CollisionPrimitive::GetAxis(unsigned index) const
{
	return mTransform.GetAxisVector(index);
}