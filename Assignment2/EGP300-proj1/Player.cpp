#include "Player.h"
#include "InputSystem.h"
#include "MassAggregate.h"
#include "ObjectSpawner.h"
#include "Particle.h"
#include "GameObjectLink.h"
#include "Random.h"

Player::Player(MassAggregate* massAggregate,  ObjectSpawner* spawner)
	:Collector(massAggregate, spawner)
{

}
Player::~Player()
{

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
	if (InputSystem::KeyPressed(' '))
	{
		Vector3f position = particle->GetPosition();
		if (position.y < -9.0f)
		{
			Push(Vector3f::unitY * mForceAmount * 2.0f);
		}
	}

	Collector::FixedUpdate(t, addTo);
}