#ifndef _OBJECT_SPAWNER_H
#define _OBJECT_SPAWNER_H

#include "MassAggregateGeometry.h"
#include "Vector3f.h"
#include <list>

class MassAggregate;

class ObjectSpawner
{
private:
	int mMaxObjects; //the maximum number of uncollected objects allowed
	int mSpawnRate;
	int mSpawnCounter;
	int mObjectCount;
	Vector3f mSpawnCenterPoint;
	float mSpawnWidth;
	float mSpawnHeight;
	std::list<MassAggregate*> mObjects; //Objects that can be collected by the player

public:
	ObjectSpawner();
	ObjectSpawner(int spawnRate, int maxObjectsAllowed, const Vector3f &spawnCenter, float spawnWidth, float spawnHeight);
	~ObjectSpawner();

	//accessors
	int GetMaxObjects() const;
	int GetSpawnRate() const;

	//spawning objects called each frame
	void FixedUpdate(double t);
	void LinkPosition();

	void SpawnObject(const Vector3f &position, MassAggregateGeometry type);

	void RemoveObject(MassAggregate* obj); //remove the object from the spawner

	MassAggregate* CheckForObjectInRange(const Vector3f &position, float radius) const; //checks to see if there is an object within a radius and returns that object

private:
	void Initialize();
};

#endif