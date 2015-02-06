#include "GravityForceGenerator.h"
#include "PlanetScaleFactor.h"
#include "RigidBody.h"
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


void GravityForceGenerator::ApplyForce(Rigidbody* rb, double t)
{
	//rb->getForce() += 9.8 * mGravityDirection * rb->mass();

	/*
	: I know I need the distance between the positions of the two planets
	take distance between two planets and divide that by the squared

then get their mass

and we need a vector indicating the direction

	the direction is just subtracting the positions and normalizing it
		*/

	if (rb == mSource)
	{ 
		//this prevents stuff from having force on itself
		return;
	}

	//Force = gravity 
	if (mSource != nullptr)
	{
		
		mGravityDirection = Vector3f::DirectionTo(mSource->GetPosition(), rb->GetPosition());
		/*
		float distance = Vector3f::Distance(rb->GetPosition(), mSource->GetPosition()) * 1000; //1000 km to m

		double val = (double)mSource->GetMass() * GRAVIATAIONAL_CONSTANT * (double)rb->GetMass();
		double force =  (val / ((double)distance * (double)distance));
	
		//float force = GRAVIATAIONAL_CONSTANT * rb->GetMass();
		mGravityAcceleration = (float)force;*/

		rb->AddForce(mGravityDirection * (rb->GetMass() * mGravityAcceleration));

		//rb->AddForce(mGravityDirection * mGravityAcceleration
	}
}

void  GravityForceGenerator::SetRigidBody(Rigidbody* sourceOfForce)
{
	mSource = sourceOfForce;
}