#ifndef _GROUND_H
#define _GROUND_H

#include <string>

class DisplayObject3D;
class CollisionPlane;

class Ground
{
private:
	DisplayObject3D* mDisplayObject;
	CollisionPlane* mCollisionPlane;
	float mElevation;

public:
	Ground();
	~Ground();

	void SetMaterial(const std::string &name);
};

#endif