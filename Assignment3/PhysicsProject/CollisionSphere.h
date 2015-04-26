#ifndef _COLLISION_SPHERE_H
#define _COLLISION_SPHERE_H

#include "CollisionPrimitive.h"

class CollisionSphere :public CollisionPrimitive
{
public:
	float mRadius;

public:
	CollisionSphere();
	CollisionSphere(float radius);
	CollisionSphere(const CollisionSphere &rhs);
};

#endif