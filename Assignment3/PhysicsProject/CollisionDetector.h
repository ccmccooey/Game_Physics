#ifndef _COLLISION_DETECTOR_H
#define _COLLISION_DETECTOR_H

#include "CollisionData.h"
#include "ColliderSphere.h"

class CollisionDetector
{
	unsigned int CollisionDetector::sphereAndSphere(const ColliderSphere &one, const ColliderSphere &two, CollisionData *data);
};

#endif

