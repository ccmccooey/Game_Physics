#ifndef _PARTICLE_CONTACT_H
#define _PARTICLE_CONTACT_H

#include "Vector3f.h"

class RigidBody;

class ParticleContact 
{
private:
	RigidBody *mParticleA, *mParticleB;
	float mRestitution;
	Vector3f mContactNormal;
	float mPenetrationDepth;  // +’ve if in collision

public:
	ParticleContact(RigidBody *a, RigidBody *b);
	ParticleContact(const ParticleContact &rhs);
	~ParticleContact();

	void Resolve(float duration);
	float SeparatingVelocity() const;
};

#endif
