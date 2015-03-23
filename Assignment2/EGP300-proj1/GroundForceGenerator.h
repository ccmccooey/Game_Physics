#ifndef _GROUND_FORCE_GENERATOR_H
#define _GROUND_FORCE_GENERATOR_H

#define DEFAULT_GROUND_FORCE 2.0f

#include "Vector3f.h"
#include "ParticleForceGenerator.h"

class GroundForceGenerator :public ParticleForceGenerator
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
};


#endif