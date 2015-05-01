#include "Contact.h"
#include "RigidBody.h"

//constructors
Contact::Contact()
{
	mBodies[0] = nullptr;
	mBodies[1] = nullptr;

	mContactPoint = Vector3f();;
	mContactNormal = Vector3f::unitY;

	mPenetrationDepth = 0.0f;
	mRestitution = 0.0f;
	mFriction = 0.0f;
	mNull = true;
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
	mNull = rhs.mNull;
}
Contact::~Contact()
{

}

//accessors
const Vector3f& Contact::GetRelativeContactPosition(unsigned int index) const
{
	return mRelativeContactPosition[index];
}
const Matrix33f& Contact::GetContactToWorld() const
{
	return mContactToWorld;
}
float Contact::GetDesiredDeltaVelocity() const
{
	return mDesiredDeltaVelocity;
}
const Vector3f& Contact::GetContactVelocity() const
{
	return mContactVelocity;
}

//basic settors
void Contact::AddContactVelocity(const Vector3f &contactVelocity)
{
	mContactVelocity += contactVelocity;
}

//calculation functions
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
		contactTangent[0].y = 0.0f;
		contactTangent[0].z = -mContactNormal.x * s;

		// The new Y-axis is at right angles to the new X- and Z- axes
		contactTangent[1].x = mContactNormal.y * contactTangent[0].x;
		contactTangent[1].y = mContactNormal.z * contactTangent[0].x - mContactNormal.x * contactTangent[0].z;
		contactTangent[1].z = -(mContactNormal.y) * contactTangent[0].x;
	}
	else
	{
		// Scaling factor to ensure the results are normalised
		const float s = 1.0f / sqrtf(mContactNormal.z * mContactNormal.z + mContactNormal.y * mContactNormal.y);

		// The new X-axis is at right angles to the world X-axis
		contactTangent[0].x = 0.0f;
		contactTangent[0].y = -(mContactNormal.z) * s;
		contactTangent[0].z = mContactNormal.y * s;

		// The new Y-axis is at right angles to the new X- and Z- axes
		contactTangent[1].x = mContactNormal.y * contactTangent[0].z - mContactNormal.z * contactTangent[0].y;
		contactTangent[1].y = -(mContactNormal.x) * contactTangent[0].z;
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
	if (mBodies[0] == nullptr)
	{
		RigidBody* tmp = mBodies[0];
		mBodies[0] = mBodies[1];
		mBodies[1] = tmp;
	}

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
void Contact::CalculateDesiredDeltaVelocity(double duration)
{
	const static float velocityLimit = 0.25f;

	// Calculate the acceleration induced velocity accumulated this frame
	float velocityFromAcc = 0;

	
	//velocityFromAcc += mBodies[0]->GetPreviousFrameAcceleration() * duration * mContactNormal;
	velocityFromAcc += Vector3f::DotProduct(mBodies[0]->GetPreviousFrameAcceleration() * (float)duration, mContactNormal);

	if (mBodies[1] != nullptr)
	{	
		velocityFromAcc -= Vector3f::DotProduct(mBodies[1]->GetPreviousFrameAcceleration() * (float)duration, mContactNormal);						
	}

	// If the velocity is very slow, limit the restitution
	float thisRestitution = mRestitution;
	if (fabs(mContactVelocity.x) < velocityLimit)
	{
		thisRestitution = 0.0f;
	}

	// Combine the bounce velocity with the removed acceleration velocity.
	mDesiredDeltaVelocity = -mContactVelocity.x -thisRestitution * (mContactVelocity.x - velocityFromAcc);
}

Vector3f Contact::CalculateLocalVelocity(unsigned int mBodyIndex, double duration)
{
    RigidBody* thisBody = mBodies[mBodyIndex];

    // Work out the velocity of the contact point.
	Vector3f velocity = Vector3f::CrossProduct(thisBody->GetRotation(), mRelativeContactPosition[mBodyIndex]);
	velocity += thisBody->GetVelocity();

    // Returned velocity is in contact space - note transformTranspose.
    Vector3f mContactVelocity = mContactToWorld.TransformTranspose(velocity);

	// Calculate the ammount of velocity that is due to forces without reactions.
	Vector3f accVelocity = thisBody->GetPreviousFrameAcceleration() * (float)duration;

    // Calculate the velocity in contact-coordinates.
    accVelocity = mContactToWorld.TransformTranspose(accVelocity);

    // We ignore any component of acceleration in the contact normal direction, we are only interested in planar acceleration
    accVelocity.x = 0;

    // Add the planar velocities - if there's enough friction they will be removed during velocity resolution
    mContactVelocity += accVelocity;

    // And return it
    return mContactVelocity;
}


//impulse and friction calculations
inline Vector3f Contact::CalculateFrictionlessImpulse(Matrix33f* inverseInertiaTensor)
{
    Vector3f impulseContact;

    // Build a vector that shows the change in velocity in world space for a unit impulse in the direction of the contact normal.
	Vector3f deltaVelocityWorld = Vector3f::CrossProduct(mRelativeContactPosition[0], mContactNormal);
    deltaVelocityWorld = inverseInertiaTensor[0].Transform(deltaVelocityWorld);
	deltaVelocityWorld = Vector3f::CrossProduct(deltaVelocityWorld, mRelativeContactPosition[0]);

    // Work out the change in velocity in contact coordiantes.
	float deltaVelocity = Vector3f::DotProduct(deltaVelocityWorld, mContactNormal);

    // Add the linear component of velocity change
	deltaVelocity += mBodies[0]->GetInverseMass();

    // Check if we need to the second body's data
    if (mBodies[1])
    {
        // Go through the same transformation sequence again
        Vector3f deltaVelocityWorld = Vector3f::CrossProduct(mRelativeContactPosition[1], mContactNormal);
        deltaVelocityWorld = inverseInertiaTensor[1].Transform(deltaVelocityWorld);
        deltaVelocityWorld = Vector3f::CrossProduct(deltaVelocityWorld, mRelativeContactPosition[1]);

        // Add the change in velocity due to rotation
        deltaVelocity += Vector3f::DotProduct(deltaVelocityWorld, mContactNormal);

        // Add the change in velocity due to linear motion
        deltaVelocity += mBodies[1]->GetInverseMass();
    }

    // Calculate the required size of the impulse
    impulseContact.x = mDesiredDeltaVelocity / deltaVelocity;
    impulseContact.y = 0;
    impulseContact.z = 0;
    return impulseContact;
}

inline Vector3f Contact::CalculateFrictionImpulse(Matrix33f* inverseInertiaTensor)
{
    Vector3f impulseContact;
    float inverseMass = mBodies[0]->GetInverseMass();

    // The equivalent of a cross product in matrices is multiplication
    // by a skew symmetric matrix - we build the matrix for converting
    // between linear and angular quantities.
    Matrix33f impulseToTorque;
    impulseToTorque.SetSkewSymmetric(mRelativeContactPosition[0]);

    // Build the matrix to convert contact impulse to change in velocity
    // in world coordinates.
    Matrix33f deltaVelocityWorld = impulseToTorque;
    deltaVelocityWorld *= inverseInertiaTensor[0];
    deltaVelocityWorld *= impulseToTorque;
    deltaVelocityWorld *= -1;

    // Check if we need to add body two's data
    if (mBodies[1])
    {
        // Set the cross product matrix
        impulseToTorque.SetSkewSymmetric(mRelativeContactPosition[1]);

        // Calculate the velocity change matrix
        Matrix33f deltaVelocityWorld2 = impulseToTorque;
        deltaVelocityWorld2 *= inverseInertiaTensor[1];
        deltaVelocityWorld2 *= impulseToTorque;
        deltaVelocityWorld2 *= -1;

        // Add to the total delta velocity.
        deltaVelocityWorld += deltaVelocityWorld2;

        // Add to the inverse mass
        inverseMass += mBodies[1]->GetInverseMass();
    }

    // Do a change of basis to convert into contact coordinates.
    Matrix33f deltaVelocity = mContactToWorld.Transpose();
    deltaVelocity *= deltaVelocityWorld;
    deltaVelocity *= mContactToWorld;

    // Add in the linear velocity change
    deltaVelocity[0] += inverseMass;
    deltaVelocity[4] += inverseMass;
    deltaVelocity[8] += inverseMass;

    // Invert to get the impulse needed per unit velocity
    Matrix33f impulseMatrix = deltaVelocity.Inverse();

    // Find the target velocities to kill
    Vector3f velKill(mDesiredDeltaVelocity, -mContactVelocity.y, -mContactVelocity.z);

    // Find the impulse to kill target velocities
    impulseContact = impulseMatrix.Transform(velKill);

    // Check for exceeding friction
    float planarImpulse = sqrtf((impulseContact.y * impulseContact.y) + (impulseContact.z * impulseContact.z));
    if (planarImpulse > impulseContact.x * mFriction)
    {
        // We need to use dynamic friction
        impulseContact.y /= planarImpulse;
        impulseContact.z /= planarImpulse;

        impulseContact.x = deltaVelocity[0] + deltaVelocity[1] * mFriction * impulseContact.y + deltaVelocity[2] * mFriction * impulseContact.z;
        impulseContact.x = mDesiredDeltaVelocity / impulseContact.x;
        impulseContact.y *= mFriction * impulseContact.x;
        impulseContact.z *= mFriction * impulseContact.x;
    }
    return impulseContact;
}

void Contact::SetBodyData(RigidBody* actorA, RigidBody* actorB, float friction, float restitution)
{	
	mBodies[0] = actorA;	
	mBodies[1] = actorB;
	mFriction = friction;
	mRestitution = restitution;
	mNull = mBodies[0] != nullptr;
}

//aplly a change in position
void Contact::ApplyPositionChange(Vector3f linearChange[2], Vector3f angularChange[2], float penetration)
{
    const float angularLimit = (float)0.2f;
    float angularMove[2];
    float linearMove[2];

    float totalInertia = 0;
    float linearInertia[2];
    float angularInertia[2];

    // We need to work out the inertia of each object in the direction
    // of the contact normal, due to angular inertia only.
    for (unsigned int i = 0; i < 2; i++) if (mBodies[i])
    {
        Matrix33f inverseInertiaTensor;
        mBodies[i]->GetInverseInertiaTensorWorld(&inverseInertiaTensor);

        // Use the same procedure as for calculating frictionless
        // velocity change to work out the angular inertia.
		Vector3f angularInertiaWorld = Vector3f::CrossProduct(mRelativeContactPosition[i], mContactNormal);
        angularInertiaWorld = inverseInertiaTensor.Transform(angularInertiaWorld);
		angularInertiaWorld = Vector3f::CrossProduct(angularInertiaWorld, mRelativeContactPosition[i]);
		angularInertia[i] = Vector3f::DotProduct(angularInertiaWorld, mContactNormal);

        // The linear component is simply the inverse mass
        linearInertia[i] = mBodies[i]->GetInverseMass();

        // Keep track of the total inertia from all components
        totalInertia += linearInertia[i] + angularInertia[i];

        // We break the loop here so that the totalInertia value is
        // completely calculated (by both iterations) before
        // continuing.
    }

    // Loop through again calculating and applying the changes
    for (unsigned int i = 0; i < 2; i++) if (mBodies[i])
    {
        // The linear and angular movements required are in proportion to
        // the two inverse inertias.
        float sign = (i == 0)?1.0f:-1.0f;

        angularMove[i] = sign * penetration * (angularInertia[i] / totalInertia);
        linearMove[i] = sign * penetration * (linearInertia[i] / totalInertia);

        // To avoid angular projections that are too great (when mass is large
        // but inertia tensor is small) limit the angular move.
        Vector3f projection = mRelativeContactPosition[i];
        //projection.AddScaledVector(contactNormal, -relativeContactPosition[i].scalarProduct(contactNormal));
		projection += (mContactNormal * -Vector3f::DotProduct(mRelativeContactPosition[i], mContactNormal));

        // Use the small angle approximation for the sine of the angle (i.e.
        // the magnitude would be sine(angularLimit) * projection.magnitude
        // but we approximate sine(angularLimit) to angularLimit).
        float maxMagnitude = angularLimit * projection.Length();

        if (angularMove[i] < -maxMagnitude)
        {
            float totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = -maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }
        else if (angularMove[i] > maxMagnitude)
        {
            float totalMove = angularMove[i] + linearMove[i];
            angularMove[i] = maxMagnitude;
            linearMove[i] = totalMove - angularMove[i];
        }

        // We have the linear amount of movement required by turning
        // the rigid body (in angularMove[i]). We now need to
        // calculate the desired rotation to achieve that.
        if (angularMove[i] == 0)
        {
            // Easy case - no angular movement means no rotation.
            //angularChange[i].clear();
			angularChange[i] = Vector3f::zero;
        }
        else
        {
            // Work out the direction we'd like to rotate in.
            //Vector3f targetAngularDirection = mRelativeContactPosition[i].vectorProduct(contactNormal);
			Vector3f targetAngularDirection = Vector3f::CrossProduct(mRelativeContactPosition[i], mContactNormal);

            Matrix33f inverseInertiaTensor;
            mBodies[i]->GetInverseInertiaTensorWorld(&inverseInertiaTensor);

            // Work out the direction we'd need to rotate to achieve that
            angularChange[i] = inverseInertiaTensor.Transform(targetAngularDirection) * (angularMove[i] / angularInertia[i]);
        }

        // Velocity change is easier - it is just the linear movement
        // along the contact normal.
        linearChange[i] = mContactNormal * linearMove[i];

        // Now we can start to apply the values we've calculated.
        // Apply the linear movement

		//Vector3f pos = mBodies[i]->GetPosition();
        //mBodies[i]->GetPosition(&pos);
        //pos.addScaledVector(contactNormal, linearMove[i]);
        //mBodies[i]->setPosition(pos);
		mBodies[i]->Translate(mContactNormal * linearMove[i]); //Translate is a forced movement

        // And the change in orientation
		Quaternion orientation = mBodies[i]->GetOrientation();
        //mBodies[i]->getOrientation(&q);
        orientation.addScaledVector(angularChange[i], 1.0f);
        mBodies[i]->SetOrientation(orientation);

        // We need to calculate the derived data for any body that is
        // asleep, so that the changes are reflected in the object's
        // data. Otherwise the resolution will not change the position
        // of the object, and the next collision detection round will
        // have the same penetration.
		mBodies[i]->CalculateDerivedData();
    }
}

//apply a change in velocity
void Contact::ApplyVelocityChange(Vector3f velocityChange[2], Vector3f rotationChange[2])
{
    // Get hold of the inverse mass and inverse inertia tensor, both in
    // world coordinates.
    Matrix33f inverseInertiaTensor[2];
    mBodies[0]->GetInverseInertiaTensorWorld(&inverseInertiaTensor[0]);
    if (mBodies[1] != nullptr)
        mBodies[1]->GetInverseInertiaTensorWorld(&inverseInertiaTensor[1]);

    // We will calculate the impulse for each contact axis
    Vector3f impulseContact;

    if (mFriction == 0.0f)
    {
        // Use the short format for mFrictionless contacts
        impulseContact = CalculateFrictionlessImpulse(inverseInertiaTensor);
    }
    else
    {
        // Otherwise we may have impulses that aren't in the direction of the contact, so we need the more complex version.
        impulseContact = CalculateFrictionImpulse(inverseInertiaTensor);
		//impulseContact = CalculateFrictionlessImpulse(inverseInertiaTensor);
    }

    // Convert impulse to world coordinates
    Vector3f impulse = mContactToWorld.Transform(impulseContact);

    // Split in the impulse into linear and rotational components
    Vector3f impulsiveTorque = Vector3f::CrossProduct(mRelativeContactPosition[0], impulse);
    rotationChange[0] = inverseInertiaTensor[0].Transform(impulsiveTorque);
	velocityChange[0] = impulse * mBodies[0]->GetInverseMass();

    // Apply the changes
    mBodies[0]->AddVelocity(velocityChange[0]);
    mBodies[0]->AddRotation(rotationChange[0]);

    if (mBodies[1] != nullptr)
    {
        // Work out mBodies one's linear and angular changes
        Vector3f impulsiveTorque = Vector3f::CrossProduct(impulse, mRelativeContactPosition[1]);
        rotationChange[1] = inverseInertiaTensor[1].Transform(impulsiveTorque);
		velocityChange[1] = impulse * -mBodies[1]->GetInverseMass();

        // And apply them.
        mBodies[1]->AddVelocity(velocityChange[1]);
        mBodies[1]->AddRotation(rotationChange[1]);
    }
}

