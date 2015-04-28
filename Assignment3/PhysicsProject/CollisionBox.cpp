#include "CollisionBox.h"

CollisionBox::CollisionBox()
{
	mHalfSize = Vector3f::one;
}
CollisionBox::CollisionBox(const Vector3f &halfSize)
{
	mHalfSize = halfSize;
}
CollisionBox::CollisionBox(float halfSizeX, float halfSizeY, float halfSizeZ)
{
	mHalfSize = Vector3f(halfSizeX, halfSizeY, halfSizeZ);
}
CollisionBox::CollisionBox(const CollisionBox &rhs)
{
	mHalfSize = rhs.mHalfSize;
}