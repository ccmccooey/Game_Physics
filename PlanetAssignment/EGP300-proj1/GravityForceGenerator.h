#ifndef _GRAVITY_FORCE_GENERATOR_H
#define _GRAVITY_FORCE_GENERATOR_H

#define GRAVIATAIONAL_CONSTANT 6.673e-11

#include "Vector3f.h"
#include "ParticleForceGenerator.h"

class GravityForceGenerator :public ParticleForceGenerator
{
private:
	Rigidbody* mSource;

public:
	GravityForceGenerator();
	~GravityForceGenerator();


	void ApplyForce(Rigidbody* rb, double t);
	void SetRigidBody(Rigidbody* sourceOfForce);
};


#endif