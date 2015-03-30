#include "Player.h"
#include "InputSystem.h"
#include "MassAggregate.h"
#include "Particle.h"

Player::Player(MassAggregate* massAggregate)
{
	mMA = massAggregate;
	mForceAmount = 20.0f;
	mMaxSpeed = 10.0f;
}
Player::~Player()
{

}

MassAggregate* Player::GetMassAggregate() const
{
	return mMA;
}

void Player::FixedUpdate(double t)
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
}
void Player::Push(const Vector3f &force)
{
	Particle* particle = mMA->GetParticleAt(0);
	particle->AddForce(force);
}