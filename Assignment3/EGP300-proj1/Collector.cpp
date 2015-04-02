#include "Collector.h"
#include "MassAggregate.h"
#include "ObjectSpawner.h"
#include "Particle.h"
#include "ParticleCable.h"
#include "ParticleRod.h"
#include "GameObjectLink.h"
#include "Random.h"

Collector::Collector(MassAggregate* massAggregate,  ObjectSpawner* spawner)
{
	mMA = massAggregate;
	mForceAmount = 20.0f;
	mMaxSpeed = 10.0f;
	mpSpawner = spawner;
	mExtraLinks = std::vector<GameObjectLink*>();
}
Collector::~Collector()
{
	for (unsigned int i = 0; i < mExtraLinks.size(); i++)
	{
		delete mExtraLinks[i];
	}
	mExtraLinks.clear();
}

MassAggregate* Collector::GetMassAggregate() const
{
	return mMA;
}

void Collector::FixedUpdate(double t, std::vector<MassAggregate*> &addTo)
{
	Particle* particle = mMA->GetParticleAt(0);
	Vector3f velocity = particle->GetVelocity();

	MassAggregate* ma = mpSpawner->CheckForObjectInRange(mMA->GetParticleAt(0)->GetPosition(), 5.0f);
	if (ma != nullptr)
	{
		mpSpawner->RemoveObject(ma);
		addTo.push_back(ma);

		ParticleCable* cable = new ParticleCable(Random::ArithmeticFloat() * 10.0f + 10.0f, Random::ArithmeticFloat() * 2.0f);
		cable->mParticleA = particle;
		cable->mParticleB = ma->GetParticleAt(0);

		GameObjectLink* link = new GameObjectLink("Cube", "BungeeLeather", cable);
		mExtraLinks.push_back(link);
	}

	for (unsigned int i = 0; i < mExtraLinks.size(); i++)
	{
		mExtraLinks[i]->LinkPositions();
	}
}
void Collector::Push(const Vector3f &force)
{
	Particle* particle = mMA->GetParticleAt(0);
	particle->AddForce(force);
}

const Vector3f& Collector::GetPosition() const
{
	return mMA->GetParticleAt(0)->GetPosition();
}
const Vector3f& Collector::GetVelocity() const
{
	return mMA->GetParticleAt(0)->GetVelocity();
}
int Collector::GetParticleCount() const
{
	return mMA->GetParticleCount();
}