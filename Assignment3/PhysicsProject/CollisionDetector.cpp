#include "CollisionDetector.h"
#include "CollisionData.h"
#include "IntersectionTests.h"
#include "Vector3f.h"
#include "Contact.h"

unsigned long CollisionDetector::iterations = 0;

unsigned int CollisionDetector::PrimitiveAndPrimitive(CollisionPrimitive* a, CollisionPrimitive* b)
{
	return 0;
}


#pragma region Sphere and Sphere
unsigned int CollisionDetector::SphereAndSphere(const CollisionSphere &one, const CollisionSphere &two, CollisionData *data)
{
	// Make sure we have remaining contacts.
	if (data->mContactsLeft <= 0)
	{
		return 0;
	}

	
	// Cache the sphere positions.
	Vector3f positionOne = one.GetAxis(3); //its 3 because the third column is the translation
	Vector3f positionTwo = two.GetAxis(3);

	// Find the vector between the objects.
	Vector3f midline = positionOne - positionTwo;
	float size = midline.Length();

	// See if it is large enough.
	if (size <= 0.0f || size >= one.mRadius + two.mRadius)
	{
		return 0;
	}

	// We manually create the normal, because we have the size to hand.
	Vector3f normal = midline * (1.0f / size);
	Contact* contact = data->mContacts;
	contact[0] = Contact();
	contact->SetBodyData(one.mBody, two.mBody, 1.0f, 1.0f);
	contact->mContactNormal = normal;
	contact->mContactPoint = positionOne + midline * 0.5f;
	contact->mPenetrationDepth = (one.mRadius + two.mRadius - size);	
	data->AddContacts(1);

	return 1;
}
#pragma endregion

#pragma region Sphere and HalfSpace
unsigned int CollisionDetector::SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *data)
{
	iterations++;

    // Make sure we have contacts
    if (data->mContactsLeft <= 0)
	{
		return 0;
	}

    // Cache the sphere position
    Vector3f position = sphere.GetAxis(3);

    // Find the distance from the plane
	float ballDistance = Vector3f::DotProduct(plane.mNormal, position) - sphere.mRadius - plane.mOffset;

    if (ballDistance >= 0)
	{
		return 0;
	}

    // Create the contact - it has a normal in the plane direction.
    Contact* contact = data->mContacts;
	contact->SetBodyData(sphere.mBody, NULL, data->mGlobalFriction, data->mGlobalRestitution);
	contact->mContactNormal = plane.mNormal;
	contact->mPenetrationDepth = ballDistance * -1.0f;
	contact->mContactPoint = position - plane.mNormal * (ballDistance + sphere.mRadius);	

    data->AddContacts(1);
    return 1;
}
#pragma endregion

#pragma region Sphere and True Plane
unsigned int CollisionDetector::SphereAndTruePlane(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *data)
{
    // Make sure we have contacts
    if (data->mContactsLeft <= 0)
	{
		return 0;
	}

    // Cache the sphere position
    Vector3f position = sphere.GetAxis(3);

    // Find the distance from the plane
	float centerDistance = Vector3f::DotProduct(plane.mNormal, position) - plane.mOffset;

    // Check if we're within radius
    if (centerDistance * centerDistance > sphere.mRadius*sphere.mRadius)
    {
        return 0;
    }

    // Check which side of the plane we're on
    Vector3f normal = plane.mNormal;
    float penetrationDepth = -centerDistance;
    if (centerDistance < 0)
    {
        normal *= -1.0f;
        penetrationDepth = -penetrationDepth;
    }
    penetrationDepth += sphere.mRadius;

    // Create the contact - it has a normal in the plane direction.
    Contact* contact = data->mContacts;
    contact->mContactNormal = normal;
	contact->mPenetrationDepth = penetrationDepth;
	contact->mContactPoint = position - plane.mNormal * centerDistance;
	contact->SetBodyData(sphere.mBody, NULL, data->mGlobalFriction, data->mGlobalRestitution);

    data->AddContacts(1);
    return 1;
}
#pragma endregion

#pragma region Box and Point
unsigned int CollisionDetector::BoxAndPoint(const CollisionBox &box, const Vector3f &point, CollisionData *data)
{
    // Transform the point into box coordinates
	Vector3f relPt = box.GetTransformMatrix().TransformInverse(point);

    Vector3f normal;

    // Check each axis, looking for the axis on which the
    // penetration is least deep.
    float minimumDepth = box.mHalfSize.x - fabs(relPt.x);
    if (minimumDepth < 0)
	{
		return 0;
	}
    normal = box.GetAxis(0) * ((relPt.x < 0)?-1:1);

    float depth = box.mHalfSize.y - fabs(relPt.y);
    if (depth < 0)
	{
		return 0;
	}
    else if (depth < minimumDepth)
    {
        minimumDepth = depth;
        normal = box.GetAxis(1) * ((relPt.y < 0)?-1:1);
    }

    depth = box.mHalfSize.z - fabs(relPt.z);
    if (depth < 0)
	{
		return 0;
	}
    else if (depth < minimumDepth)
    {
        minimumDepth = depth;
        normal = box.GetAxis(2) * ((relPt.z < 0)?-1:1);
    }

    // Compile the contact
    Contact* contact = data->mContacts;
    contact->mContactNormal = normal;
    contact->mContactPoint = point;
    contact->mPenetrationDepth = minimumDepth;

    // Note that we don't know what rigid body the point
    // belongs to, so we just use NULL. Where this is called
    // this value can be left, or filled in.
	contact->SetBodyData(box.mBody, NULL, data->mGlobalFriction, data->mGlobalRestitution);

	data->AddContacts(1);
    return 1;
}
#pragma endregion

