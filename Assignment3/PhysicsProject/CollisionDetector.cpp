#include "CollisionDetector.h"
#include "CollisionData.h"
#include "Vector3f.h"
#include "Contact.h"

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
	// We manually create the normal, because we have the
	// size to hand.
	Vector3f normal = midline * (1.0f / size);
	Contact* contact = data->contacts;
	contact->mContactNormal = normal;
	contact->mContactPoint = positionOne + midline * 0.5f;
	contact->mPenetrationDepth = (one.mRadius + two.mRadius - size);
	contact->SetBodyData(one.mBody, two.mBody, 1.0f, 1.0f);
	data->addContacts(1);

	return 1;
}