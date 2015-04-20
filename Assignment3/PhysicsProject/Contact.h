#ifndef _CONTACT_H
#define _CONTACT_H

class RigidBody;

#include "Vector3f.h"
#include "Matrix33f.h"

class Contact 
{
public:
	// Bodies involved in contact. Second may be null.
	RigidBody *mBodies[2];

	Vector3f mContactPoint;
	Vector3f mContactNormal;

	// Penetration depth along contact normal.
	float mPenetrationDepth;

	// Provided by contact generator - based on bodies in collision.
	float mRestitution;
	float mFriction;

protected:
	Matrix33f mContactToWorld;
	Vector3f mContactVelocity;
	float mDesiredDeltaVelocity;
	Vector3f mRelativeContactPosition[2];

public:
	Contact();
	Contact(const Contact &rhs);
	~Contact();

	void CalculateContactBasis();
	void CalculateInternals(double duration);
	Vector3f CalculateLocalVelocity(unsigned bodyIndex, float duration);
	void CalculateDesiredDeltaVelocity(float duration);
};

#endif
