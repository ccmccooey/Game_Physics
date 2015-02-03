#ifndef _PARTICLE_H
#define _PARTICLE_H

#include "DisplayObject3D.h"
#include "Vector3f.h"


class Particle :public DisplayObject3D
{
	Vector3f mVelocity;
	Vector3f mAcceleration;
	Vector3f mForce;
	float mMass;

public:
	Particle(Model* model);
	~Particle();

	void AddForce(const Vector3f &force);
	void FixedUpdate();
};

#endif