#include "GroundContactGenerator.h"
#include "ParticleContact.h"
#include "ParticleSystem.h"
#include "Particle.h"

GroundContactGenerator::GroundContactGenerator()
	:ParticleContactGenerator()
{
	mGroundHeight = 0.0f;
}
GroundContactGenerator::GroundContactGenerator(float groundHeight)
	:ParticleContactGenerator()
{
	mGroundHeight = groundHeight;
}
GroundContactGenerator::GroundContactGenerator(const GroundContactGenerator &rhs)
	:ParticleContactGenerator(rhs)
{
	mGroundHeight = rhs.mGroundHeight;
}
GroundContactGenerator::~GroundContactGenerator()
{

}

//accessors
float GroundContactGenerator::GetGroundHeight() const
{
	return mGroundHeight;
}

//setters
void GroundContactGenerator::SetGroundHeight(float height)
{
	mGroundHeight = height;
}

int GroundContactGenerator::AddContact(ParticleSystem *system)
{
	Particle *current;
	Vector3f currentPosition;
	int i;
	int count = system->GetTotalParticles();
	
	for (i = 0; i < count; i++) 
	{
		current = system->GetParticleAt(i);
		currentPosition = current->GetPosition();
		if (currentPosition.y < mGroundHeight) 
		{
			ParticleContact contact = ParticleContact(current, nullptr, 0.5f, Vector3f::unitY, fabsf(currentPosition.y - mGroundHeight));

			/*
			contact.penetration_depth =
				particle.position().y() - ground_height;
			contact.particle_a = &particle;
			contact.restitution = 0.5f;  // Arbitrary
			contact.contact_normal = Vector3f(0.0f, 1.0f, 0.0f);*/
			
			system->AddContact(&contact);
		}
	}
	return count;
}