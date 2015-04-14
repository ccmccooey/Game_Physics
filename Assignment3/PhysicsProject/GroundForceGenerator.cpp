#include "GroundForceGenerator.h"
#include "ScaleFactor.h"
#include "Particle.h"
#include "RigidBody.h"


GroundForceGenerator::GroundForceGenerator()
:ForceGenerator()
{
	mGravity = DEFAULT_GROUND_FORCE;
}
GroundForceGenerator::GroundForceGenerator(float gravity)
	:ForceGenerator()
{
	mGravity = gravity;
}
GroundForceGenerator::~GroundForceGenerator()
{

}


float GroundForceGenerator::GetGravity() const
{
	return mGravity;
}

void GroundForceGenerator::SetGravity(float gravity)
{
	mGravity = gravity;
}

void GroundForceGenerator::ApplyForce(Particle* particle, double t)
{	
	particle->AddForce(Vector3f::unitY * -mGravity);
}
void GroundForceGenerator::ApplyForce(RigidBody* rb, double t)
{	
	rb->AddForce(Vector3f::unitY * -mGravity);
}