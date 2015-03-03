#include "ParticleSystem.h"
#include "RigidBody.h"
#include "GravityForceGenerator.h"

ParticleSystem::ParticleSystem()
{
	mParticles = vector<Rigidbody*>();
	mRegistry = vector<ParticleForceGenerator*>();
}
ParticleSystem::~ParticleSystem()
{
	mParticles.clear();

	//remove all force generators from the registry
	for (unsigned int i = 0; i < mRegistry.size(); i++)
	{
		delete mRegistry[i];
		mRegistry[i] = nullptr;
	}
	mRegistry.clear();
}
void ParticleSystem::FixedUpdate(double t)
{
	unsigned int i, j;

	for (j = 0; j < mParticles.size(); j++)
	{
		for (i = 0; i < mRegistry.size(); i++)
		{
			mRegistry[i]->ApplyForce(mParticles[j], t);
		}
	}
}


void ParticleSystem::AddGravityForceGenerator(Rigidbody* source)
{
	GravityForceGenerator* gfg = new GravityForceGenerator();
	gfg->SetRigidBody(source);
	mRegistry.push_back(gfg);
}
void ParticleSystem::AddRigidBody(Rigidbody* rb)
{
	mParticles.push_back(rb);
}


void ParticleSystem::RemoveFromSystem(Rigidbody* rb)
{
	unsigned int i;
	for (i = 0; i < mParticles.size(); i++)
	{
		if (rb == mParticles[i])
		{
			mParticles.begin() + i;
			break;
		}
	}

}

void ParticleSystem::RemoveLast()
{
	mParticles.pop_back();
	ParticleForceGenerator* fg = mRegistry.back();
	delete fg;
	mRegistry.pop_back();
}