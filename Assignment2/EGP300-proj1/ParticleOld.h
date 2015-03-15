#ifndef _PARTICLE_OLD_H
#define _PARTICLE_OLD_H

#include "DisplayObject3D.h"
#include "Vector3f.h"


class ParticleOld :public DisplayObject3D
{
	Vector3f mVelocity;
	Vector3f mAcceleration;
	Vector3f mForce;
	float mMass;

public:
	ParticleOld(Model* model);
	~ParticleOld();

	void AddForce(const Vector3f &force);
	void FixedUpdate();
};

#endif