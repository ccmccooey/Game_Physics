#include "BoxCollisionHelperFunctions.h"
#include "CollisionDetector.h"
#include "CollisionData.h"
#include "Contact.h"
#include "CollisionGeometries.h"

unsigned int CollisionDetector::BoxAndBox(const CollisionBox &one, const CollisionBox &two, CollisionData *data)
{
    //if (!IntersectionTests::boxAndBox(one, two)) return 0;

    // Find the vector between the two centres
    Vector3f toCentre = two.GetAxis(3) - one.GetAxis(3);

    // We start assuming there is no contact
    float pen = FLT_MAX;
    unsigned int best = 0xffffff;

    // Now we check each axes, returning if it gives us a separating axis, and keeping track of the axis with the smallest penetration otherwise.
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, one.GetAxis(0), toCentre, 0, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, one.GetAxis(1), toCentre, 1, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, one.GetAxis(2), toCentre, 2, pen, best)){ return 0; }

	if (!BoxCollisionHelperFunctions::TryAxis(one, two, one.GetAxis(0), toCentre, 3, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, one.GetAxis(1), toCentre, 4, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, one.GetAxis(2), toCentre, 5, pen, best)){ return 0; }

	// Store the best axis-major, in case we run into almost parallel edge collisions later
    unsigned int bestSingleAxis = best;

	if (!BoxCollisionHelperFunctions::TryAxis(one, two, Vector3f::CrossProduct(one.GetAxis(0), two.GetAxis(0)), toCentre, 6, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, Vector3f::CrossProduct(one.GetAxis(0), two.GetAxis(1)), toCentre, 7, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, Vector3f::CrossProduct(one.GetAxis(0), two.GetAxis(2)), toCentre, 8, pen, best)){ return 0; }

	if (!BoxCollisionHelperFunctions::TryAxis(one, two, Vector3f::CrossProduct(one.GetAxis(1), two.GetAxis(0)), toCentre, 9, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, Vector3f::CrossProduct(one.GetAxis(1), two.GetAxis(1)), toCentre, 10, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, Vector3f::CrossProduct(one.GetAxis(1), two.GetAxis(2)), toCentre, 11, pen, best)){ return 0; }

	if (!BoxCollisionHelperFunctions::TryAxis(one, two, Vector3f::CrossProduct(one.GetAxis(2), two.GetAxis(0)), toCentre, 12, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, Vector3f::CrossProduct(one.GetAxis(2), two.GetAxis(1)), toCentre, 13, pen, best)){ return 0; }
	if (!BoxCollisionHelperFunctions::TryAxis(one, two, Vector3f::CrossProduct(one.GetAxis(2), two.GetAxis(2)), toCentre, 14, pen, best)){ return 0; }


    // Make sure we've got a result.
    //assert(best != 0xffffff);

    // We now know there's a collision, and we know which of the axes gave the smallest penetration. We now can deal with it in different ways depending on the case.
    if (best < 3)
    {
        // We've got a vertex of box two on a face of box one.
        BoxCollisionHelperFunctions::FillPointFaceBoxBox(one, two, toCentre, data, best, pen);
        data->AddContacts(1);
        return 1;
    }
    else if (best < 6)
    {
        // We've got a vertex of box one on a face of box two.
        // We use the same algorithm as above, but swap around
        // one and two (and therefore also the vector between their
        // centres).
        BoxCollisionHelperFunctions::FillPointFaceBoxBox(two, one, toCentre * -1.0f, data, best - 3, pen);
        data->AddContacts(1);
        return 1;
    }
    else
    {
        // We've got an edge-edge contact. Find out which axes
        best -= 6;
        unsigned oneAxisIndex = best / 3;
        unsigned twoAxisIndex = best % 3;
        Vector3f oneAxis = one.GetAxis(oneAxisIndex);
        Vector3f twoAxis = two.GetAxis(twoAxisIndex);
		Vector3f axis = Vector3f::CrossProduct(oneAxis, twoAxis);
        axis.Normalize();

        // The axis should point from box one to box two.
		if (Vector3f::DotProduct(axis, toCentre) > 0.0f)
		{
			axis = axis * -1.0f;
		}
        // We have the axes, but not the edges: each axis has 4 edges parallel to it, we need to find which of the 4 for each object. We do
        // that by finding the point in the centre of the edge. We know its component in the direction of the box's collision axis is zero
        // (its a mid-point) and we determine which of the extremes in each of the other axes is closest.
		Vector3f ptOnOneEdge = one.mHalfSize;
        Vector3f ptOnTwoEdge = two.mHalfSize;
        for (unsigned int i = 0; i < 3; i++)
        {
            if (i == oneAxisIndex)
			{
				ptOnOneEdge[i] = 0.0f;
			}
            else if (Vector3f::DotProduct(one.GetAxis(i), axis) > 0.0f)
			{
				ptOnOneEdge[i] = -ptOnOneEdge[i];
			}

            if (i == twoAxisIndex)
			{
				ptOnTwoEdge[i] = 0.0f;
			}
            else if (Vector3f::DotProduct(two.GetAxis(i), axis) < 0.0f)
			{
				ptOnTwoEdge[i] = -ptOnTwoEdge[i];
			}
        }

        // Move them into world coordinates (they are already oriented
        // correctly, since they have been derived from the axes).
		ptOnOneEdge = one.GetTransformMatrix() * ptOnOneEdge;
        ptOnTwoEdge = two.GetTransformMatrix() * ptOnTwoEdge;

        // So we have a point and a direction for the colliding edges.
        // We need to find out point of closest approach of the two
        // line-segments.
		Vector3f vertex = BoxCollisionHelperFunctions::ContactPoint(
            ptOnOneEdge, oneAxis, one.mHalfSize[oneAxisIndex],
            ptOnTwoEdge, twoAxis, two.mHalfSize[twoAxisIndex],
            bestSingleAxis > 2
            );

        // We can fill the contact.
        Contact* contact = data->mContacts;

        contact->mPenetrationDepth = pen;
        contact->mContactNormal = axis;
        contact->mContactPoint = vertex;
		contact->SetBodyData(one.mBody, two.mBody, data->mGlobalFriction, data->mGlobalRestitution);
        data->AddContacts(1);
        return 1;
    }
    return 0;
}
