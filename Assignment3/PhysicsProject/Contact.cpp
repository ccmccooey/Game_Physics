#include "Contact.h"
#include "RigidBody.h"

Contact::Contact()
{
	mBodies[0] = nullptr;
	mBodies[1] = nullptr;

	mContactPoint = Vector3f();;
	mContactNormal = Vector3f::unitY;

	mPenetrationDepth = 0.0f;
	mRestitution = 0.0f;
	mFriction = 0.0f;
}
Contact::Contact(const Contact &rhs)
{
	mBodies[0] = rhs.mBodies[0];
	mBodies[1] = rhs.mBodies[1];

	mContactPoint = rhs.mContactPoint;
	mContactNormal = rhs.mContactNormal;

	mPenetrationDepth = rhs.mPenetrationDepth;
	mRestitution = rhs.mRestitution;
	mFriction = rhs.mFriction;
}
Contact::~Contact()
{

}

void Contact::CalculateInternals(double duration) 
{

    // Calculate an set of axis at the contact point.
    CalculateContactBasis();

    // Store the relative position of the contact relative to each body
    mRelativeContactPosition[0] = mContactPoint - mBodies[0]->GetPosition();
    if (mBodies[1] != nullptr)
	{
        mRelativeContactPosition[1] = mContactPoint - mBodies[1]->GetPosition();
    }

    // Find the relative velocity of the bodies at the contact point.
    mContactVelocity = CalculateLocalVelocity(0, duration);
    if (mBodies[1] != nullptr) 
	{
        mContactVelocity -= CalculateLocalVelocity(1, duration);
    }

    // Calculate the desired change in velocity for resolution.
    // Visited later in today’s lecture.
    
	calculateDesiredDeltaVelocity(duration);
}

Vector3f Contact::CalculateLocalVelocity(unsigned bodyIndex, float duration)
{
    RigidBody *thisBody = mBodies[bodyIndex];

    // Work out the velocity of the contact point.
    Vector3f velocity = thisBody->GetRotation() % relativeContactPosition[bodyIndex];
    velocity += thisBody->GetVelocity();

    // Returned velocity is in contact space - note transformTranspose.
    Vector3f mContactVelocity = mContactToWorld.transformTranspose(velocity);

    // And return it
    return mContactVelocity;
}

