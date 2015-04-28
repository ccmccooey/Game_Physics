#ifndef _INTERSECTION_TEST_H
#define _INTERSECTION_TEST_H

#include "CollisionBox.h"
#include "CollisionPlane.h"

class IntersectionTests
{
public:
	static bool BoxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane);
};

#endif