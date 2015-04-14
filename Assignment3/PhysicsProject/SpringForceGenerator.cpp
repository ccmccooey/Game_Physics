#include "SpringForceGenerator.h"
#include "Particle.h"
#include "RigidBody.h"

//constructors
SpringForceGenerator::SpringForceGenerator()
	:mK(1.0f), mRestLength(0.125f), ForceGenerator()
{
	mEndBody = nullptr;
}
SpringForceGenerator::SpringForceGenerator(float k, float restLength)
	:mK(k), mRestLength(restLength), ForceGenerator()
{
	mEndBody = nullptr;
}
SpringForceGenerator::SpringForceGenerator(Particle* endBody)
	:mK(1.0f), mRestLength(0.125f), ForceGenerator()
{
	mEndBody = endBody;
}
SpringForceGenerator::SpringForceGenerator(float k, float restLength, Particle* endBody)
	:mK(k), mRestLength(restLength), ForceGenerator()
{
	mEndBody = endBody;
}
SpringForceGenerator::SpringForceGenerator(const SpringForceGenerator& rhs)
	:mK(rhs.mK), mRestLength(rhs.mRestLength), ForceGenerator()
{
	mEndBody = rhs.mEndBody;
}

//destructor
SpringForceGenerator::~SpringForceGenerator()
{

}

//accessors
float SpringForceGenerator::GetK() const
{
	return mK;
}
float SpringForceGenerator::GetRestLength() const
{
	return mRestLength;
}
bool SpringForceGenerator::BodySet() const
{
	return mEndBody != nullptr;
}
bool SpringForceGenerator::BodyCleared() const
{
	return mEndBody == nullptr;
}

//setters
void SpringForceGenerator::SetEndBody(Particle* endBody)
{
	mEndBody = endBody;
}
void SpringForceGenerator::ClearEndBody()
{
	mEndBody = nullptr;
}

//apply force
void SpringForceGenerator::ApplyForce(Particle* particle, double t)
{
	if (mEndBody != nullptr)
	{
		Vector3f force= particle->GetPosition();
		Vector3f endPosition = mEndBody->GetPosition();
		force -= endPosition;

		float magnitude = force.Length();
		magnitude = abs(magnitude - mRestLength);
		magnitude *= mK;

		force.Normalize();
		force *= -magnitude;
		particle->AddForce(force);
	}

}
void SpringForceGenerator::ApplyForce(RigidBody* rb, double t)
{
	if (mEndBody != nullptr)
	{
		Vector3f force= rb->GetPosition();
		Vector3f endPosition = mEndBody->GetPosition();
		force -= endPosition;

		float magnitude = force.Length();
		magnitude = abs(magnitude - mRestLength);
		magnitude *= mK;

		force.Normalize();
		force *= -magnitude;
		rb->AddForce(force);
	}
}