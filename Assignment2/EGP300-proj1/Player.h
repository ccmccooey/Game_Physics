#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include "Vector3f.h"

class GameObjectLink;
class ObjectSpawner;
class MassAggregate;

class Player
{
private:
	MassAggregate *mMA;
	ObjectSpawner* mpSpawner;
	std::vector<GameObjectLink*> mExtraLinks;
	float mForceAmount;
	float mMaxSpeed;

public:
	Player(MassAggregate* massAggregate, ObjectSpawner* spawner);
	~Player();

	MassAggregate* GetMassAggregate() const;

	void FixedUpdate(double t, std::vector<MassAggregate*> &addTo);
	void Push(const Vector3f &force);	
};

#endif