#ifndef _PLAYER_H
#define _PLAYER_H

#include "Vector3f.h"

class MassAggregate;

class Player
{
private:
	MassAggregate *mMA;
	float mForceAmount;
	float mMaxSpeed;

public:
	Player(MassAggregate* massAggregate);
	~Player();

	MassAggregate* GetMassAggregate() const;

	void FixedUpdate(double t);
	void Push(const Vector3f &force);	
};

#endif