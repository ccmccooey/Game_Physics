#include "ContactResolver.h"
#include "Contact.h"


ContactResolver::ContactResolver()
{
	mPositionIterationsUsed = 0;
	mVelocityIterationsUsed = 0;

	mPositionIterations = 1;
	mVelocityIterations = 1;

	mPositionEpsilon = FLT_EPSILON;
	mVelocityEpsilon = FLT_EPSILON;
}
ContactResolver::~ContactResolver()
{

}


void ContactResolver::SetIterations(unsigned int velocityIterations, unsigned int positionIterations)
{
	mPositionIterations = positionIterations;
	mVelocityIterations = velocityIterations;
}
void ContactResolver::SetIterations(unsigned int iterations) //applies to velocity and position
{
	mPositionIterations = mVelocityIterations = iterations;
}
void ContactResolver::SetEpsilon(float velocityEpsilon, float positionEpsilon)
{
	mVelocityEpsilon = velocityEpsilon;
	mPositionEpsilon = positionEpsilon;
}

void ContactResolver::ResolveContacts(Contact *contacts, unsigned int numContacts, double duration)
{
    // Make sure we have something to do.
    if (numContacts == 0) return;

    //Prepare the contacts for processing
    PrepareContacts(contacts, numContacts, (float)duration);

    //Resolve the interpenetration problems with the contacts.
    ResolvePositions(contacts, numContacts, (float)duration);

    //Resolve the velocity problems with the contacts.
    ResolveVelocities(contacts, numContacts, (float)duration);
}

void ContactResolver::PrepareContacts(Contact* contacts, unsigned int numContacts, float duration)
{
    // Generate contact velocity and axis information.
    Contact* lastContact = contacts + numContacts;
    for (Contact* contact = contacts; contact < lastContact; contact++)
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
        for (i = 0; i < numContacts; i++)
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
        contact[index].ApplyPositionChange(linearChange, angularChange, max);

        // Again this action may have changed the penetration of other
        // bodies, so we update contacts.
		

        for (i = 0; i < numContacts; i++)
        {
            // Check each rigid body in the contact
			for (b = 0; b < 2; b++) if (contact[i].mBodies[b] != nullptr)
            {
                // Check for a match with each rigid body in the newly
                // resolved contact
                for (d = 0; d < 2; d++)
                {
                    if (contact[i].mBodies[b] == contact[index].mBodies[d])
                    {
                        //deltaPosition = linearChange[d] + angularChange[d].vectorProduct(c[i].relativeContactPosition[b]);
						deltaPosition = linearChange[d] + Vector3f::CrossProduct(angularChange[d], contact[i].GetRelativeContactPosition(b));

                        // The sign of the change is positive if we're
                        // dealing with the second rigid body in a contact
                        // and negative otherwise (because we're
                        // subtracting the resolution)..
                        
						//contact[i].penetration += deltaPosition.scalarProduct(contact[i].contactNormal) * (b ? 1:-1);
						if (b)
							contact[i].mPenetrationDepth += Vector3f::DotProduct(deltaPosition, contact[i].mContactNormal);
						else
							contact[i].mPenetrationDepth += Vector3f::DotProduct(deltaPosition, contact[i].mContactNormal) * -1.0f;
                    }
                }
            }
        }
        mPositionIterationsUsed++;
    }
}

void ContactResolver::ResolveVelocities(Contact *contact, unsigned numContacts, float duration)
{
    Vector3f velocityChange[2], rotationChange[2];
    Vector3f deltaVelocity;

    // iteratively handle impacts in order of severity.
    mVelocityIterationsUsed = 0;
	float desiredVelocity;
    while (mVelocityIterationsUsed < mVelocityIterations)
    {
        // Find contact with maximum magnitude of probable velocity change.
        float max = mVelocityEpsilon;
        unsigned index = numContacts;
        for (unsigned int i = 0; i < numContacts; i++)
        {
			desiredVelocity = contact[i].GetDesiredDeltaVelocity();
			if (desiredVelocity > max)
            {
				max = desiredVelocity;
                index = i;
            }
        }
        if (index == numContacts) break;

        // Match the awake state at the contact
        //contact[index].matchAwakeState();

        // Do the resolution on the contact that came out top.
        contact[index].ApplyVelocityChange(velocityChange, rotationChange);

        // With the change in velocity of the two bodies, the update of
        // contact velocities means that some of the relative closing
        // velocities need recomputing.
        for (unsigned int i = 0; i < numContacts; i++)
        {
            // Check each rigid body in the contact
            for (unsigned int b = 0; b < 2; b++) if (contact[i].mBodies[b])
            {
                // Check for a match with each rigid body in the newly
                // resolved contact
                for (unsigned int d = 0; d < 2; d++)
                {
                    if (contact[i].mBodies[b] == contact[index].mBodies[d])
                    {
                        //deltaVel = velocityChange[d] + rotationChange[d].vectorProduct(contact[i].relativeContactPosition[b]);
						deltaVelocity = velocityChange[d] + Vector3f::CrossProduct(rotationChange[d], contact[i].GetRelativeContactPosition(b));

                        // The sign of the change is negative if we're dealing
                        // with the second rigid body in a contact.
                        //contact[i].contactVelocity += contact[i].contactToWorld.transformTranspose(deltaVel) * (b?-1:1);
                        
						if (b)
							contact[i].AddContactVelocity(contact[i].GetContactToWorld().TransformTranspose(deltaVelocity) * -1.0f);
						else
							contact[i].AddContactVelocity(contact[i].GetContactToWorld().TransformTranspose(deltaVelocity));
						
						contact[i].CalculateDesiredDeltaVelocity(duration);
                    }
                }
            }
        }
        mVelocityIterationsUsed++;
    }
}
