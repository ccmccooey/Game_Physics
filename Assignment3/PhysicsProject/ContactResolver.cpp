#include "ContactResolver.h"
#include "Contact.h"


ContactResolver::ContactResolver()
{
	mPositionIterationsUsed = 0;
	mVelocityIterationsUsed = 0;
}
ContactResolver::~ContactResolver()
{

}

void ContactResolver::ResolveContacts (Contact *contacts, unsigned int numContacts, double duration)
{
    // Make sure we have something to do.
    if (numContacts == 0) return;

    //Prepare the contacts for processing
    PrepareContacts(contacts, numContacts, duration);

    //Resolve the interpenetration problems with the contacts.
    ResolvePositions(contacts, numContacts, duration);

    //Resolve the velocity problems with the contacts.
    ResolveVelocities(contacts, numContacts, duration);
}

void ContactResolver::PrepareContacts(Contact* contacts, unsigned numContacts, float duration)
{
    // Generate contact velocity and axis information.
    Contact* lastContact = contacts + numContacts;
    for (Contact* contact=contacts; contact < lastContact; contact++)
    {
        // Calculate the internal contact data (inertia, basis, etc).
        contact->CalculateInternals(duration);
    }
}

void ContactResolver::ResolvePositions(Contact *contact, unsigned int numContacts, float duration)
{
    unsigned int i, index;
	unsigned int b, d;
    Vector3f linearChange[2], angularChange[2];
    float max;
    Vector3f deltaPosition;

    // iteratively resolve interpenetrations in order of severity.
    mPositionIterationsUsed = 0;
    while (mPositionIterationsUsed < mPositionIterations)
    {
        // Find biggest penetration
		//max = positionEpsilon;
		max = Vector3f::EPSILON;
		
        index = numContacts;
        for (i = 0; i< numContacts; i++)
        {
			if (contact[i].mPenetrationDepth > max)
            {
				max = contact[i].mPenetrationDepth;
                index = i;
            }
        }
        if (index == numContacts) break;

        // Match the awake state at the contact
        //contact[index].matchAwakeState();

        // Resolve the penetration.
        contact[index].applyPositionChange(linearChange, angularChange, max);

        // Again this action may have changed the penetration of other
        // bodies, so we update contacts.
		

        for (i = 0; i < numContacts; i++)
        {
            // Check each body in the contact
			for (b = 0; b < 2; b++) if (contact[i].mBodies[b] != nullptr)
            {
                // Check for a match with each body in the newly
                // resolved contact
                for (d = 0; d < 2; d++)
                {
                    if (c[i].body[b] == c[index].body[d])
                    {
                        //deltaPosition = linearChange[d] + angularChange[d].vectorProduct(c[i].relativeContactPosition[b]);
						deltaPosition = linearChange[d] + Vector3f::CrossProduct(angularChange[d], contact[i].GetRelativeContactPosition(b));

                        // The sign of the change is positive if we're
                        // dealing with the second body in a contact
                        // and negative otherwise (because we're
                        // subtracting the resolution)..
                        c[i].penetration +=
                            deltaPosition.scalarProduct(c[i].contactNormal)
                            * (b?1:-1);
                    }
                }
            }
        }
        positionIterationsUsed++;
    }
}

void ContactResolver::ResolveVelocities(Contact *contact, unsigned numContacts, float duration)
{
    Vector3f velocityChange[2], rotationChange[2];
    Vector3f deltaVel;

    // iteratively handle impacts in order of severity.
    mVelocityIterationsUsed = 0;
    while (velocityIterationsUsed < velocityIterations)
    {
        // Find contact with maximum magnitude of probable velocity change.
        float max = velocityEpsilon;
        unsigned index = numContacts;
        for (unsigned i = 0; i < numContacts; i++)
        {
            if (c[i].desiredDeltaVelocity > max)
            {
                max = c[i].desiredDeltaVelocity;
                index = i;
            }
        }
        if (index == numContacts) break;

        // Match the awake state at the contact
        c[index].matchAwakeState();

        // Do the resolution on the contact that came out top.
        c[index].applyVelocityChange(velocityChange, rotationChange);

        // With the change in velocity of the two bodies, the update of
        // contact velocities means that some of the relative closing
        // velocities need recomputing.
        for (unsigned i = 0; i < numContacts; i++)
        {
            // Check each body in the contact
            for (unsigned b = 0; b < 2; b++) if (c[i].body[b])
            {
                // Check for a match with each body in the newly
                // resolved contact
                for (unsigned d = 0; d < 2; d++)
                {
                    if (c[i].body[b] == c[index].body[d])
                    {
                        deltaVel = velocityChange[d] +
                            rotationChange[d].vectorProduct(
                                c[i].relativeContactPosition[b]);

                        // The sign of the change is negative if we're dealing
                        // with the second body in a contact.
                        c[i].contactVelocity +=
                            c[i].contactToWorld.transformTranspose(deltaVel)
                            * (b?-1:1);
                        c[i].calculateDesiredDeltaVelocity(duration);
                    }
                }
            }
        }
        velocityIterationsUsed++;
    }
}
