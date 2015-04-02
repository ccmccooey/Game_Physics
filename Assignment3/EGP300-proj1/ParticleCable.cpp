#include "ParticleCable.h"
#include "ParticleContact.h"
#include "ParticleSystem.h"
#include "Particle.h"

ParticleCable::ParticleCable()
	:ParticleLink()
{
	mMaxLength = 2.0f;
	mRestitution = 0.0f;
}
ParticleCable::ParticleCable(float maxLength, float restitution)
	:ParticleLink()
{
	mRestitution = restitution;
	mMaxLength = maxLength;
}
ParticleCable::ParticleCable(const ParticleCable &rhs)
	:ParticleLink(rhs)
{
	mRestitution = rhs.mRestitution;
	mMaxLength = rhs.mMaxLength;
}
ParticleCable::~ParticleCable()
{

}

int ParticleCable::AddContact(ParticleSystem* system) 
{
	float length = CurrentLength();
	if (length < mMaxLength) 
		return 1;

	ParticleContact contact = ParticleContact(mParticleA, mParticleB);
  
	Vector3f normal = Vector3f::DirectionTo(mParticleB->GetPosition(), mParticleA->GetPosition());
	//Vector3f normal = particle_b->position() - particle_a->position();
	//normal.normalize();

	contact.SetContactNormal(normal);
	contact.SetPenetrationDepth(length - mMaxLength);
	contact.SetRestitution(mRestitution);

	system->AddContact(&contact);

	return 0;
}