#ifndef _PARTICLE_ROD_H
#define _PARTICLE_ROD_H

#include "ParticleLink.h"

class ParticleRod : public ParticleLink 
{
public:
	float mLength;

public:
	ParticleRod();
	ParticleRod(float length);
	ParticleRod(const ParticleRod &rhs);
	~ParticleRod();

	int AddContact(ParticleSystem* system);
};

#endif