#include "ParticleRod.h"
#include "ParticleContact.h"
#include "ParticleSystem.h"
#include "Particle.h"

#define PARTICLE_ROD_DEFAULT_LENGTH 1

ParticleRod::ParticleRod()
	:ParticleLink()
{
	mLength = PARTICLE_ROD_DEFAULT_LENGTH;
}
ParticleRod::ParticleRod(float length)
	:ParticleLink()
{
	mLength = length;
}
ParticleRod::ParticleRod(const ParticleRod &rhs)
	:ParticleLink(rhs)
{
	mLength = rhs.mLength;
}
ParticleRod::~ParticleRod()
{

}


int ParticleRod::AddContact(ParticleSystem* system) 
{
	float length = CurrentLength();
	if (length == mLength)
	{
		return -1;
	}
	ParticleContact contact = ParticleContact(mParticleA, mParticleB);
  
	Vector3f normal = Vector3f::DirectionTo(mParticleB->GetPosition(), mParticleA->GetPosition());
	//Vector3f normal = particle_b->position() - particle_a->position();
	//normal.normalize();

	if (length > mLength) 
	{
		contact.SetContactNormal(normal);
		contact.SetPenetrationDepth(length - mLength);
	}
	else
	{
		contact.SetContactNormal(normal * -1.0f);
		contact.SetPenetrationDepth(mLength - length);
	} 
	contact.SetRestitution(0.0f);

	system->AddContact(&contact);
	return 0;
}