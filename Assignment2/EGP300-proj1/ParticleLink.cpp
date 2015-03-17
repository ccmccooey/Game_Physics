#include "ParticleLink.h"
#include "Particle.h"
#include "Transform.h"
#include "ScaleFactor.h"

ParticleLink::ParticleLink()
	:ParticleContactGenerator()
{
	mParticleA = nullptr;
	mParticleB = nullptr;
	mTransform = nullptr;
}
ParticleLink::ParticleLink(const ParticleLink &rhs)
	:ParticleContactGenerator(rhs)
{
	mParticleA = rhs.mParticleA;
	mParticleB = rhs.mParticleB;
	mTransform = nullptr;
}
ParticleLink::~ParticleLink()
{

}


float ParticleLink::CurrentLength() const
{
	return Vector3f::Distance(mParticleA->GetPosition(), mParticleB->GetPosition());
}

void ParticleLink::UpdateGraphicsPosition()
{
	if (mTransform != nullptr && mParticleA != nullptr && mParticleB != nullptr)
	{
		Vector3f position = Vector3f::Midpoint(mParticleA->GetPosition(), mParticleB->GetPosition());

		mTransform->SetPosition(position * DISTANCE_SCALE);

		float distance = Vector3f::Distance(mParticleA->GetPosition(), mParticleB->GetPosition());
		mTransform->SetScale(distance * DISTANCE_SCALE, 1.0f, 1.0f);

		
	}
}