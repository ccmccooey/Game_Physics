#ifndef _SPRING_FORCE_GENERATOR_H
#define _SPRING_FORCE_GENERATOR_H

#include "Vector3f.h"
#include "ForceGenerator.h"

class SpringForceGenerator :public ForceGenerator
{
private:
	const float mK;
	const float mRestLength;
	Particle* mEndBody;

public:
	SpringForceGenerator();
	SpringForceGenerator(Particle* endBody);
	SpringForceGenerator(float k, float restLength);
	SpringForceGenerator(float k, float restLength, Particle* endBody);
	SpringForceGenerator(const SpringForceGenerator& rhs);
	~SpringForceGenerator();

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