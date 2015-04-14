#ifndef _PARTICLE_FORCE_GENERATOR_H
#define _PARTICLE_FORCE_GENERATOR_H

#include "Vector3f.h"

class Particle;
class RigidBody;

class ForceGenerator
{
protected:
	Vector3f mGravityDirection;

public:
	ForceGenerator();
	virtual ~ForceGenerator();

	virtual void ApplyForce(Particle* particle, double duration)=0;
	virtual void ApplyForce(RigidBody* ridigBody, double duration)=0;
};

#endif