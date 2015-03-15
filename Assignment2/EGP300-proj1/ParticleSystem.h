#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include <vector>

class Particle;
class ParticleForceGenerator;

using namespace std;

class ParticleSystem
{
private:
	vector<Particle*> mParticles;
	vector<ParticleForceGenerator*> mRegistry;

public:
	ParticleSystem();
	~ParticleSystem();

	void FixedUpdate(double t);

	void AddGravityForceGenerator(Particle* source);
	void AddRigidBody(Particle* particle);
	void RemoveFromSystem(Particle* particle);
	void RemoveLast();
};

#endif