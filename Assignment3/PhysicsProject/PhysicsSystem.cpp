#include "PhysicsSystem.h"
#include "RigidBody.h"
#include "ForceGenerator.h"
#include "ContactResolver.h"
#include "CollisionSphere.h"
#include "CollisionPlane.h"
#include "CollisionDetector.h"
#include "CollisionData.h"

#define MAX_CONTACTS 100

using namespace std;

typedef vector<CollisionPrimitive*>::iterator CollidersIter;
typedef vector<CollisionPrimitive*>::const_iterator CollidersConstIter;

unsigned long PhysicsSystem::msTotalPhysicsUpdates = 0;

//constructor
PhysicsSystem::PhysicsSystem()
{
	mColliders = vector<CollisionPrimitive*>();
	mRigidBodies = vector<RigidBody*>();
	mRegistry = vector<ForceGenerator*>();
	mContactGenerators = vector<ContactGenerator*>();
	mDeleteQueue = queue<RigidBody*>();
	mContactResolver = new ContactResolver();

	mCollisionData = new CollisionData(MAX_CONTACTS);
	mGround = new CollisionPlane(Vector3f::unitY, -30.0f);
}
PhysicsSystem::~PhysicsSystem()
{
	RemoveAllRigidBodies();
	FlushDeleteQueue();

	delete mContactResolver;
	delete mCollisionData;
	delete mGround;
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
void PhysicsSystem::AddRigidBody(RigidBody* rigidBody)
{	
	mRigidBodies.push_back(rigidBody);	
}
RigidBody* PhysicsSystem::AddNewRigidBody(const Vector3f &position)
{
	RigidBody* rb = new RigidBody(1.0f, position);
	return rb;
}

//adding force generators
void PhysicsSystem::AddForceGenerator(ForceGenerator* forceGenerator)
{
	mRegistry.push_back(forceGenerator);
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

//adding and removing colliders
void PhysicsSystem::AddNewCollider(CollisionPrimitive* collider)
{	
	mColliders.push_back(collider);
}
void PhysicsSystem::DeleteCollider(CollisionPrimitive* collider)
{
	CollidersConstIter iter = mColliders.begin();	
	CollidersConstIter back = mColliders.end();

	while (iter != back)
	{
		if ((*iter) == collider)
		{
			delete (*iter);
			mColliders.erase(iter);
			break;
		}
		++iter;
	}
}
void PhysicsSystem::DeleteAllColliders()
{
	unsigned int size = mColliders.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete mColliders[i];
	}
	mColliders.clear();
}

//generate contacts
unsigned int PhysicsSystem::GenerateContacts()
{
	unsigned int i, j;
	unsigned int contactsMade = 0;

	unsigned int size = mColliders.size();
	for (i = 0; i < size; i++)
	{
		contactsMade += CollisionDetector::SphereAndHalfSpace(*((CollisionSphere*)mColliders[i]) , *mGround, mCollisionData);
		for (j = i; j < size; j++)
		{	
			//avoid collision detecting colliders with themselves
			if (i != j) 
			{
				contactsMade += CollisionDetector::SphereAndSphere(*((CollisionSphere*)mColliders[i]), *((CollisionSphere*)mColliders[j]), mCollisionData); //Horrible!
			}
		}
	}
	return contactsMade;
}

//Process contacts
void PhysicsSystem::ProcessContacts(double t, unsigned int usedContacts)
{
	//resolver.setIterations(usedContacts * 4);
    //resolver.resolveContacts(contacts, usedContacts, duration);

	mContactResolver->SetIterations(usedContacts * 4);
	mContactResolver->ResolveContacts(mCollisionData->mContactArray, usedContacts, t);
}

//update the physics system
void PhysicsSystem::FixedUpdate(double t)
{
	//declare the sizes and iteration variables
	unsigned int rbSize = mRigidBodies.size();
	unsigned int registrySize = mRegistry.size();
	unsigned int i;
	unsigned int j;

	//apply all the forces
	for (i = 0; i < rbSize; i++)
	{
		for (j = 0; j < registrySize; j++)
		{
			mRegistry[j]->ApplyForce(mRigidBodies[i], t);
		}
	}

	//update the rigid bodies
	for (i = 0; i < rbSize; i++)
	{
		mRigidBodies[i]->FixedUpdate(t);
	}

	//generate contacts
	unsigned int usedContacts = GenerateContacts();

	//process contats
	ProcessContacts(t, usedContacts);

	//delete removed rigid bodies from memory
	FlushDeleteQueue();

	//update the physics frame counter
	msTotalPhysicsUpdates++;
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