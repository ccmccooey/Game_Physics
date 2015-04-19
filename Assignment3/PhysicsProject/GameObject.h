#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "Vector3f.h"
#include <string>

class DisplayObject3D;
class RigidBody;

class GameObject
{
protected:
	DisplayObject3D* mGraphicsObject;
	RigidBody* mPhysicsObject;

private:
	bool mAdded;
	std::string mTag;
	unsigned const int mID;

private:
	static unsigned int msIDS;

public:
	GameObject();
	GameObject(const std::string &modelKey);
	GameObject(const std::string &modelKey, const Vector3f &positionPhysics);
	GameObject(const std::string &modelKey, float x, float y, float z);
	GameObject(const std::string &modelKey, const std::string &materialKey, const Vector3f &positionPhysics);
	GameObject(const GameObject &rhs);
	virtual ~GameObject();

	//accessors
	DisplayObject3D* GetGraphicsObject() const;
	RigidBody* GetPhysicsObject() const;
	const Vector3f& GetPhysicsPosition() const;
	bool AddedToSystems() const;
	const std::string& GetTag() const;
	unsigned int GetID() const;

	//setters
	void AddToSystems();
	void DeleteFromSystems();

	void LinkPositions(); //link the position of the graphics object from the physics object
	void SetTag(const std::string &tag);
	void SetMaterial(const std::string &material);

private:
	void CommonInit(const std::string &modelKey, const std::string &materialKey, const Vector3f &positionPhysics);

public:
	static GameObject* Clone(const GameObject* other);
};

#endif