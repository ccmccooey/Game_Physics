#ifndef _COLLIDER_MANAGER_H
#define _COLLIDER_MANAGER_H

#include <vector>

class CollisionData;

#include "CollisionPlane.h"
#include "CollisionSphere.h"
#include "CollisionBox.h"


class ColliderManager
{
private:
	std::vector<CollisionPlane*> mPlanes;
	std::vector<CollisionPlane*> mHalfspaces;
	std::vector<CollisionSphere*> mSpheres;
	std::vector<CollisionBox*> mBoxes;

public:
	ColliderManager();
	~ColliderManager();

	void GenerateCollisions(CollisionData* data);

	void AddCollisionSphere(CollisionSphere* sphere);
	void AddCollisionBox(CollisionBox* box);
	void AddCollisionPlane(CollisionPlane* plane);
	void AddCollisionHalfspace(CollisionPlane* halfspace);

	void RemoveCollisionPrimitive(CollisionPrimitive* collider);
	void RemoveAllCollisionPrimitives();

private:

};

#endif