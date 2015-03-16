#include "ParticleCable.h"
#include "ParticleContact.h"
#include "ParticleSystem.h"
#include "Particle.h"

ParticleCable::ParticleCable()
	:ParticleLink()
{
	
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
	if (length < mMaxLength) return;

	ParticleContact contact = ParticleContact(mParticleA, mParticleB);
  
	Vector3f normal = Vector3f::DirectionTo(mParticleA->GetPosition(), mParticleB->GetPosition());
	//Vector3f normal = particle_b->position() - particle_a->position();
	//normal.normalize();

	contact.SetContactNormal(normal);
	contact.SetPenetrationDepth(length - mMaxLength);
	contact.SetRestitution(mRestitution);

	system->AddContact(&contact);

	return 0;
}