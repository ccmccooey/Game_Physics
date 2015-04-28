#include "CollisionPlane.h"

CollisionPlane::CollisionPlane()
{
	mNormal = Vector3f::unitY;
	mOffset = 0.0f;
	mShape = Shape::Plane;
}
CollisionPlane::CollisionPlane(const Vector3f &normal, float offset, bool plane)
{
	mNormal = normal;
	mOffset = offset;
	if (plane)
	{
		mShape = Shape::Plane;
	}
	else
	{
		mShape = Shape::Half_Space;
	}
}
CollisionPlane::CollisionPlane(const CollisionPlane &rhs)
{
	mNormal = rhs.mNormal;
	mOffset = rhs.mOffset;
	mShape = rhs.mShape;;
}