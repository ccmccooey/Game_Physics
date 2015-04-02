#ifndef _PARTICLE_CONTACT_GENERATOR_H
#define _PARTICLE_CONTACT_GENERATOR_H

class ParticleSystem;

class ParticleContactGenerator
{
public:
	ParticleContactGenerator();
	virtual ~ParticleContactGenerator();

	virtual int AddContact(ParticleSystem *system) = 0;
};

#endif