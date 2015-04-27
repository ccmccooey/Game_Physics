#include "CollisionData.h"
#include "Contact.h"

CollisionData::CollisionData(unsigned int capacity)
{
	mContactArray = new Contact[capacity];
	for (unsigned int i = 0; i < capacity; i++)
	{
		mContactArray[i] = Contact();
	}
	mContactCount = 0;
	mContactsLeft = capacity;
	mContacts = mContactArray;

	mGlobalFriction = 0.0f;
	mGlobalRestitution = 0.5f;

	mTolerance = 0.1f;
}
CollisionData::~CollisionData()
{
	delete [] mContactArray;
}


void CollisionData::AddContacts(unsigned int count)
{
    // Reduce the number of contacts remaining, add number used
    mContactsLeft -= count;
    mContactCount += count;

    // Move the array forward
    mContacts += count;
}
void CollisionData::AddContact()
{
    // Reduce the number of contacts remaining, add number used
    mContactsLeft--;
    mContactCount++;

    // Move the array forward
    mContacts++;
}