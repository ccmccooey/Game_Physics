#include "ParticleContact.h"
#include "Particle.h"

//constructor
ParticleContact::ParticleContact(Particle *a, Particle *b)
{
	mParticleA = a;
	mParticleB = b;
	if (a == nullptr && b != nullptr)
	{
		mParticleA = b;
		mParticleB = a;
	}
}
ParticleContact::ParticleContact(Particle *a, Particle *b, float restitution, const Vector3f &contactNormal, float penetrationDepth)
{
	mParticleA = a;
	mParticleB = b;
	mRestitution = restitution;
	mContactNormal = contactNormal;
	mPenetrationDepth = penetrationDepth;
	mDisplacementA = Vector3f::zero;
	mDisplacementB = Vector3f::zero;

	if (a == nullptr && b != nullptr)
	{
		mParticleA = b;
		mParticleB = a;
	}
}
ParticleContact::ParticleContact(const ParticleContact &rhs)
{
	mParticleA = rhs.mParticleA;
	mParticleB = rhs.mParticleB;
	mRestitution = rhs.mRestitution;
	mContactNormal = rhs.mContactNormal;
	mPenetrationDepth = rhs.mPenetrationDepth;
	mDisplacementA = rhs.mDisplacementA;
	mDisplacementB = rhs.mDisplacementB;
}
ParticleContact::~ParticleContact()
{

}

//accessors
Particle* ParticleContact::GetActorA() const
{
	return mParticleA;
}
Particle* ParticleContact::GetActorB() const
{
	return mParticleB;
}
const Vector3f& ParticleContact::GetActorADisplacement() const
{
	return mDisplacementA;
}
const Vector3f& ParticleContact::GetActorBDisplacement() const
{
	return mDisplacementB;
}
float ParticleContact::GetRestitution() const
{
	return mRestitution;
}
Vector3f const& ParticleContact::GetContactNormal() const
{
	return mContactNormal;
}
float ParticleContact::GetPenetrationDepth() const
{
	return mPenetrationDepth;
}

//setters
void ParticleContact::SetParticleA(Particle *a)
{
	mParticleA = a;
}
void ParticleContact::SetParticleB(Particle *b)
{
	mParticleB = b;
}
void ParticleContact::SetRestitution(float restitution)
{
	mRestitution = restitution;
}
void ParticleContact::SetContactNormal(const Vector3f &normal)
{
	mContactNormal = normal;
}
void ParticleContact::SetContactNormal(float normalX, float normalY, float normalZ)
{
	mContactNormal.x = normalX;
	mContactNormal.y = normalY;
	mContactNormal.z = normalZ;
}
void ParticleContact::SetPenetrationDepth(float depth)
{
	mPenetrationDepth = depth;
}

//getting separting velocity
float ParticleContact::SeparatingVelocity() const
{
	Vector3f relativeVelocity = mParticleA->GetVelocity();
	if (mParticleB != nullptr)
	{
		relativeVelocity -= mParticleB->GetVelocity();
	}
	return Vector3f::DotProduct(relativeVelocity, mContactNormal);
}

//resolve the contact
/*
void ParticleContact::ResolveVelocity(float duration)
{
	float separatingVelocity = SeparatingVelocity();
	if (separatingVelocity <= 0 )
	{
		float massA = mParticleA->GetMass();
		float massB = 0.0f;
		if (mParticleB != nullptr)
		{
			massB = mParticleB->GetMass();
		}
		
		float newVelocity = -mRestitution * separatingVelocity;

		float totalMass = massA + massB;

		float deltaVelocity = newVelocity - separatingVelocity;

		float impulseMagnitude = deltaVelocity / totalMass;
		Vector3f impulse = mContactNormal * impulseMagnitude;

		mParticleA->AddVelocity(impulse * massB);
		if (mParticleB != nullptr)
		{
			mParticleB->AddVelocity(impulse * massA);
		}
	}
}*/
void ParticleContact::ResolveVelocity(float duration)
{
	float separatingVelocity = SeparatingVelocity();
	if (separatingVelocity <= 0 )
	{
		float massA = mParticleA->GetMass();
		float massB = 0.0f;
		if (mParticleB != nullptr)
		{
			massB = mParticleB->GetMass();
		}
		
		float newSepVelocity = -mRestitution * separatingVelocity;

		Vector3f accCausedVelocity = mParticleA->GetAcceleration();
		if (mParticleB != nullptr)
		{
			accCausedVelocity -= mParticleB->GetAcceleration();
		}
		float accCausedSepVelocity = Vector3f::DotProduct(accCausedVelocity, mContactNormal);

		if (accCausedSepVelocity < 0)
		{
			newSepVelocity += mRestitution * accCausedSepVelocity;
			if (newSepVelocity < 0)
				newSepVelocity = 0;
		}
		float deltaVelocity = newSepVelocity - separatingVelocity;
		float totalInverseMass = mParticleA->GetInverseMass();

		if (mParticleB != nullptr)
		{
			totalInverseMass += mParticleB->GetInverseMass();
		}

		if (totalInverseMass > 0)
		{
			float impulse = deltaVelocity / totalInverseMass;
			// Find the amount of impulse per unit of inverse mass.
			Vector3f impulsePerIMass = mContactNormal * impulse;
			if (mParticleB != nullptr)
			{
				totalInverseMass += mParticleB->GetInverseMass();
			}

			mParticleA->SetVelocity(mParticleA->GetVelocity() + impulsePerIMass * mParticleA->GetInverseMass());
			if (mParticleB != nullptr)
			{
				mParticleB->SetVelocity(mParticleB->GetVelocity() + impulsePerIMass * -mParticleB->GetInverseMass());
			}
		}
	}
}

