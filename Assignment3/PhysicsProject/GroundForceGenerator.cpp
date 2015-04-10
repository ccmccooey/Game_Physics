#include "GroundForceGenerator.h"
#include "ScaleFactor.h"
#include "Particle.h"
#include <limits>


GroundForceGenerator::GroundForceGenerator()
:ParticleForceGenerator()
{
	mGravity = DEFAULT_GROUND_FORCE;
}
GroundForceGenerator::GroundForceGenerator(float gravity)
	:ParticleForceGenerator()
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