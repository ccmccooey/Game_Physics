#ifndef _PLANET_H
#define _PLANET_H

#include "RigidBody.h"
#include "DisplayObject3D.h"
#include "TextField.h"
#include <string>

class Planet :public DisplayObject3D
{
private:
	Rigidbody* mRigidBody;
	TextField* mLabel;
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
	TextField* GetTextField() const;

	void DrawAll(DrawData* drawData);
};


#endif