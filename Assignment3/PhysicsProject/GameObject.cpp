#include "GameObject.h"
#include "MainApp.h"
#include "ModelManager.h"
#include "MaterialManager.h"
#include "RigidBody.h"
#include "DisplayObject3D.h"
#include "Material.h"
#include "CollisionSphere.h"
#include "PhysicsSystem.h"
#include "GraphicsSystem.h"
#include "ScaleFactor.h"
#include <iostream>

unsigned int GameObject::msIDS = 0;

//constructors
GameObject::GameObject()
	:mID(GameObject::msIDS)
{
	CommonInit("Cube", "", Vector3f::zero);
}
GameObject::GameObject(const std::string &modelKey)
	:mID(GameObject::msIDS)
{
	CommonInit(modelKey, "", Vector3f::zero);
}
GameObject::GameObject(const std::string &modelKey, const Vector3f &positionPhysics)
	:mID(GameObject::msIDS)
{
	CommonInit(modelKey, "", Vector3f(positionPhysics));
}
GameObject::GameObject(const std::string &modelKey, float x, float y, float z)
	:mID(GameObject::msIDS)
{
	CommonInit(modelKey, "", Vector3f(x, y, z));
}
GameObject::GameObject(const std::string &modelKey, const std::string &materialKey, const Vector3f &positionPhysics)
	:mID(GameObject::msIDS)
{
	CommonInit(modelKey, materialKey, Vector3f(positionPhysics));
}
GameObject::GameObject(const GameObject &rhs)
	:mID(GameObject::msIDS)
{
	CommonInit("Cube", "", Vector3f::zero);
}
GameObject::~GameObject()
{
	DeleteFromSystems();

	if (mAdded)
	{
		cerr << "ERROR: Object " << mID << " has been deleted without being removed from the graphics and physics system" << endl;
	}
}
void GameObject::CommonInit(const std::string &modelKey, const std::string &materialKey, const Vector3f &positionPhysics)
{
	//create the graphics object
	mGraphicsObject = new DisplayObject3D(GraphicsSystem::GetModel(modelKey));
	if (materialKey != "")
		mGraphicsObject->SetMaterial(GraphicsSystem::GetMaterial(materialKey));
	
	//create the physics object
	mPhysicsObject = new RigidBody();
	mPhysicsObject->SetPosition(positionPhysics);

	//create the collider object
	mCollider = new CollisionSphere();
	mCollider->mBody = mPhysicsObject;
	mCollider->mRadius = 1.0f;

	mAdded = false;

	AddToSystems();
	msIDS++;
}

//accessors
DisplayObject3D* GameObject::GetGraphicsObject() const
{
	return mGraphicsObject;
}

RigidBody* GameObject::GetPhysicsObject() const
{
	return mPhysicsObject;
}
/*
const Vector3f& GameObject::GetPhysicsPosition() const
{
	return mPhysicsObject->GetPosition();
}*/
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
void GameObject::AddToSystems()
{
	if (!mAdded)
	{
		GraphicsSystem::AddDisplayObject(mGraphicsObject);
		MainApp::GetPhysicsSystem()->AddRigidBody(mPhysicsObject);
		MainApp::GetPhysicsSystem()->AddNewCollider(mCollider);
		mAdded = true;
	}
}
void GameObject::DeleteFromSystems()
{
	if (mAdded)
	{
		GraphicsSystem::RemoveDisplayObject(mGraphicsObject);
		MainApp::GetPhysicsSystem()->RemoveRigidBody(mPhysicsObject);
		MainApp::GetPhysicsSystem()->DeleteCollider(mCollider);
		mAdded = false;
	}
}

void GameObject::LinkPositions() //link the position of the graphics object from the physics object
{
	//mGraphicsObject->getTransform()->SetPosition(mPhysicsObject->GetPosition() * DISTANCE_SCALE);
	//mGraphicsObject->getTransform()->SetTransformRT(mPhysicsObject->GetTransformMatrix());
	mGraphicsObject->getTransform()->SetTransformData(mPhysicsObject->GetPosition(), mPhysicsObject->GetOrientation(), Vector3f::one);
}
void GameObject::SetTag(const std::string &tag)
{
	mTag = tag;
}
void GameObject::SetMaterial(const std::string &material)
{
	mGraphicsObject->SetMaterial(GraphicsSystem::GetMaterial(material));
}

//cloning objects
GameObject* GameObject::Clone(const GameObject* other)
{
	GameObject *obj = new GameObject(*other);
	return obj;
}