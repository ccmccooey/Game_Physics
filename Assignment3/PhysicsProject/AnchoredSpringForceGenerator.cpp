#include "AnchoredSpringForceGenerator.h"
#include "RigidBody.h"
#include "Particle.h"

//constructors
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator()
	:mK(1.0f), mRestLength(0.125f)
{
	mAnchor = Vector3f::zero;
}
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(float k, float restLength, const Vector3f &anchor)
	:mK(k), mRestLength(restLength)
{
	mAnchor = anchor;
}
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(float k, float restLength, float anchorX, float anchorY, float anchorZ)
	:mK(k), mRestLength(restLength)
{
	mAnchor = Vector3f(anchorX, anchorY, anchorZ);
}
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(float k, float restLength, const Vector3f &directionNormal, float length)
	:mK(k), mRestLength(restLength)
{
	mAnchor = directionNormal * length;
}
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(const AnchoredSpringForceGenerator& rhs)
	:mK(rhs.mK), mRestLength(rhs.mRestLength)
{
	mAnchor = rhs.mAnchor;
}

//destructor
AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator()
{

}

//accessors
Vector3f AnchoredSpringForceGenerator::GetAnchor() const
{
	return mAnchor;
}

//apply force
void AnchoredSpringForceGenerator::ApplyForce(Particle* particle, double t)
{
	Vector3f force = particle->GetPosition() - mAnchor;

	float magnitude = force.Length();
	magnitude = fabs(magnitude - mRestLength);
	magnitude *= mK;

	force.Normalize();
	force *= -magnitude;
	particle->AddForce(force);
}
void AnchoredSpringForceGenerator::ApplyForce(RigidBody* rb, double t)
{
	Vector3f force = rb->GetPosition() - mAnchor;

	float magnitude = force.Length();
	magnitude = fabs(magnitude - mRestLength);
	magnitude *= mK;

	force.Normalize();
	force *= -magnitude;
	rb->AddForce(force);
}