void ParticleContact::ResolvePenetrationDepth(float duration)
{
	// If we don’t have any penetration, skip this step.
	if (mPenetrationDepth > 0)
	{
		// The movement of each object is based on their inverse mass,
		// so total that.

		float totalInverseMass = mParticleA->GetInverseMass();
		if (mParticleB != nullptr)
		{
			totalInverseMass += mParticleB->GetInverseMass();
		}

		// If all particles have infinite mass, then we do nothing.
		if (totalInverseMass > 0)
		{
			// Find the amount of penetration resolution per unit
			// of inverse mass.
			Vector3f movePerIMass = mContactNormal * (mPenetrationDepth / totalInverseMass);
			// Calculate the movement amounts.
			mDisplacementA = movePerIMass * mParticleA->GetInverseMass();
			if (mParticleB != nullptr) 
			{
				mDisplacementB = movePerIMass * -mParticleB->GetInverseMass();
			}
			else 
			{
				//mDisplacementB.clear();
				//mDisplacementB = Vector3f::zero;
			}
			// Apply the penetration resolution.
			mParticleA->SetPosition(mParticleA->GetPosition() + mDisplacementA);
			if (mParticleB != nullptr) 
			{
				mParticleB->SetPosition(mParticleB->GetPosition() + mDisplacementB);
			}
		}

	}
}
/*
//The code for this function came from the book
void ParticleContact::ResolveVelocity(float duration)
{
	// Find the velocity in the direction of the contact.
	float separatingVelocity = SeparatingVelocity();
	// Check if it needs to be resolved.
	if (separatingVelocity > 0)
	{
	// The contact is either separating, or stationary; there’s
	// no impulse required.
	return;
	}
	// Calculate the new separating velocity.
	real newSepVelocity = -separatingVelocity * restitution;
	// Check the velocity buildup due to acceleration only.
	Vector3 accCausedVelocity = mParticleA->getAcceleration();
	if (mParticleB) accCausedVelocity -= mParticleB->getAcceleration();
	real accCausedSepVelocity = accCausedVelocity * contactNormal
	* duration;
	// If we’ve got a closing velocity due to aceleration buildup,
	// remove it from the new separating velocity.
	if (accCausedSepVelocity < 0)
	7.2 Collision Processing 129
	{
	newSepVelocity += restitution * accCausedSepVelocity;
	// Make sure we haven’t removed more than was
	// there to remove.
	if (newSepVelocity < 0) newSepVelocity = 0;
	}
	real deltaVelocity = newSepVelocity - separatingVelocity;
	// We apply the change in velocity to each object in proportion to
	// their inverse mass (i.e., those with lower inverse mass [higher
	// actual mass] get less change in velocity).
	real totalInverseMass = mParticleA->getInverseMass();
	if (mParticleB) totalInverseMass += mParticleB->getInverseMass();
	// If all particles have infinite mass, then impulses have no effect.
	if (totalInverseMass <= 0) return;
	// Calculate the impulse to apply.
	real impulse = deltaVelocity / totalInverseMass;
	// Find the amount of impulse per unit of inverse mass.
	Vector3 impulsePerIMass = contactNormal * impulse;
	// Apply impulses: they are applied in the direction of the contact,
	// and are proportional to the inverse mass.
	mParticleA->setVelocity(mParticleA->getVelocity() +
	impulsePerIMass * mParticleA->getInverseMass()
	);
	if (mParticleB)
	{
	// Particle 1 goes in the opposite direction.
	mParticleB->setVelocity(mParticleB->getVelocity() +
	impulsePerIMass * -mParticleB->getInverseMass()
	);
	}
}*/
