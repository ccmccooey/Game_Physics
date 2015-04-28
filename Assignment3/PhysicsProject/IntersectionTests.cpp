#include "IntersectionTests.h"
#include "CollisionBox.h"
#include "CollisionGeometries.h"

static inline float TransformToAxis(const CollisionBox &box, const Vector3f &axis)
{
    return
		box.mHalfSize.x * fabs(Vector3f::DotProduct(axis, box.GetAxis(0))) +
        box.mHalfSize.y * fabs(Vector3f::DotProduct(axis, box.GetAxis(1))) +
        box.mHalfSize.z * fabs(Vector3f::DotProduct(axis, box.GetAxis(2)));
}

bool IntersectionTests::SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane)
{
    // Find the distance from the origin
	float ballDistance = Vector3f::DotProduct(plane.mNormal, sphere.GetAxis(3)) - sphere.mRadius;

    // Check for the intersection
    return ballDistance <= plane.mOffset;
}

bool IntersectionTests::SphereAndSphere(const CollisionSphere &one,const CollisionSphere &two)
{
    // Find the vector between the objects
    Vector3f midline = one.GetAxis(3) - two.GetAxis(3);

    // See if it is large enough.
	return midline.LengthSquared() < (one.mRadius + two.mRadius) * (one.mRadius + two.mRadius);
}

bool IntersectionTests::BoxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane)
{
	 // Work out the projected radius of the box onto the plane direction
	float projectedRadius = TransformToAxis(box, plane.mNormal);

    // Work out how far the box is from the origin
    float boxDistance = Vector3f::DotProduct(plane.mNormal, box.GetAxis(3)) - projectedRadius;

    // Check for the intersection
    return boxDistance <= plane.mOffset;
}