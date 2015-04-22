#ifndef _COLLISION_PLANE_H
#define _COLLISION_PLANE_H

#include "CollisionPrimitive.h"

class CollisionPlane :public CollisionPrimitive
{
public:
	/**
	* The plane normal
	*/
	Vector3f mNormal;

	/**
	* The distance of the plane from the origin.
	*/
	float mOffset;

};

#endif