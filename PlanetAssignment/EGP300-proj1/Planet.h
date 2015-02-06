#ifndef _PLANET_H
#define _PLANET_H

#include "RigidBody.h"
#include "DisplayObject3D.h"
#include <string>

class Planet :public DisplayObject3D
{
private:
	Rigidbody* mRigidBody;
	std::string mName;
	float mGravity;

public:
	Planet(Model* model);
	~Planet();

	void FixedUpdate(double t) const;
	void FinishUpdate() const;
	void SetName(const std::string &name);
	void SetGravity(float gravity);

	//accessors
	Rigidbody* GetRigidBody() const;
	std::string GetName() const;
	float GetGravity() const;
};


#endif