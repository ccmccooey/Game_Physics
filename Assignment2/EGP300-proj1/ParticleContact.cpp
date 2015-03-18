#include "ParticleContact.h"
#include "Particle.h"

//constructor
ParticleContact::ParticleContact(Particle *a, Particle *b)
{
	mParticleA = a;
	mParticleB = b;
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
}
ParticleContact::ParticleContact(const ParticleContact &rhs)
{
	mParticleA = rhs.mParticleA;
	mParticleB = rhs.mParticleB;
	mRestitution = rhs.mRestitution;
	mContactNormal = rhs.mContactNormal;
	mPenetrationDepth = rhs.mPenetrationDepth;
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
Vector3f ParticleContact::GetActorADisplacement() const
{
	return mParticleA->GetPosition();
}
Vector3f ParticleContact::GetActorBDisplacement() const
{
	return mParticleB->GetPosition();
}
float ParticleContact::GetRestitution() const
{
	return mRestitution;
}
Vector3f ParticleContact::GetContactNormal() const
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
void ParticleContact::Resolve(float duration)
{
	float separatingVelocity = SeparatingVelocity();
	if (separatingVelocity <= 0 )
	{
		float newVelocity = -mRestitution * separatingVelocity;

		float totalMass = mParticleA->GetMass() + mParticleB->GetMass();

		float deltaVelocity = newVelocity - separatingVelocity;

		float impulseMagnitude = deltaVelocity / totalMass;
		Vector3f impulse = mContactNormal * impulseMagnitude;

		mParticleA->AddVelocity(impulse * mParticleB->GetMass());
		mParticleB->AddVelocity(impulse * mParticleA->GetMass());
	}
}
