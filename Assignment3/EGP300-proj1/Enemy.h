#ifndef _ENEMY_H
#define _ENEMY_H

#include "Collector.h"

class Enemy :public Collector
{
private:
	int mAICounter;
	Vector3f mDesiredDirection;

public:
	Enemy(MassAggregate* massAggregate, ObjectSpawner* spawner);
	~Enemy();
	
	void FixedUpdate(double t, std::vector<MassAggregate*> &addTo);
};


#endif