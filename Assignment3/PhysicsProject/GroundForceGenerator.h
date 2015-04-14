#ifndef _GROUND_FORCE_GENERATOR_H
#define _GROUND_FORCE_GENERATOR_H

#define DEFAULT_GROUND_FORCE 2.0f

#include "Vector3f.h"
#include "ForceGenerator.h"

class GroundForceGenerator :public ForceGenerator
{
private:
	float mGravity; //amount of gravity

public:
	GroundForceGenerator();
	GroundForceGenerator(float gravity);
	~GroundForceGenerator();

	float GetGravity() const;

	void SetGravity(float gravity);

	void ApplyForce(Particle* particle, double t);
	void ApplyForce(RigidBody* rigidBody, double t);
};


#endif