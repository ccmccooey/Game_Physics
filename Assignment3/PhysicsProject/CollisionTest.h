#ifndef _COLLISION_TEST_H
#define _COLLISION_TEST_H

#include "ColliderBox.h"
#include "ColliderSphere.h"

class CollisionTest
{
	static bool CollisionBoxSphere(const ColliderBox &box, const ColliderSphere &sphere);
};

#endif