#ifndef _COLLIDER_H
#define _COLLIDER_H

class RigidBody;

#include "Matrix44f.h"

class Collider
{
public:
	// Pointer to owning rigid body.
	RigidBody* mBody;

	// Offset of primitive in local space of rigid body.
	Matrix44f mOffset;

	virtual bool HitTest(const Collider &other) const=0;
};

#endif