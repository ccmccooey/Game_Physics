#ifndef _PARTICLE_CONTACT_H
#define _PARTICLE_CONTACT_H

#include "Vector3f.h"

class Particle;

class ParticleContact 
{
private:
	Particle *mParticleA;
	Particle *mParticleB;
	float mRestitution;
	Vector3f mContactNormal;
	float mPenetrationDepth;  // +’ve if in collision
	Vector3f mDisplacementA;
	Vector3f mDisplacementB;

public:
	ParticleContact(Particle *a, Particle *b);
	ParticleContact(Particle *a, Particle *b, float restitution, const Vector3f &contactNormal, float penetrationDepth);
	ParticleContact(const ParticleContact &rhs);
	~ParticleContact();

	//accessors
	Particle* GetActorA() const;
	Particle* GetActorB() const;
	Vector3f GetActorADisplacement() const;
	Vector3f GetActorBDisplacement() const;
	float GetRestitution() const;
	Vector3f GetContactNormal() const;
	float GetPenetrationDepth() const;

	//setters
	void SetParticleA(Particle *a);
	void SetParticleB(Particle *b);
	void SetRestitution(float restitution);
	void SetContactNormal(const Vector3f &normal);
	void SetContactNormal(float normalX, float normalY, float normalZ);
	void SetPenetrationDepth(float depth);

	//resolution
	float SeparatingVelocity() const;
	void ResolveVelocity(float duration);
	void ResolvePenetrationDepth(float duration);	
};

#endif
