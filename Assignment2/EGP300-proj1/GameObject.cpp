#include "GameObject.h"
#include "Particle.h"
#include "DisplayObject3D.h"
#include "Material.h"
#include "ParticleSystem.h"
#include "DisplayObject3DManager.h"
#include "ScaleFactor.h"
#include <iostream>

unsigned int GameObject::msIDS = 0;

//constructors
GameObject::GameObject()
	:mID(GameObject::msIDS)
{
	CommonInit();
}
GameObject::GameObject(Model* model)
	:mID(GameObject::msIDS)
{
	CommonInit();
	mGraphicsObject = new DisplayObject3D(model);
	mPhysicsObject = new Particle(mGraphicsObject->getTransform());	
}
GameObject::GameObject(Model* model, const Vector3f &positionPhysics)
	:mID(GameObject::msIDS)
{
	CommonInit();
	mGraphicsObject = new DisplayObject3D(model);
	mPhysicsObject = new Particle(mGraphicsObject->getTransform());
	mPhysicsObject->SetPosition(positionPhysics);
}
GameObject::GameObject(Model* model, float x, float y, float z)
	:mID(GameObject::msIDS)
{
	CommonInit();
	mGraphicsObject = new DisplayObject3D(model);
	mPhysicsObject = new Particle(mGraphicsObject->getTransform());
	mPhysicsObject->SetPosition(x, y, z);
}
GameObject::GameObject(Model* model, Material* material, const Vector3f &positionPhysics)
	:mID(GameObject::msIDS)
{
	CommonInit();
	mGraphicsObject = new DisplayObject3D(model);
	mGraphicsObject->SetMaterial(material);
	mPhysicsObject = new Particle(mGraphicsObject->getTransform());
	mPhysicsObject->SetPosition(positionPhysics);
}
GameObject::GameObject(const GameObject &rhs)
	:mID(GameObject::msIDS)
{
	CommonInit();
	mGraphicsObject = new DisplayObject3D(*rhs.mGraphicsObject);
	mPhysicsObject = new Particle(*rhs.mPhysicsObject);
}
GameObject::~GameObject()
{
	//delete mGraphicsObject;
	//delete mPhysicsObject;

	if (mAdded)
	{
		cerr << "ERROR: Object " << mID << " has been deleted without being removed from the graphics and physics system" << endl;
	}
}
void GameObject::CommonInit()
{
	msIDS++;
	mAdded = false;
}

//accessors
DisplayObject3D* GameObject::GetGraphicsObject() const
{
	return mGraphicsObject;
}
Particle* GameObject::GetPhysicsObject() const
{
	return mPhysicsObject;
}
bool GameObject::AddedToSystems() const
{
	return mAdded;
}
const std::string& GameObject::GetTag() const
{
	return mTag;
}
unsigned int GameObject::GetID() const
{
	return mID;
}

//setters
void GameObject::AddToSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem)
{
	if (!mAdded)
	{
		graphicsSystem->AddObject(mGraphicsObject);
		physicsSystem->AddParticle(mPhysicsObject);
		mAdded = true;
	}
}
void GameObject::DeleteFromSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem)
{
	if (mAdded)
	{
		graphicsSystem->RemoveObject(mGraphicsObject);
		physicsSystem->RemoveFromSystem(mPhysicsObject);
		mAdded = false;
	}
}

void GameObject::LinkPositions() //link the position of the graphics object from the physics object
{
	mGraphicsObject->getTransform()->SetPosition(mPhysicsObject->GetPosition() * DISTANCE_SCALE);
}
void GameObject::SetTag(const std::string &tag)
{
	mTag = tag;
}

//cloning objects
GameObject* GameObject::Clone(const GameObject* other)
{
	GameObject *obj = new GameObject(*other);
	return obj;
}
GameObject* GameObject::CloneAndAdd(const GameObject* other, ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem)
{
	GameObject *obj = new GameObject(*other);
	obj->AddToSystems(physicsSystem, graphicsSystem);
	return obj;
}