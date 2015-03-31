#ifndef _COLLECTOR_H
#define _COLLECTOR_H

#include <vector>
#include "Vector3f.h"

class GameObjectLink;
class ObjectSpawner;
class MassAggregate;

class Collector
{
protected:
	MassAggregate *mMA;
	ObjectSpawner* mpSpawner;
	std::vector<GameObjectLink*> mExtraLinks;
	float mForceAmount;
	float mMaxSpeed;

public:
	Collector(MassAggregate* massAggregate, ObjectSpawner* spawner);
	virtual ~Collector();

	MassAggregate* GetMassAggregate() const;

	virtual void FixedUpdate(double t, std::vector<MassAggregate*> &addTo);
	void Push(const Vector3f &force);

	const Vector3f& GetPosition() const;
	const Vector3f& GetVelocity() const;
	int GetParticleCount() const;
};

#endif