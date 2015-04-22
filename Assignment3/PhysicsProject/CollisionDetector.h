#ifndef _COLLISION_DETECTOR_H
#define _COLLISION_DETECTOR_H

#include "CollisionData.h"
#include "CollisionSphere.h"
#include "CollisionPlane.h"

class CollisionDetector
{
	static unsigned int SphereAndSphere(const CollisionSphere &one, const CollisionSphere &two, CollisionData *data);
	static unsigned int SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *data);
	static unsigned int SphereAndTruePlane(const CollisionSphere &sphere, const CollisionPlane &plane,CollisionData *data);
};

#endif

