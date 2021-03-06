#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include <vector>
#include <queue>

class Particle;
class ParticleForceGenerator;
class ParticleContactGenerator;
class ParticleContact;
class ParticleContactResolver;

using namespace std;

class ParticleSystem
{
private:
	vector<Particle*> mParticles;
	vector<ParticleForceGenerator*> mRegistry;
	vector<ParticleContactGenerator*> mContactGenerators;
	vector<ParticleContact*> mActiveContacts;
	ParticleContactResolver* mResolver;

	queue<ParticleContact*> mDeleteQueue;

public:
	ParticleSystem();
	~ParticleSystem();

	void FixedUpdate(double t);

	//getting particles
	Particle* GetParticleAt(int index) const;
	int GetTotalParticles() const;

	//adding and removing particles
	void AddParticle(Particle* particle);
	void AddForceGenerator(ParticleForceGenerator *forceGenerator);
	void AddContact(const ParticleContact *contact);
	void AddContactGenerator(ParticleContactGenerator* contactGenerator);

	void RemoveContactGenerator(ParticleContactGenerator* contactGenerator);
	void RemoveForceGenerator(ParticleForceGenerator *forceGenerator);
	void RemoveFromSystem(Particle* particle);
	void RemoveLast();

private:
	void FlushDeleteQueue();
};

#endif