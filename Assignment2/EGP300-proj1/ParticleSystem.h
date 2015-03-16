#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include <vector>

class Particle;
class ParticleForceGenerator;
class ParticleContactGenerator;
class ParticleContact;

using namespace std;

class ParticleSystem
{
private:
	vector<Particle*> mParticles;
	vector<ParticleForceGenerator*> mRegistry;
	vector<ParticleContactGenerator*> mContactGenerators;
	vector<ParticleContact*> mActiveContacts;

public:
	ParticleSystem();
	~ParticleSystem();

	void FixedUpdate(double t);

	//getting particles
	Particle* GetParticleAt(int index) const;
	int GetTotalParticles() const;

	//adding and removing particles
	void AddGravityForceGenerator(Particle* source);
	void AddParticle(Particle* particle);
	void AddContact(const ParticleContact *contact);
	void RemoveFromSystem(Particle* particle);
	void RemoveLast();
};

#endif