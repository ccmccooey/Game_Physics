#ifndef _PARTICLE_CABLE_H
#define _PARTICLE_CABLE_H

class ParticleSystem;

#include "ParticleLink.h"

class ParticleCable : public ParticleLink 
{
public:
	float mMaxLength;
	float mRestitution;

public:
	ParticleCable();
	ParticleCable(float maxLength, float restitution);
	ParticleCable(const ParticleCable &rhs);
	~ParticleCable();

	int AddContact(ParticleSystem *system);
};

#endif