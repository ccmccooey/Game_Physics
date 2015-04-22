#ifndef _COLLIDER_H
#define _COLLIDER_H

class RigidBody;

#include "Matrix44f.h"
#include "Vector3f.h"

class CollisionPrimitive
{
public:
	// Pointer to owning rigid body.
	RigidBody* mBody;

	// Offset of primitive in local space of rigid body.
	Matrix44f mOffset;


private:
	Matrix44f mTransform;

public:
	Vector3f GetAxis(unsigned index) const;
};

#endif