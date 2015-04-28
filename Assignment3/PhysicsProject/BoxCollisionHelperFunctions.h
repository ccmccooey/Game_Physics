#ifndef _BOX_COLLISION_HELPER_FUNCTIONS_H
#define _BOX_COLLISION_HELPER_FUNCTIONS_H

struct CollisionData;
class CollisionBox;

#include "Vector3f.h"

class BoxCollisionHelperFunctions
{
public:
	static float PenetrationOnAxis(const CollisionBox &one, const CollisionBox &two, const Vector3f &axis, const Vector3f &toCentre);
	static bool TryAxis(const CollisionBox &one, const CollisionBox &two, Vector3f axis, const Vector3f& toCentre, unsigned index, float& smallestPenetrationOut, unsigned &smallestCaseOut);
	static void FillPointFaceBoxBox(const CollisionBox &one, const CollisionBox &two, const Vector3f &toCentre, CollisionData *data, unsigned best, float pen);
	static Vector3f ContactPoint(const Vector3f &pOne, const Vector3f &dOne, float oneSize, const Vector3f &pTwo, const Vector3f &dTwo, float twoSize, bool useOne);
};

#endif