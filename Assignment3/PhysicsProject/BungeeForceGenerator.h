#ifndef _BUNGEE_FORCE_GENERATOR_H
#define _BUNGEE_FORCE_GENERATOR_H

#include "Vector3f.h"
#include "ForceGenerator.h"

class BungeeForceGenerator :public ForceGenerator
{
private:
	const float mK;
	const float mRestLength;
	Particle* mEndBody;

public:
	BungeeForceGenerator();
	BungeeForceGenerator(Particle* endBody);
	BungeeForceGenerator(float k, float restLength);
	BungeeForceGenerator(float k, float restLength, Particle* endBody);
	BungeeForceGenerator(const BungeeForceGenerator& rhs);
	~BungeeForceGenerator();

	//accessors
	float GetK() const;
	float GetRestLength() const;
	bool BodySet() const;
	bool BodyCleared() const;

	//setters
	void SetEndBody(Particle* endBody);
	void ClearEndBody();

	//apply force (override function)
	void ApplyForce(Particle* particle, double t);
	void ApplyForce(RigidBody* rigidBody, double t);
};

#endif