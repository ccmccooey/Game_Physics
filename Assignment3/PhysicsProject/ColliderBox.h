#ifndef _COLLIDER_BOX_H
#define _COLLIDER_BOX_H

#include "CollisionPrimitive.h"
#include "Vector3f.h"

class CollisionBox :public CollisionPrimitive
{
public:
	Vector3f mHalfSize;
};

#endif