#include "CollisionBox.h"

CollisionBox::CollisionBox()
{
	mHalfSize = Vector3f::one;
	mShape = Shape::Box;
}
CollisionBox::CollisionBox(const Vector3f &halfSize)
{
	mHalfSize = halfSize;
	mShape = Shape::Box;
}
CollisionBox::CollisionBox(float halfSizeX, float halfSizeY, float halfSizeZ)
{
	mHalfSize = Vector3f(halfSizeX, halfSizeY, halfSizeZ);
	mShape = Shape::Box;
}
CollisionBox::CollisionBox(const CollisionBox &rhs)
{
	mHalfSize = rhs.mHalfSize;
	mShape = rhs.mShape;
}