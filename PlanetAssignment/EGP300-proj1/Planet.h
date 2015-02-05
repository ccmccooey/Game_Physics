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

public:
	Planet(Model* model);
	~Planet();

	void FixedUpdate(double t);
	void SetName(const std::string &name);

	//accessors
	Rigidbody* GetRigidBody() const;
	std::string GetName() const;
};


#endif