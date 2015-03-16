#include "ParticleSystem.h"
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "ParticleContact.h"

ParticleSystem::ParticleSystem()
{
	mParticles = vector<Particle*>();
	mRegistry = vector<ParticleForceGenerator*>();
	mContactGenerators = vector<ParticleContactGenerator*>();
	mActiveContacts = vector<ParticleContact*>();
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

//getting particles
Particle* ParticleSystem::GetParticleAt(int index) const
{
	if (index >= 0 && index < (int)mParticles.size())
	{
		return mParticles[index];
	}
	return nullptr;
}
int ParticleSystem::GetTotalParticles() const
{
	return (int)mParticles.size();
}

//adding contacts
void ParticleSystem::AddContact(const ParticleContact *contact)
{
	mActiveContacts.push_back(new ParticleContact(*contact));
}

//adding generators
void ParticleSystem::AddGravityForceGenerator(Particle* source)
{
	GravityForceGenerator* gfg = new GravityForceGenerator();
	gfg->SetRigidBody(source);
	mRegistry.push_back(gfg);
}
void ParticleSystem::AddParticle(Particle* particle)
{
	mParticles.push_back(particle);
}


void ParticleSystem::RemoveFromSystem(Particle* particle)
{
	unsigned int i;
	for (i = 0; i < mParticles.size(); i++)
	{
		if (particle == mParticles[i])
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