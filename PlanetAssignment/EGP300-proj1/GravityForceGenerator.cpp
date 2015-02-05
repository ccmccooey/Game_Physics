#include "GravityForceGenerator.h"
#include "RigidBody.h"


GravityForceGenerator::GravityForceGenerator()
:ParticleForceGenerator()
{
	mSource = nullptr;
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

	//Force = gravity 
	if (mSource != nullptr)
	{
		mGravityDirection = Vector3f::DirectionTo(mSource->GetPosition(), rb->GetPosition());

		float distance = Vector3f::Distance(rb->GetPosition(), mSource->GetPosition());
		float force = GRAVIATAIONAL_CONSTANT * ((mSource->GetMass() * rb->GetMass()) / (distance * distance));

		rb->AddForce(mGravityDirection * force);
	}
}

void  GravityForceGenerator::SetRigidBody(Rigidbody* sourceOfForce)
{
	mSource = sourceOfForce;
}