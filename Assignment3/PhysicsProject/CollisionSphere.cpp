#include "CollisionSphere.h"

CollisionSphere::CollisionSphere()
{
	mRadius = 1.0f;
	mShape = Shape::Sphere;
}
CollisionSphere::CollisionSphere(float radius)
{
	mRadius = radius;
	mShape = Shape::Sphere;
}
CollisionSphere::CollisionSphere(const CollisionSphere &rhs)
{
	mRadius = rhs.mRadius;
	mShape = rhs.mShape;
}