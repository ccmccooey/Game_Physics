#include "BoxCollisionHelperFunctions.h"
#include "CollisionBox.h"
#include "CollisionData.h"
#include "Contact.h"

static inline float TransformToAxis(const CollisionBox &box, const Vector3f &axis)
{
    return
		box.mHalfSize.x * fabs(Vector3f::DotProduct(axis, box.GetAxis(0))) +
        box.mHalfSize.y * fabs(Vector3f::DotProduct(axis, box.GetAxis(1))) +
        box.mHalfSize.z * fabs(Vector3f::DotProduct(axis, box.GetAxis(2)));
}

//most of this is the book's code
float BoxCollisionHelperFunctions::PenetrationOnAxis(const CollisionBox &one, const CollisionBox &two, const Vector3f &axis, const Vector3f &toCentre)
{
    // Project the half-size of one onto axis
    float oneProject = TransformToAxis(one, axis);
    float twoProject = TransformToAxis(two, axis);

    // Project this onto the axis
	float distance = fabs(Vector3f::DotProduct(toCentre, axis));

    // Return the overlap (i.e. positive indicates
    // overlap, negative indicates separation).
    return oneProject + twoProject - distance;
}


bool BoxCollisionHelperFunctions::TryAxis(const CollisionBox &one, const CollisionBox &two, Vector3f axis, const Vector3f& toCentre, unsigned index, float& smallestPenetration, unsigned int &smallestCase)
{
    // Make sure we have a normalized axis, and don't check almost parallel axes
	if (axis.LengthSquared() < 0.0001f)
	{
		return true;
	}
	axis.Normalize();

    float penetrationDepth = BoxCollisionHelperFunctions::PenetrationOnAxis(one, two, axis, toCentre);

    if (penetrationDepth < 0)
	{
		return false;
	}
    if (penetrationDepth < smallestPenetration) 
	{
        smallestPenetration = penetrationDepth;
        smallestCase = index;
    }
    return true;
}

void BoxCollisionHelperFunctions::FillPointFaceBoxBox(const CollisionBox &one, const CollisionBox &two, const Vector3f &toCentre, CollisionData *data, unsigned int best, float pen)
{
    // This method is called when we know that a vertex from box two is in contact with box one.
    Contact* contact = data->mContacts;

    // We know which axis the collision is on (i.e. best), but we need to work out which of the two faces on this axis.
    Vector3f normal = one.GetAxis(best);
    //if (one.GetAxis(best) * toCentre > 0)
	if (Vector3f::DotProduct(one.GetAxis(best), toCentre) > 0.0f)
    {
        normal *= -1.0f;
    }

    // Work out which vertex of box two we're colliding with.
    // Using toCentre doesn't work!
    Vector3f vertex = two.mHalfSize;
    if (Vector3f::DotProduct(two.GetAxis(0), normal) < 0)
	{
		vertex.x = -vertex.x;
	}
    if (Vector3f::DotProduct(two.GetAxis(1), normal) < 0)
	{
		vertex.y = -vertex.y;
	}
    if (Vector3f::DotProduct(two.GetAxis(2), normal) < 0)
	{
		vertex.z = -vertex.z;
	}

    // Create the contact data
    contact->mContactNormal = normal;
    contact->mPenetrationDepth = pen;
	contact->mContactPoint = two.GetTransformMatrix() * vertex;
	contact->SetBodyData(one.mBody, two.mBody, data->mGlobalFriction, data->mGlobalRestitution);
}

Vector3f BoxCollisionHelperFunctions::ContactPoint(const Vector3f &pOne, const Vector3f &dOne, float oneSize, const Vector3f &pTwo, const Vector3f &dTwo, float twoSize, bool useOne) // (useOne) If this is true, and the contact point is outside the edge (in the case of an edge-face contact) then we use one's midpoint, otherwise we use two's.  
{
    Vector3f toSt, cOne, cTwo;
    float dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
    float denom, mua, mub;

	smOne = dOne.LengthSquared();
    smTwo = dTwo.LengthSquared();
	dpOneTwo = Vector3f::DotProduct(dTwo, dOne);

    toSt = pOne - pTwo;
    dpStaOne = Vector3f::DotProduct(dOne, toSt);
    dpStaTwo = Vector3f::DotProduct(dTwo, toSt);

    denom = smOne * smTwo - dpOneTwo * dpOneTwo;

    // Zero denominator indicates parrallel lines
    if (fabs(denom) < 0.0001f) 
	{
        return useOne?pOne:pTwo;
    }

    mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
    mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

    // If either of the edges has the nearest point out
    // of bounds, then the edges aren't crossed, we have
    // an edge-face contact. Our point is on the edge, which
    // we know from the useOne parameter.
    if (mua > oneSize || mua < -oneSize || mub > twoSize || mub < -twoSize)
    {
        return useOne?pOne:pTwo;
    }
    else
    {
        cOne = pOne + dOne * mua;
        cTwo = pTwo + dTwo * mub;

        return cOne * 0.5 + cTwo * 0.5;
    }
}