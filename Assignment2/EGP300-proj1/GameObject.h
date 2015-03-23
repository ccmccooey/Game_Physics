#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "Vector3f.h"
#include <string>

class Model;
class Material;
class DisplayObject3D;
class Particle;
class ParticleSystem;
class DisplayObject3DManager;

class GameObject
{
protected:
	DisplayObject3D* mGraphicsObject;
	Particle* mPhysicsObject;

private:
	bool mAdded;
	std::string mTag;
	unsigned const int mID;

private:
	static unsigned int msIDS;

public:
	GameObject();
	GameObject(Model* model);
	GameObject(Model* model, const Vector3f &positionPhysics);
	GameObject(Model* model, float x, float y, float z);
	GameObject(Model* model, Material* material, const Vector3f &positionPhysics);
	GameObject(const GameObject &rhs);
	virtual ~GameObject();

	//accessors
	DisplayObject3D* GetGraphicsObject() const;
	Particle* GetPhysicsObject() const;
	bool AddedToSystems() const;
	const std::string& GetTag() const;
	unsigned int GetID() const;

	//setters
	void AddToSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem);
	void DeleteFromSystems(ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem);

	void LinkPositions(); //link the position of the graphics object from the physics object
	void SetTag(const std::string &tag);

private:
	void CommonInit();

public:
	static GameObject* Clone(const GameObject* other);
	static GameObject* CloneAndAdd(const GameObject* other, ParticleSystem* physicsSystem, DisplayObject3DManager* graphicsSystem);
};

#endif