#pragma region Box and Sphere
unsigned int CollisionDetector::BoxAndSphere(const CollisionBox &box, const CollisionSphere &sphere, CollisionData *data)
{
    // Transform the centre of the sphere into box coordinates
    Vector3f centre = sphere.GetAxis(3);
	Vector3f relCentre = box.GetTransformMatrix().TransformInverse(centre);

    // Early out check to see if we can exclude the contact
    if (fabs(relCentre.x) - sphere.mRadius > box.mHalfSize.x ||
        fabs(relCentre.y) - sphere.mRadius > box.mHalfSize.y ||
        fabs(relCentre.z) - sphere.mRadius > box.mHalfSize.z)
    {
        return 0;
    }

	Vector3f closestPt = Vector3f::zero;
    float distance;

    // Clamp each coordinate to the box.
    distance = relCentre.x;
    if (distance > box.mHalfSize.x) distance = box.mHalfSize.x;
    if (distance < -box.mHalfSize.x) distance = -box.mHalfSize.x;
    closestPt.x = distance;

    distance = relCentre.y;
    if (distance > box.mHalfSize.y) distance = box.mHalfSize.y;
    if (distance < -box.mHalfSize.y) distance = -box.mHalfSize.y;
    closestPt.y = distance;

    distance = relCentre.z;
    if (distance > box.mHalfSize.z) distance = box.mHalfSize.z;
    if (distance < -box.mHalfSize.z) distance = -box.mHalfSize.z;
    closestPt.z = distance;

    // Check we're in contact
	distance = (closestPt - relCentre).LengthSquared();
    if (distance > sphere.mRadius * sphere.mRadius)
	{
		return 0;
	}

    // Compile the contact
	Vector3f closestPtWorld = box.GetTransformMatrix().Transform(closestPt);

    Contact* contact = data->mContacts;
    contact->mContactNormal = (closestPtWorld - centre);
	contact->mContactNormal.Normalize();
    contact->mContactPoint = closestPtWorld;
	contact->mPenetrationDepth = sphere.mRadius - sqrtf(distance);
	contact->SetBodyData(box.mBody, sphere.mBody, data->mGlobalFriction, data->mGlobalRestitution);

    data->AddContacts(1);
    return 1;
}
#pragma endregion

#pragma region Box and Half Space
unsigned int CollisionDetector::BoxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane, CollisionData *data)
{
    // Make sure we have contacts
    if (data->mContactsLeft <= 0) return 0;

    // Check for intersection
    if (!IntersectionTests::BoxAndHalfSpace(box, plane))
    {
        return 0;
    }

    // We have an intersection, so find the intersection points. We can make
    // do with only checking vertices. If the box is resting on a plane
    // or on an edge, it will be reported as four or two contact points.

    // Go through each combination of + and - for each half-size
    static float mults[8][3] = {{1,1,1},{-1,1,1},{1,-1,1},{-1,-1,1},
                               {1,1,-1},{-1,1,-1},{1,-1,-1},{-1,-1,-1}};

    Contact* contact = data->mContacts;
    unsigned contactsUsed = 0;
    for (unsigned i = 0; i < 8; i++) {

        // Calculate the position of each vertex
        Vector3f vertexPos(mults[i][0], mults[i][1], mults[i][2]);
        //vertexPos.componentProductUpdate(box.mHalfSize);
		vertexPos *= box.mHalfSize; //component product
        vertexPos = box.GetTransformMatrix().Transform(vertexPos);

        // Calculate the distance from the plane
		//float vertexDistance = vertexPos * plane.mNormal;
		float vertexDistance = Vector3f::DotProduct(vertexPos, plane.mNormal);

        // Compare this to the plane's distance
        if (vertexDistance <= plane.mOffset)
        {
            // Create the contact data.

            // The contact point is halfway between the vertex and the
            // plane - we multiply the direction by half the separation
            // distance and add the vertex location.
            contact->mContactPoint = plane.mNormal;
            contact->mContactPoint *= (vertexDistance-plane.mOffset);
            contact->mContactPoint += vertexPos;
			contact->mContactNormal = plane.mNormal;
            contact->mPenetrationDepth = plane.mOffset - vertexDistance;

            // Write the appropriate data
			contact->SetBodyData(box.mBody, NULL, data->mGlobalFriction, data->mGlobalRestitution);

            // Move onto the next contact
            contact++;
            contactsUsed++;
            if (contactsUsed == (unsigned)data->mContactsLeft) return contactsUsed;
        }
    }

    data->AddContacts(contactsUsed);
    return contactsUsed;
}
#pragma endregion

