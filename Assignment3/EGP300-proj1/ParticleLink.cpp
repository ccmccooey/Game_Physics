#include "ParticleLink.h"
#include "Particle.h"
#include "Transform.h"
#include "ScaleFactor.h"

ParticleLink::ParticleLink()
	:ParticleContactGenerator()
{
	mParticleA = nullptr;
	mParticleB = nullptr;
}
ParticleLink::ParticleLink(const ParticleLink &rhs)
	:ParticleContactGenerator(rhs)
{
	mParticleA = rhs.mParticleA;
	mParticleB = rhs.mParticleB;
}
ParticleLink::~ParticleLink()
{

}


float ParticleLink::CurrentLength() const
{
	return Vector3f::Distance(mParticleA->GetPosition(), mParticleB->GetPosition());
}


const Vector3f& ParticleLink::GetPositionA() const
{
	return mParticleA->GetPosition();
}
const Vector3f& ParticleLink::GetPositionB() const
{
	return mParticleB->GetPosition();
}