#ifndef _PARTICLE_LINK_H
#define _PARTICLE_LINK_H

class Transform;
class Particle;

#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator 
{
public:
	Particle *mParticleA;
	Particle *mParticleB;
	Transform* mTransform;

public:
	ParticleLink();
	ParticleLink(const ParticleLink &rhs);
	~ParticleLink();

	float CurrentLength() const;

	void UpdateGraphicsPosition();
};

#endif