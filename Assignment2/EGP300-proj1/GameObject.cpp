#include "GameObject.h"
#include "MainApp.h"
#include "ModelManager.h"
#include "MaterialManager.h"
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
	mGraphicsObject = new DisplayObject3D(MainApp::GetModelManager()->FindModel(modelKey));
	if (materialKey != "")
		mGraphicsObject->SetMaterial(MainApp::GetMaterialManager()->FindMaterial(materialKey));
	mPhysicsObject = new Particle(mGraphicsObject->getTransform());
	mPhysicsObject->SetPosition(positionPhysics);
	AddToSystems();

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
const Vector3f& GameObject::GetPhysicsPosition() const
{
	return mPhysicsObject->GetPosition();
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
void GameObject::AddToSystems()
{
	if (!mAdded)
	{
		MainApp::GetGraphicsSystem()->AddObject(mGraphicsObject);
		MainApp::GetPhysicsSystem()->AddParticle(mPhysicsObject);
		mAdded = true;
	}
}
void GameObject::DeleteFromSystems()
{
	if (mAdded)
	{
		MainApp::GetGraphicsSystem()->RemoveObject(mGraphicsObject);
		MainApp::GetPhysicsSystem()->RemoveFromSystem(mPhysicsObject);
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