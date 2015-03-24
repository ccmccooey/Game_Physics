#ifndef _GROUND_CONTACT_GENERATOR_H
#define _GROUND_CONTACT_GENERATOR_H

#include "ParticleContactGenerator.h"

class GroundContactGenerator :public ParticleContactGenerator
{
private:
	float mGroundHeight;

public:
	GroundContactGenerator();
	GroundContactGenerator(float groundHeight);
	GroundContactGenerator(const GroundContactGenerator &rhs);
	~GroundContactGenerator();

	//accessors
	float GetGroundHeight() const;

	//setters
	void SetGroundHeight(float height);

	int AddContact(ParticleSystem *system);
};


#endif