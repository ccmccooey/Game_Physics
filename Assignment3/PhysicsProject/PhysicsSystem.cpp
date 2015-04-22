#include "PhysicsSystem.h"
#include "RigidBody.h"

using namespace std;

PhysicsSystem::PhysicsSystem()
{

}
PhysicsSystem::~PhysicsSystem()
{
	RemoveAllRigidBodies();
	FlushDeleteQueue();
}

//accessors
RigidBody* PhysicsSystem::GetRigidBodyAt(int index) const
{
	RigidBody* rb = nullptr;
	if (ValidIndex(index))
	{
		rb = mRigidBodies[index];
	}
	return rb;
}
int PhysicsSystem::IndexOf(RigidBody* rigidBody) const
{
	int index = -1;
	unsigned int size = mRigidBodies.size();
	for (unsigned int i = 0; i < size; i++)
	{
		if (mRigidBodies[i] == rigidBody)
		{
			index = i;
			break;
		}
	}
	return index;
}
bool PhysicsSystem::ContainsRigidBody(RigidBody* rigidBody) const
{
	bool found = false;
	unsigned int size = mRigidBodies.size();
	for (unsigned int i = 0; i < size; i++)
	{
		if (mRigidBodies[i] == rigidBody)
		{
			found = true;
			break;
		}
	}
	return found;
}
bool PhysicsSystem::ValidIndex(int index) const
{
	return index >= 0 && index < (int)mRigidBodies.size();
}

//adding rigid bodies
RigidBody* PhysicsSystem::AddRigidBody(RigidBody* rigidBody)
{	
	mRigidBodies.push_back(rigidBody);	
}
void PhysicsSystem::AddNewRigidBody(const Vector3f &position)
{
	RigidBody* rb = new RigidBody(1.0f, position);
}

//removing rigid bodies
void PhysicsSystem::RemoveRigidBody(RigidBody* rigidBody)
{
	vector<RigidBody*>::const_iterator iter = mRigidBodies.begin();
	vector<RigidBody*>::const_iterator back = mRigidBodies.end();

	while (iter != back)
	{
		if ((*iter) == rigidBody)
		{
			mDeleteQueue.push(*iter);
			mRigidBodies.erase(iter);
			break;
		}
		++iter;
	}
}
void PhysicsSystem::RemoveRigidBodyAt(int index)
{
	if (ValidIndex(index))
	{
		mDeleteQueue.push(mRigidBodies[index]);
		mRigidBodies.erase(mRigidBodies.begin() + index);
	}
}
void PhysicsSystem::RemoveAllRigidBodies()
{
	unsigned int size = mRigidBodies.size();
	for (unsigned int i = 0; i < size; i++)
	{
		mDeleteQueue.push(mRigidBodies[i]);
	}
}

//update the physics system
void PhysicsSystem::FixedUpdate(double t)
{
	unsigned int size = mRigidBodies.size();
	for (unsigned int i = 0; i < size; i++)
	{
		//update here
	}
	FlushDeleteQueue();
}

void PhysicsSystem::FlushDeleteQueue()
{
	RigidBody* rb;
	while (mDeleteQueue.size() > 0)
	{
		rb = mDeleteQueue.front();
		delete rb;
		mDeleteQueue.pop();
	}
}