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

	void FixedUpdate(double t);
};

#endif