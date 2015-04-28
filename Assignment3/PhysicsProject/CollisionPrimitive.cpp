#include "CollisionPrimitive.h"
#include "RigidBody.h"

Vector3f CollisionPrimitive::GetAxis(unsigned index) const
{
	//return mTransform.GetAxisVector(index);
	return mBody->GetTransformMatrix().GetAxisVector(index);
}
const Matrix44f& CollisionPrimitive::GetTransformMatrix() const
{
	return mTransform;
}