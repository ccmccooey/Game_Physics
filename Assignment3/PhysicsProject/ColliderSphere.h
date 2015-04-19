#ifndef _COLLIDER_SPHERE_H
#define _COLLIDER_SPHERE_H

#include "Collider.h"

class ColliderSphere :public Collider
{
public:
	float mRadius;

	bool HitTest(const Collider &other) const;
};

#endif