#pragma region Box and Box
#define CHECK_OVERLAP(axis, index) \ if (!tryAxis(one, two, (axis), toCentre, (index), pen, best)) return 0;
unsigned int CollisionDetector::BoxAndBox(const CollisionBox &one, const CollisionBox &two, CollisionData *data)
{
    //if (!IntersectionTests::boxAndBox(one, two)) return 0;

    // Find the vector between the two centres
    Vector3f toCentre = two.GetAxis(3) - one.GetAxis(3);

    // We start assuming there is no contact
    float pen = FLT_MAX;
    unsigned int best = ~0;//0xffffff;

    // Now we check each axes, returning if it gives us
    // a separating axis, and keeping track of the axis with
    // the smallest penetration otherwise.
    CHECK_OVERLAP(one.GetAxis(0), 0);
    CHECK_OVERLAP(one.GetAxis(1), 1);
    CHECK_OVERLAP(one.GetAxis(2), 2);

    CHECK_OVERLAP(two.GetAxis(0), 3);
    CHECK_OVERLAP(two.GetAxis(1), 4);
    CHECK_OVERLAP(two.GetAxis(2), 5);

    // Store the best axis-major, in case we run into almost
    // parallel edge collisions later
    unsigned bestSingleAxis = best;

    CHECK_OVERLAP(one.GetAxis(0) % two.GetAxis(0), 6);
    CHECK_OVERLAP(one.GetAxis(0) % two.GetAxis(1), 7);
    CHECK_OVERLAP(one.GetAxis(0) % two.GetAxis(2), 8);
    CHECK_OVERLAP(one.GetAxis(1) % two.GetAxis(0), 9);
    CHECK_OVERLAP(one.GetAxis(1) % two.GetAxis(1), 10);
    CHECK_OVERLAP(one.GetAxis(1) % two.GetAxis(2), 11);
    CHECK_OVERLAP(one.GetAxis(2) % two.GetAxis(0), 12);
    CHECK_OVERLAP(one.GetAxis(2) % two.GetAxis(1), 13);
    CHECK_OVERLAP(one.GetAxis(2) % two.GetAxis(2), 14);

    // Make sure we've got a result.
    //assert(best != 0xffffff);

    // We now know there's a collision, and we know which
    // of the axes gave the smallest penetration. We now
    // can deal with it in different ways depending on
    // the case.
    if (best < 3)
    {
        // We've got a vertex of box two on a face of box one.
        fillPointFaceBoxBox(one, two, toCentre, data, best, pen);
        data->AddContacts(1);
        return 1;
    }
    else if (best < 6)
    {
        // We've got a vertex of box one on a face of box two.
        // We use the same algorithm as above, but swap around
        // one and two (and therefore also the vector between their
        // centres).
        fillPointFaceBoxBox(two, one, toCentre*-1.0f, data, best-3, pen);
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
        Vector3f axis = oneAxis % twoAxis;
        axis.Normalize();

        // The axis should point from box one to box two.
        if (axis * toCentre > 0.0f) axis = axis * -1.0f;

        // We have the axes, but not the edges: each axis has 4 edges parallel
        // to it, we need to find which of the 4 for each object. We do
        // that by finding the point in the centre of the edge. We know
        // its component in the direction of the box's collision axis is zero
        // (its a mid-point) and we determine which of the extremes in each
        // of the other axes is closest.
        Vector3f ptOnOneEdge = one.halfSize;
        Vector3f ptOnTwoEdge = two.halfSize;
        for (unsigned i = 0; i < 3; i++)
        {
            if (i == oneAxisIndex) ptOnOneEdge[i] = 0;
            else if (one.GetAxis(i) * axis > 0) ptOnOneEdge[i] = -ptOnOneEdge[i];

            if (i == twoAxisIndex) ptOnTwoEdge[i] = 0;
            else if (two.GetAxis(i) * axis < 0) ptOnTwoEdge[i] = -ptOnTwoEdge[i];
        }

        // Move them into world coordinates (they are already oriented
        // correctly, since they have been derived from the axes).
        ptOnOneEdge = one.transform * ptOnOneEdge;
        ptOnTwoEdge = two.transform * ptOnTwoEdge;

        // So we have a point and a direction for the colliding edges.
        // We need to find out point of closest approach of the two
        // line-segments.
        Vector3f vertex = contactPoint(
            ptOnOneEdge, oneAxis, one.halfSize[oneAxisIndex],
            ptOnTwoEdge, twoAxis, two.halfSize[twoAxisIndex],
            bestSingleAxis > 2
            );

        // We can fill the contact.
        Contact* contact = data->mContacts;

        contact->mPenetrationDepth = pen;
        contact->mContactNormal = axis;
        contact->mContactPoint = vertex;
		contact->SetBodyData(one.mBody, two.mBody,
            data->mGlobalFriction, data->mRestitution);
        data->AddContacts(1);
        return 1;
    }
    return 0;
}
#undef CHECK_OVERLAP
#pragma endregion