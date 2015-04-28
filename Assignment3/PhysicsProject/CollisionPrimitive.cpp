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

CollisionPrimitive::Shape CollisionPrimitive::GetShape() const
{
	return mShape;
}

bool CollisionPrimitive::IsHalfSpace() const
{
	return mShape == Shape::Half_Space;
}
bool CollisionPrimitive::IsPlane() const
{
	return mShape == Shape::Plane;
}
bool CollisionPrimitive::IsSphere() const
{
	return mShape == Shape::Sphere;
}
bool CollisionPrimitive::IsBox() const
{
	return mShape == Shape::Box;
}