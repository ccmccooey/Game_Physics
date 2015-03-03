#ifndef _SPRING_FORCE_GENERATOR_H
#define _SPRING_FORCE_GENERATOR_H

#include "Vector3f.h"
#include "ParticleForceGenerator.h"

class SpringForceGenerator :public ParticleForceGenerator
{
private:
	float mSpringAcceleration;

public:
	SpringForceGenerator();
	~SpringForceGenerator();

	void ApplyForce(Rigidbody* rb, double t);
};

#endif