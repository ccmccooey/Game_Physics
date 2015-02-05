#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include <vector>

class Rigidbody;
class ParticleForceGenerator;

using namespace std;

class ParticleSystem
{
private:
	vector<Rigidbody*> mParticles;
	vector<ParticleForceGenerator*> mRegistry;

public:
	ParticleSystem();
	~ParticleSystem();

	void FixedUpdate(double t);

	void AddGravityForceGenerator(Rigidbody* source);
	void AddRigidBody(Rigidbody* rb);
};

#endif