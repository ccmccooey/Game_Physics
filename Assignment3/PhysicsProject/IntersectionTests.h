#ifndef _INTERSECTION_TEST_H
#define _INTERSECTION_TEST_H

class CollisionBox;
class CollisionSphere;
class CollisionPlane;

class IntersectionTests
{
public:
	static bool SphereAndSphere(const CollisionSphere &one,const CollisionSphere &two);
	static bool SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane);
	static bool BoxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane);
};

#endif