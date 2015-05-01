#include "GameObject.h"
#include "MainApp.h"
#include "ModelManager.h"
#include "MaterialManager.h"
#include "RigidBody.h"
#include "DisplayObject3D.h"
#include "Material.h"
#include "CollisionSphere.h"
#include "CollisionBox.h"
#include "PhysicsSystem.h"
#include "GraphicsSystem.h"
#include "ScaleFactor.h"
#include <iostream>

unsigned int GameObject::msIDS = 0;

//constructors
GameObject::GameObject()
	:mID(GameObject::msIDS)
{
	CommonInit("Cube", "", Vector3f::zero, GameObjectShape::Sphere, 1.0f, 1.0f);
}
GameObject::GameObject(const std::string &modelKey)
	:mID(GameObject::msIDS)
{
	CommonInit(modelKey, "", Vector3f::zero, GameObjectShape::Sphere, 1.0f, 1.0f);
}
GameObject::GameObject(const std::string &modelKey, const std::string &materialKey, const Vector3f &positionPhysics, GameObjectShape shape, float mass, float size)
	:mID(GameObject::msIDS)
{
	CommonInit(modelKey, materialKey, Vector3f(positionPhysics), shape, mass, size);
}
GameObject::GameObject(const GameObject &rhs)
	:mID(GameObject::msIDS)
{
	CommonInit("Cube", "", Vector3f::zero, GameObjectShape::Sphere, 1.0f, 1.0f);
}
GameObject::~GameObject()
{
	DeleteFromSystems();

	if (mAdded)
	{
		cerr << "ERROR: Object " << mID << " has been deleted without being removed from the graphics and physics system" << endl;
	}
}
void GameObject::CommonInit(const std::string &modelKey, const std::string &materialKey, const Vector3f &positionPhysics, GameObjectShape shape, float mass, float size)
{
	//create the graphics object
	mGraphicsObject = new DisplayObject3D(GraphicsSystem::GetModel(modelKey));
	if (materialKey != "")
		mGraphicsObject->SetMaterial(GraphicsSystem::GetMaterial(materialKey));
	
	//create the physics object
	mPhysicsObject = new RigidBody();
	mPhysicsObject->SetPosition(positionPhysics);
	mPhysicsObject->SetMass(mass);

	//create the collider object
	if (shape == GameObjectShape::Sphere)
	{
		CollisionSphere* sphere = new CollisionSphere();
		sphere->mBody = mPhysicsObject;
		sphere->mRadius = size;
		
		Matrix33f tensor;
		float coeff = mPhysicsObject->GetMass()* size * size * 0.4f;
		tensor.SetInertiaTensorCoeffs(coeff, coeff, coeff);
		mPhysicsObject->SetIntertiaTensor(tensor);

		mCollider = static_cast<CollisionPrimitive*>(sphere);
	}
	else if (shape == GameObjectShape::Box)
	{
		CollisionBox* box = new CollisionBox();
		box->mBody = mPhysicsObject;
		box->mHalfSize = Vector3f::one * size;
		
		Matrix33f tensor;
		tensor.SetBlockInertiaTensor(box->mHalfSize, mPhysicsObject->GetMass());
		mPhysicsObject->SetIntertiaTensor(tensor);

		mCollider = static_cast<CollisionPrimitive*>(box);
	}
	else
	{
		std::cerr << "ERROR: Tried to create a gameobject with an invalid shape" << std::endl;
	}
	mPhysicsObject->CalculateDerivedData();
	LinkPositions();

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
	Vector3f scale = Vector3f::one;
	if (mCollider->IsSphere())
	{
		CollisionSphere* sphere = (CollisionSphere*)mCollider;
		scale = Vector3f::one * sphere->mRadius;
	}
	else if (mCollider->IsBox())
	{
		CollisionBox* box = (CollisionBox*)mCollider;
		scale = box->mHalfSize * 2.0f;
	}

	mGraphicsObject->getTransform()->SetTransformData(mPhysicsObject->GetPosition(), mPhysicsObject->GetOrientation(), scale);
}
void GameObject::SetTag(const std::string &tag)
{
	mTag = tag;
}
void GameObject::SetMaterial(const std::string &material)
{
	mGraphicsObject->SetMaterial(GraphicsSystem::GetMaterial(material));
}
void GameObject::SetStatic(bool isStatic)
{
	mPhysicsObject->SetStatic(isStatic);
}
void GameObject::SetScale(const Vector3f &scale)
{
	if (mCollider->IsBox())
	{
		CollisionBox* box = (CollisionBox*)mCollider;
		box->mHalfSize = scale;
	}
}

//cloning objects
GameObject* GameObject::Clone(const GameObject* other)
{
	GameObject *obj = new GameObject(*other);
	return obj;
}