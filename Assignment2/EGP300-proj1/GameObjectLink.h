#ifndef _GAME_OBJECT_LINK_H
#define _GAME_OBJECT_LINK_H

class ParticleSystem;
class DisplayObject3DManager;
class ParticleLink;
class DisplayObject3D;
class Model;

class GameObjectLink
{
private:
	DisplayObject3D* mGraphicsObject;
	ParticleLink* mPhysicsLink;
	bool mAdded;
	const unsigned int mID;
	static unsigned int msIDs;

public:
	GameObjectLink(Model* model, ParticleLink *link);
	GameObjectLink(const GameObjectLink &rhs);
	~GameObjectLink();

	ParticleLink* GetLink() const;
	DisplayObject3D *GetGraphicsObject() const;

	void LinkPositions(); //link the position of the graphics object from the physics object
};

#endif