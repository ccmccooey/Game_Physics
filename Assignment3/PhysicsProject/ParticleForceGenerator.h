#ifndef _PARTICLE_FORCE_GENERATOR_H
#define _PARTICLE_FORCE_GENERATOR_H

#include "Vector3f.h"

class Particle;

class ParticleForceGenerator
{
protected:
	Vector3f mGravityDirection;

public:
	ParticleForceGenerator();
	virtual ~ParticleForceGenerator();

	virtual void ApplyForce(Particle* particle, double duration)=0;
};

#endif