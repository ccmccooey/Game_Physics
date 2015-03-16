#include "ParticleLink.h"

ParticleLink::ParticleLink()
	:ParticleContactGenerator()
{

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