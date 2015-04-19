#include "CollisionDetector.h"
#include "Vector3f.h"
#include "Contact.h"

unsigned int CollisionDetector::sphereAndSphere(const ColliderSphere &one, const ColliderSphere &two, CollisionData *data)
{
	// Make sure we have contacts.
	if (data->contactsLeft <= 0)
	{
		return 0;
	}
	// Cache the sphere positions.
	Vector3f positionOne = one.getAxis(3);
	Vector3f positionTwo = two.getAxis(3);
	// Find the vector between the objects.
	Vector3f midline = positionOne - positionTwo;
	float size = midline.Length();
	// See if it is large enough.
	if (size <= 0.0f || size >= one.radius+two.radius)
	{
		return 0;
	}
	// We manually create the normal, because we have the
	// size to hand.
	Vector3f normal = midline * (1.0f / size);
	Contact* contact = data->contacts;
	contact->mContactNormal = normal;
	contact->mContactPoint = positionOne + midline * 0.5f;
	contact->mPenetrationDepth = (one.radius + two.radius - size);
	contact->setBodyData(one.body, two.body,
	data->friction, data->restitution);
	data->addContacts(1);
	return 1;
}