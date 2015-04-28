#include "CollisionSphere.h"

CollisionSphere::CollisionSphere()
{
	mRadius = 1.0f;
}
CollisionSphere::CollisionSphere(float radius)
{
	mRadius = radius;
}
CollisionSphere::CollisionSphere(const CollisionSphere &rhs)
{
	mRadius = rhs.mRadius;
}