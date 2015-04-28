#ifndef _COLLISION_BOX_H
#define _COLLISION_BOX_H

#include "CollisionPrimitive.h"
#include "Vector3f.h"

class CollisionBox :public CollisionPrimitive
{
public:
	Vector3f mHalfSize;

	CollisionBox();
	CollisionBox(const Vector3f &halfSize);
	CollisionBox(float halfSizeX, float halfSizeY, float halfSizeZ);
	CollisionBox(const CollisionBox &rhs);
};

#endif