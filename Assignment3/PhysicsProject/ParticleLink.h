#ifndef _PARTICLE_LINK_H
#define _PARTICLE_LINK_H

#include "Vector3f.h"

class Transform;
class Particle;

#include "ParticleContactGenerator.h"

class ParticleLink : public ParticleContactGenerator 
{
public:
	Particle *mParticleA;
	Particle *mParticleB;

public:
	ParticleLink();
	ParticleLink(const ParticleLink &rhs);
	~ParticleLink();

	float CurrentLength() const;

	const Vector3f& GetPositionA() const;
	const Vector3f& GetPositionB() const;
};

#endif