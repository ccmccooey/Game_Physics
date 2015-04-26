#include "CollisionDetector.h"
#include "CollisionData.h"
#include "Vector3f.h"
#include "Contact.h"

unsigned int CollisionDetector::PrimitiveAndPrimitive(CollisionPrimitive* a, CollisionPrimitive* b)
{
	return 0;
}
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
	contact->mContactNormal = normal;
	contact->mContactPoint = positionOne + midline * 0.5f;
	contact->mPenetrationDepth = (one.mRadius + two.mRadius - size);
	contact->SetBodyData(one.mBody, two.mBody, 1.0f, 1.0f);
	data->AddContacts(1);

	return 1;
}

unsigned int CollisionDetector::SphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane, CollisionData *data)
{
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
	contact->mContactNormal = plane.mNormal;
	contact->mPenetrationDepth = ballDistance * -1.0f;
	contact->mContactPoint = position - plane.mNormal * (ballDistance + sphere.mRadius);
	contact->SetBodyData(sphere.mBody, NULL, data->mGlobalFriction, data->mGlobalRestitution);

    data->AddContacts(1);
    return 1;
}

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