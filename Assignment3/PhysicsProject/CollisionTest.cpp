#include "CollisionTest.h"



bool CollisionTest::CollisionBoxSphere(const ColliderBox &box, const ColliderSphere &sphere)
{
	

	Vector3f relCentre = box.transform.transformInverse(centre);
    
	Vector3f closestPt(0,0,0);
	float dist;

	// Clamp each coordinate to the box.
	dist = relCentre.x;
	if (dist > box.mHalfSize.x) dist = box.mHalfSize.x;
	if (dist < -box.mHalfSize.x) dist = -box.mHalfSize.x;
	closestPt.x = dist;

	dist = relCentre.y;
	if (dist > box.mHalfSize.y) dist = box.mHalfSize.y;
	if (dist < -box.mHalfSize.y) dist = -box.mHalfSize.y;
	closestPt.y = dist;

	dist = relCentre.z;
	if (dist > box.mHalfSize.z) dist = box.mHalfSize.z;
	if (dist < -box.mHalfSize.z) dist = -box.mHalfSize.z;
	closestPt.z = dist;

	// Check we're in contact
	dist = (closestPt - relCentre).LengthSquared();
	if (dist > sphere.mRadius * sphere.mRadius) 
		{
			return 0;
	}

	// Compile the contact
	Vector3f closestPtWorld = box.transform.transform(closestPt);
}