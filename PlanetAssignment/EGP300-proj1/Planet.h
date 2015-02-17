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
	Rigidbody* mOriginalData;

public:
	Planet(Model* model);
	~Planet();

	void FixedUpdate(double t) const;
	void FinishUpdate() const;
	void SetName(const std::string &name);
	void SetGravity(float gravity);
	void Reset();
	void SetOriginalDataToCurrent();

	//accessors
	Rigidbody* GetRigidBody() const;
	std::string GetName() const;
	float GetGravity() const;
	TextField* GetTextField() const;
	void GetDebugInfo(std::string &out) const;

	void DrawAll(DrawData* drawData);
};


#endif