#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H

#include "Vector3f.h"
#include <vector>
#include <queue>
#include <string>

class ForceGenerator;
class RigidBody;
class Contact;

class PhysicsSystem
{
private:
	std::vector<RigidBody*> mRigidBodies;
	std::queue<RigidBody*> mDeleteQueue;
	std::vector<ForceGenerator*> mRegistry;
	std::vector<Contact*> mActiveContacts;

public:
	PhysicsSystem();
	~PhysicsSystem();

	//accessors
	RigidBody* GetRigidBodyAt(int index) const;
	int IndexOf(RigidBody* rigidBody) const;
	bool ContainsRigidBody(RigidBody* rigidBody) const;
	bool ValidIndex(int index) const;

	//adding rigid bodies, contacts, and force generators
	void AddRigidBody(RigidBody* rigidBody);
	void AddNewRigidBody(const Vector3f &position);
	void AddForceGenerator(ForceGenerator* forceGenerator);
	void AddContact(Contact* contact);

	//removing rigid bodies, contacts, and force generators
	void RemoveRigidBody(RigidBody* rigidBody);
	void RemoveRigidBodyAt(int index);
	void RemoveAllRigidBodies();
	void RemoveForceGenerator(ForceGenerator* forceGenerator);
	void RemoveContact(Contact* contact);

	//update the physics system
	void FixedUpdate(double t);

private:
	void FlushDeleteQueue();

};

#endif