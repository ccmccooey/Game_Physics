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

void Contact::CalculateContactBasis()
{
	Vector3f contactTangent[2];

	// Check whether the Z-axis is nearer to the X or Y axis
	if (fabs(mContactNormal.x) > fabs(mContactNormal.y))
	{
		// Scaling factor to ensure the results are normalized
		const float s = 1.0f / sqrtf(mContactNormal.z * mContactNormal.z + mContactNormal.x * mContactNormal.x);

		// The new X-axis is at right angles to the world Y-axis
		contactTangent[0].x = mContactNormal.z * s;
		contactTangent[0].y = 0;
		contactTangent[0].z = -mContactNormal.x * s;

		// The new Y-axis is at right angles to the new X- and Z- axes
		contactTangent[1].x = mContactNormal.y * contactTangent[0].x;
		contactTangent[1].y = mContactNormal.z * contactTangent[0].x - mContactNormal.x * contactTangent[0].z;
		contactTangent[1].z = -mContactNormal.y * contactTangent[0].x;
	}
	else
	{
		// Scaling factor to ensure the results are normalised
		const float s = 1.0 / sqrtf(mContactNormal.z * mContactNormal.z + mContactNormal.y * mContactNormal.y);

		// The new X-axis is at right angles to the world X-axis
		contactTangent[0].x = 0;
		contactTangent[0].y = -mContactNormal.z * s;
		contactTangent[0].z = mContactNormal.y * s;

		// The new Y-axis is at right angles to the new X- and Z- axes
		contactTangent[1].x = mContactNormal.y * contactTangent[0].z - mContactNormal.z * contactTangent[0].y;
		contactTangent[1].y = -mContactNormal.x * contactTangent[0].z;
		contactTangent[1].z = mContactNormal.x * contactTangent[0].y;
	}

	// Make a matrix from the three vectors.
	mContactToWorld.SetColumns(mContactNormal, contactTangent[0], contactTangent[1]);

	/*
	mContactToWorld.setComponents(
		mContactNormal,
		contactTangent[0],
		contactTangent[1]);*/
}
void Contact::CalculateInternals(double duration) 
{

    // Calculate an set of axis at the contact point.
    CalculateContactBasis();

    // Store the relative position of the contact relative to each mBody
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
    
	CalculateDesiredDeltaVelocity(duration);
}
void Contact::CalculateDesiredDeltaVelocity(float duration)
{
	const static float velocityLimit = (float)0.25f;

	// Calculate the acceleration induced velocity accumulated this frame
	float velocityFromAcc = 0;

	
	//velocityFromAcc += mBodies[0]->GetPreviousFrameAcceleration() * duration * mContactNormal;
	velocityFromAcc += Vector3f::DotProduct(mBodies[0]->GetPreviousFrameAcceleration(), mContactNormal) * duration;
	

	if (mBodies[1] != nullptr)
	{
		velocityFromAcc += Vector3f::DotProduct(mBodies[1]->GetPreviousFrameAcceleration(), mContactNormal) * duration;
		//velocityFromAcc -= mBodies[1]->GetPreviousFrameAcceleration() * duration * mContactNormal;				
	}
	

	// If the velocity is very slow, limit the restitution
	float thisRestitution = mRestitution;
	if (fabs(mContactVelocity.x) < velocityLimit)
	{
		thisRestitution = 0.0f;
	}

	// Combine the bounce velocity with the removed acceleration velocity.
	mDesiredDeltaVelocity = -mContactVelocity.x - thisRestitution * (mContactVelocity.x - velocityFromAcc);
}

Vector3f Contact::CalculateLocalVelocity(unsigned mBodyIndex, float duration)
{
    RigidBody *thisBody = mBodies[mBodyIndex];

    // Work out the velocity of the contact point.
    //Vector3f velocity = thisBody->GetRotation() % relativeContactPosition[mBodyIndex];
    //velocity += thisBody->GetVelocity();

	Vector3f velocity = Vector3f::CrossProduct(thisBody->GetRotation(), mRelativeContactPosition[mBodyIndex]) + thisBody->GetVelocity();

    // Returned velocity is in contact space - note transformTranspose.
    Vector3f mContactVelocity = mContactToWorld.TransformTranspose(velocity);

    // And return it
    return mContactVelocity;
}

