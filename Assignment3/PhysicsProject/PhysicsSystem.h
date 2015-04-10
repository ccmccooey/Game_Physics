#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H

#include "Vector3f.h"
#include <vector>
#include <queue>
#include <string>

class RigidBody;

class PhysicsSystem
{
private:
	std::vector<RigidBody*> mRigidBodies;
	std::queue<RigidBody*> mDeleteQueue;

public:
	PhysicsSystem();
	~PhysicsSystem();

	//accessors
	RigidBody* GetRigidBodyAt(int index) const;
	int IndexOf(RigidBody* rigidBody) const;
	bool ContainsRigidBody(RigidBody* rigidBody) const;
	bool ValidIndex(int index) const;

	//adding rigid bodies
	void AddRigidBody(RigidBody* rigidBody);
	void AddNewRigidBody(const Vector3f &position);

	//removing rigid bodies
	void RemoveRigidBody(RigidBody* rigidBody);
	void RemoveRigidBodyAt(int index);
	void RemoveAllRigidBodies();	

	//update the physics system
	void FixedUpdate(double t);

private:
	void FlushDeleteQueue();

};

#endif