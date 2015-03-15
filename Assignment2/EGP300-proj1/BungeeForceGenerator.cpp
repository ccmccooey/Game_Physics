#include "BungeeForceGenerator.h"
#include "Particle.h"

//constructors
BungeeForceGenerator::BungeeForceGenerator()
	:mK(1.0f), mRestLength(0.125f), ParticleForceGenerator()
{
	mEndBody = nullptr;
}
BungeeForceGenerator::BungeeForceGenerator(float k, float restLength)
	:mK(k), mRestLength(restLength), ParticleForceGenerator()
{
	mEndBody = nullptr;
}
BungeeForceGenerator::BungeeForceGenerator(Particle* endBody)
	:mK(1.0f), mRestLength(0.125f), ParticleForceGenerator()
{
	mEndBody = endBody;
}
BungeeForceGenerator::BungeeForceGenerator(float k, float restLength, Particle* endBody)
	:mK(k), mRestLength(restLength), ParticleForceGenerator()
{
	mEndBody = endBody;
}
BungeeForceGenerator::BungeeForceGenerator(const BungeeForceGenerator& rhs)
	:mK(rhs.mK), mRestLength(rhs.mRestLength), ParticleForceGenerator()
{
	mEndBody = rhs.mEndBody;
}

//destructor
BungeeForceGenerator::~BungeeForceGenerator()
{

}

//accessors
float BungeeForceGenerator::GetK() const
{
	return mK;
}
float BungeeForceGenerator::GetRestLength() const
{
	return mRestLength;
}
bool BungeeForceGenerator::BodySet() const
{
	return mEndBody != nullptr;
}
bool BungeeForceGenerator::BodyCleared() const
{
	return mEndBody == nullptr;
}

//setters
void BungeeForceGenerator::SetEndBody(Particle* endBody)
{
	mEndBody = endBody;
}
void BungeeForceGenerator::ClearEndBody()
{
	mEndBody = nullptr;
}

//apply force
void BungeeForceGenerator::ApplyForce(Particle* particle, double t)
{
	if (mEndBody != nullptr)
	{
		Vector3f force = particle->GetPosition();
		force -= mEndBody->GetPosition();

		float magnitude = force.Length();

		// Check to see if bungee is being compressed. If so, no force to apply.
		if (magnitude > mRestLength)
		{		
			magnitude = mK * (magnitude - mRestLength);
			force.Normalize();
			force *= -magnitude;
			particle->AddForce(force);
		}		
	}

}