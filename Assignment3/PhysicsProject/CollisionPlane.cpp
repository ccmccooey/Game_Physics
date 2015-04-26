#include "CollisionPlane.h"

CollisionPlane::CollisionPlane()
{
	mNormal = Vector3f::unitY;
	mOffset = 0.0f;
}
CollisionPlane::CollisionPlane(const Vector3f &normal, float offset)
{
	mNormal = normal;
	mOffset = offset;
}
CollisionPlane::CollisionPlane(const CollisionPlane &rhs)
{
	mNormal = rhs.mNormal;
	mOffset = rhs.mOffset;
}