#include "Enemy.h"
#include "MassAggregate.h"
#include "ObjectSpawner.h"
#include "Particle.h"
#include "GameObject.h"
#include "Random.h"

Enemy::Enemy(MassAggregate* massAggregate,  ObjectSpawner* spawner)
	:Collector(massAggregate, spawner)
{
	mAICounter = 0;
	mDesiredDirection = Vector3f::zero;

	int i = 0;
	GameObject* obj = mMA->GetGameObjectAt(0);
	while (obj != nullptr)
	{
		obj->SetMaterial("GreenBlob");
		i++;

		obj = mMA->GetGameObjectAt(i);		
	}
	
}
Enemy::~Enemy()
{

}
void Enemy::FixedUpdate(double t, std::vector<MassAggregate*> &addTo)
{
	Particle* particle = mMA->GetParticleAt(0);
	Vector3f velocity = particle->GetVelocity();
	Vector3f position = particle->GetPosition();

	if (mAICounter <= 0)
	{
		mAICounter = 20;
		mDesiredDirection = Vector3f(Random::ArithmeticFloat() * 10.0f, 0.0f, Random::ArithmeticFloat() * 10.0f);
		mDesiredDirection.Normalize();
	}

	//prevent AI from going out of bounds
	if (position.x >= 150.0f)
		mDesiredDirection.x = -1.0f;		
	else if (position.x <= -150.0f)
		mDesiredDirection.x = 1.0f;

	if (position.z >= 150.0f)
		mDesiredDirection.z = -1.0f;		
	else if (position.z <= -150.0f)
		mDesiredDirection.z = 1.0f;
	
	if (velocity.LengthSquared() < mMaxSpeed * mMaxSpeed)
		Push(mDesiredDirection * mForceAmount);
	
	

	Collector::FixedUpdate(t, addTo);
}