#ifndef _PHYSICS_SYSTEM_H
#define _PHYSICS_SYSTEM_H

#include "Vector3f.h"
#include <vector>
#include <queue>
#include <string>

class CollisionPrimitive;
class CollisionPlane;
class ContactResolver;
class ContactGenerator;
class ForceGenerator;
class RigidBody;
class Contact;
struct CollisionData;

class PhysicsSystem
{
private:
	std::vector<RigidBody*> mRigidBodies;
	std::queue<RigidBody*> mDeleteQueue;
	std::vector<ForceGenerator*> mRegistry;
	std::vector<ContactGenerator*> mContactGenerators;
	std::vector<CollisionPrimitive*> mColliders;
	
	ContactResolver* mContactResolver;
	CollisionData* mCollisionData;

	static unsigned long msTotalPhysicsUpdates;

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
	RigidBody* AddNewRigidBody(const Vector3f &position);
	void AddForceGenerator(ForceGenerator* forceGenerator);

	//removing rigid bodies, contacts, and force generators
	void RemoveRigidBody(RigidBody* rigidBody);
	void RemoveRigidBodyAt(int index);
	void RemoveAllRigidBodies();
	void RemoveForceGenerator(ForceGenerator* forceGenerator);

	//adding and removing colliders
	void AddNewCollider(CollisionPrimitive* collider);
	void DeleteCollider(CollisionPrimitive* collider);
	void DeleteAllColliders();

	//update the physics system
	void FixedUpdate(double t);

private:
	unsigned int GenerateContacts(); //returns the number of contacts generated
	void ProcessContacts(double t, unsigned int usedContacts);

	

	void FlushDeleteQueue();

};

#endif