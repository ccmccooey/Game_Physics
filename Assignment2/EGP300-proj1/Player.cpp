#include "Player.h"
#include "MainApp.h"
#include "InputSystem.h"
#include "MassAggregate.h"
#include "ObjectSpawner.h"
#include "Particle.h"
#include "ParticleCable.h"
#include "ParticleRod.h"
#include "GameObjectLink.h"
#include "Random.h"

Player::Player(MassAggregate* massAggregate,  ObjectSpawner* spawner)
{
	mMA = massAggregate;
	mForceAmount = 20.0f;
	mMaxSpeed = 10.0f;
	mpSpawner = spawner;
	mExtraLinks = std::vector<GameObjectLink*>();
}
Player::~Player()
{
	for (unsigned int i = 0; i < mExtraLinks.size(); i++)
	{
		delete mExtraLinks[i];
	}
	mExtraLinks.clear();
}

MassAggregate* Player::GetMassAggregate() const
{
	return mMA;
}

void Player::FixedUpdate(double t, std::vector<MassAggregate*> &addTo)
{
	Particle* particle = mMA->GetParticleAt(0);
	Vector3f velocity = particle->GetVelocity();

	if (InputSystem::KeyDown('a') || InputSystem::KeyDown('A'))
	{
		if (velocity.x > -mMaxSpeed)
			Push(-Vector3f::unitX * mForceAmount);
	}
	else if (InputSystem::KeyDown('d') || InputSystem::KeyDown('D'))
	{
		if (velocity.x < mMaxSpeed)
			Push(Vector3f::unitX * mForceAmount);
	}
	if (InputSystem::KeyDown('s') || InputSystem::KeyDown('S'))
	{
		if (velocity.z < mMaxSpeed)
			Push(Vector3f::unitZ * mForceAmount);
	}
	else if (InputSystem::KeyDown('w') || InputSystem::KeyDown('W'))
	{
		if (velocity.z > -mMaxSpeed)
			Push(-Vector3f::unitZ * mForceAmount);
	}

	
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
void Player::Push(const Vector3f &force)
{
	Particle* particle = mMA->GetParticleAt(0);
	particle->AddForce(force);
}