#ifndef _GRAVITY_FORCE_GENERATOR_H
#define _GRAVITY_FORCE_GENERATOR_H

#define GRAVIATAIONAL_CONSTANT 6.673e-20

#include "Vector3f.h"
#include "ParticleForceGenerator.h"

class GravityForceGenerator :public ParticleForceGenerator
{
private:
	Rigidbody* mSource;
	float mGravityAcceleration; //I know its suppose to be calculated, but the numbers are too massive to be computed, even with long double

public:
	GravityForceGenerator();
	~GravityForceGenerator();

	Rigidbody* GetSource() const;

	void ApplyForce(Rigidbody* rb, double t);
	void SetRigidBody(Rigidbody* sourceOfForce);
};


#endif