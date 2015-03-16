#ifndef _PARTICLE_CONTACT_RESOLVER_H
#define _PARTICLE_CONTACT_RESOLVER_H

class ParticleContact;

class ParticleContactResolver
{
private:
	int mPasses;

public:
	ParticleContactResolver();
	~ParticleContactResolver();

	void MultiPassResolveContacts(ParticleContact **contacts, int num_contacts, float duration);
};

#endif