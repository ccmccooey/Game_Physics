#ifndef _COLLIDER_H
#define _COLLIDER_H

class RigidBody;

#include "Matrix44f.h"
#include "Vector3f.h"

class CollisionPrimitive
{
protected:
	enum Shape
	{
		Invalid = 0,
		Half_Space,
		Plane,
		Sphere,
		Box
	};
public:
	// Pointer to owning rigid body.
	RigidBody* mBody;

	// Offset of primitive in local space of rigid body.
	Matrix44f mOffset;

protected:
	Shape mShape;

private:
	Matrix44f mTransform;	

public:
	Vector3f GetAxis(unsigned index) const;
	const Matrix44f& GetTransformMatrix() const;
	Shape GetShape() const;
	
	bool IsHalfSpace() const;
	bool IsPlane() const;
	bool IsSphere() const;
	bool IsBox() const;
};

#endif