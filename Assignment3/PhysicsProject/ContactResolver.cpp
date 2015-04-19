#include "ContactResolver.h"
#include "Contact.h"

void ContactResolver::ResolveContacts (Contact *contacts, unsigned numContacts, double duration)
{
    // Make sure we have something to do.
    if (numContacts == 0) return;

    // Prepare the contacts for processing
    //prepareContacts(contacts, numContacts, duration);

    // Resolve the interpenetration problems with the contacts.
    //adjustPositions(contacts, numContacts, duration);

    // Resolve the velocity problems with the contacts.
    //adjustVelocities(contacts, numContacts, duration);
}
