#include "ObjectSpawner.h"
#include "MassAggregate.h"
#include "Particle.h"
#include "Random.h"

typedef std::list<MassAggregate*>::iterator listIter;
typedef std::list<MassAggregate*>::const_iterator listConstIter;

using namespace std;

ObjectSpawner::ObjectSpawner()
{
	mSpawnRate = 250;
	mMaxObjects = 10;
	mSpawnCenterPoint = Vector3f(0.0f, 20.0f, 0.0f);;
	mSpawnWidth = 15.0f;
	mSpawnHeight = 15.0f;
	Initialize();
}
ObjectSpawner::ObjectSpawner(int spawnRate, int maxObjectsAllowed, const Vector3f &spawnCenter, float spawnWidth, float spawnHeight)
{
	mSpawnRate = spawnRate;
	mMaxObjects = maxObjectsAllowed;
	mSpawnCenterPoint = spawnCenter;
	mSpawnWidth = spawnWidth;
	mSpawnHeight = spawnHeight;
	Initialize();
}
ObjectSpawner::~ObjectSpawner()
{
	MassAggregate* obj;
	while (mObjects.size() > 0)
	{
		obj = mObjects.front();
		delete obj;
		mObjects.pop_front();
	}
}

//true for both contructors
void ObjectSpawner::Initialize()
{
	mObjectCount = 0;
	mSpawnCounter = 0;
	mObjects = list<MassAggregate*>();
}

//accessors
int ObjectSpawner::GetMaxObjects() const
{
	return mMaxObjects;
}
int ObjectSpawner::GetSpawnRate() const
{
	return mSpawnRate;
}

//spawning objects called each frame
void ObjectSpawner::FixedUpdate(double t)
{
	mSpawnCounter++;
	if (mSpawnCounter >= mSpawnRate)
	{
		mSpawnCounter = 0;

		//create a mass aggregate
		
	}
}
void ObjectSpawner::LinkPosition()
{
	listConstIter iter = mObjects.begin();
	listConstIter listEnd = mObjects.end();

	
	while (iter != listEnd)
	{
		(*iter)->LinkPositions();
		++iter;
	}
}
void ObjectSpawner::SpawnObject(const Vector3f &position, MassAggregateGeometry type)
{
	MassAggregate* ma = new MassAggregate(type, position);
	mObjects.push_back(ma);
}

void ObjectSpawner::RemoveObject(MassAggregate* obj) //remove the object from the spawner
{
	listConstIter iter = mObjects.begin();
	listConstIter listEnd = mObjects.end();

	while (iter != listEnd)
	{
		if (obj == (*iter))
		{
			mObjects.remove(obj);
			break;
		}
		++iter;
	}
}

MassAggregate* ObjectSpawner::CheckForObjectInRange(const Vector3f &position, float radius) const //checks to see if there is an object within a radius and returns that object
{
	listConstIter iter = mObjects.begin();
	listConstIter listEnd = mObjects.end();

	MassAggregate* obj = nullptr;
	float radiusSquared = radius * radius;

	while (iter != listEnd)
	{
		if (Vector3f::DistanceSquared(position, (*iter)->GetParticleAt(0)->GetPosition()) <= radiusSquared)
		{
			obj = (*iter);
			break;
		}
		++iter;
	}

	return obj;
}