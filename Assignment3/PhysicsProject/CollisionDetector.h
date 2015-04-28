#ifndef _COLLISION_DETECTOR_H
#define _COLLISION_DETECTOR_H

#include "CollisionData.h"
#include "CollisionSphere.h"
#include "CollisionBox.h"
#include "CollisionPlane.h"

class CollisionDetector
{
private:
	static unsigned long iterations;

public:
	//sphere collisions
	static unsigned int SphereAndSphere(const CollisionSphere &one, const CollisionSphere &two, CollisionData *data);
	static unsigned int SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *data);
	static unsigned int SphereAndTruePlane(const CollisionSphere &sphere, const CollisionPlane &plane,CollisionData *data);

	//box collisions
	static unsigned int BoxAndPoint(const CollisionBox &box, const Vector3f &point, CollisionData *data);
	static unsigned int BoxAndSphere(const CollisionBox &box, const CollisionSphere &sphere, CollisionData *data);
	static unsigned int BoxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane, CollisionData *data);
	static unsigned int BoxAndBox(const CollisionBox &one, const CollisionBox &two, CollisionData *data);

	//this function will figure out which collision function to call
	static unsigned int PrimitiveAndPrimitive(CollisionPrimitive* a, CollisionPrimitive* b);

private:
	
};

#endif

