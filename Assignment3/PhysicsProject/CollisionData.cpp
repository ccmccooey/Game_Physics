#include "CollisionData.h"
#include "Contact.h"

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