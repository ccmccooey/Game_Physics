#include "GravityForceGenerator.h"



GravityForceGenerator::GravityForceGenerator()
:ParticleForceGenerator()
{

}
GravityForceGenerator::~GravityForceGenerator()
{

}


void GravityForceGenerator::UpdateForce(RigidBody* rb, double t)
{
	//rb->getForce() += 9.8 * mGravityDirection * rb->mass();

	/*
	: I know I need the distance between the positions of the two planets
	take distance between two planets and divide that by the squared

then get their mass

and we need a vector indicating the direction

	the direction is just subtracting the positions and normalizing it
		*/
}