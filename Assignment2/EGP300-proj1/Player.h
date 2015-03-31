#ifndef _PLAYER_H
#define _PLAYER_H

#include "Collector.h"

class Player :public Collector
{
private:

public:
	Player(MassAggregate* massAggregate, ObjectSpawner* spawner);
	~Player();

	void FixedUpdate(double t, std::vector<MassAggregate*> &addTo);
};

#endif