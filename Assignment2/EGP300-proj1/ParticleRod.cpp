#include "ParticleRod.h"
#include "ParticleContact.h"
#include "ParticleSystem.h"
#include "Particle.h"

ParticleRod::ParticleRod()
	:ParticleLink()
{

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
  
	Vector3f normal = Vector3f::DirectionTo(mParticleA->GetPosition(), mParticleB->GetPosition());
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