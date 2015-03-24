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

	for (j = 0; j < mParticles.size(); j++)
	{
		mParticles[j]->FixedUpdate(t);
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
void ParticleSystem::AddParticle(Particle* particle)
{
	mParticles.push_back(particle);
}
void ParticleSystem::AddContactGenerator(ParticleContactGenerator* contactGenerator)
{
	mContactGenerators.push_back(contactGenerator);
}
void ParticleSystem::AddForceGenerator(ParticleForceGenerator *forceGenerator)
{
	mRegistry.push_back(forceGenerator);
}

void ParticleSystem::RemoveFromSystem(Particle* particle)
{
	unsigned int i;
	for (i = 0; i < mParticles.size(); i++)
	{
		if (particle == mParticles[i])
		{
			mParticles.erase(mParticles.begin() + i);
			break;
		}
	}
}
void ParticleSystem::RemoveContactGenerator(ParticleContactGenerator* contactGenerator)
{
	unsigned int i;
	for (i = 0; i < mContactGenerators.size(); i++)
	{
		if (contactGenerator == mContactGenerators[i])
		{
			mContactGenerators.erase(mContactGenerators.begin() + i);
			break;
		}
	}
}
void ParticleSystem::RemoveForceGenerator(ParticleForceGenerator *forceGenerator)
{
	unsigned int i;
	for (i = 0; i < mRegistry.size(); i++)
	{
		if (forceGenerator == mRegistry[i])
		{
			mRegistry.erase(mRegistry.begin() + i);
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