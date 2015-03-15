#include "GravityForceGenerator.h"
#include "ScaleFactor.h"
#include "Particle.h"
#include <limits>


GravityForceGenerator::GravityForceGenerator()
:ParticleForceGenerator()
{
	mSource = nullptr;

	mGravityAcceleration = 27.94;// * PLANET_GRAVITY_FACTOR;
}
GravityForceGenerator::~GravityForceGenerator()
{

}


Particle* GravityForceGenerator::GetSource() const
{
	return mSource;
}

void GravityForceGenerator::ApplyForce(Particle* particle, double t)
{
	//particle->getForce() += 9.8 * mGravityDirection * particle->mass();

	/*
	: I know I need the distance between the positions of the two planets
	take distance between two planets and divide that by the squared

then get their mass

and we need a vector indicating the direction

	the direction is just subtracting the positions and normalizing it
		*/

	if (particle == mSource)
	{ 
		//this prevents stuff from having force on itself
		return;
	}

	//Force = gravity 
	if (mSource != nullptr)
	{
		
		mGravityDirection = Vector3f::DirectionTo(mSource->GetPosition(), particle->GetPosition());
		
		double distance = (double)Vector3f::Distance(particle->GetPosition(), mSource->GetPosition());// *1000; //1000 km to m

		double val = (double)mSource->GetMass() * GRAVIATAIONAL_CONSTANT * (double)particle->GetMass();
		double force =  val / (distance * distance);
	
		//float force = GRAVIATAIONAL_CONSTANT * particle->GetMass();
		mGravityAcceleration = (float)force;

		//particle->AddForce(mGravityDirection * (particle->GetMass() * mGravityAcceleration));
		particle->AddForce(mGravityDirection * mGravityAcceleration);

		//particle->AddForce(mGravityDirection * mGravityAcceleration
	}
}

void  GravityForceGenerator::SetRigidBody(Particle* sourceOfForce)
{
	mSource = sourceOfForce;
}