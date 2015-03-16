#ifndef _PARTICLE_LINK_H
#define _PARTICLE_LINK_H

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
};

#endif