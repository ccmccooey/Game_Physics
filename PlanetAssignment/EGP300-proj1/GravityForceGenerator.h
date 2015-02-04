#ifndef _GRAVITY_FORCE_GENERATOR_H
#define _GRAVITY_FORCE_GENERATOR_H

#include "ParticleForceGenerator.h"

class GravityForceGenerator :public ParticleForceGenerator
{
public:
	GravityForceGenerator();
	~GravityForceGenerator();


	void UpdateForce(RigidBody* rb, double t);
};


#endif