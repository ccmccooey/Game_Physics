#ifndef _COLLIDER_BOX_H
#define _COLLIDER_BOX_H

#include "Collider.h"
#include "Vector3f.h"

class ColliderBox :public Collider
{
public:
	Vector3f mHalfSize;

	bool HitTest(const Collider &other) const;
};

#endif