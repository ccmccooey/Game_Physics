#ifndef _ANCHORED_SPRING_FORCE_GENERATOR_H
#define _ANCHORED_SPRING_FORCE_GENERATOR_H

#include "Vector3f.h"
#include "ParticleForceGenerator.h"

class AnchoredSpringForceGenerator :public ParticleForceGenerator
{
private:
	float const mK;
	float const mRestLength;
	Vector3f mAnchor;

public:
	AnchoredSpringForceGenerator();
	AnchoredSpringForceGenerator(float k, float restLength, const Vector3f &anchor);
	AnchoredSpringForceGenerator(float k, float restLength, float anchorX, float anchorY, float anchorZ);
	AnchoredSpringForceGenerator(float k, float restLength, const Vector3f &directionNormal, float length);
	AnchoredSpringForceGenerator(const AnchoredSpringForceGenerator& rhs);
	~AnchoredSpringForceGenerator();

	//accessors
	Vector3f GetAnchor() const;

	//apply force
	void ApplyForce(Particle* particle, double t);
};

#endif