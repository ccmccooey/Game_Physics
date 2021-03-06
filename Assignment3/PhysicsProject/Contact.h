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
	bool mNull; //I use this for debugging

protected:
	Matrix33f mContactToWorld;
	Vector3f mContactVelocity;
	float mDesiredDeltaVelocity;
	Vector3f mRelativeContactPosition[2];

public:
	Contact();
	Contact(const Contact &rhs); 
	~Contact();

	//accessors
	const Vector3f& GetRelativeContactPosition(unsigned int index) const;
	const Matrix33f& GetContactToWorld() const;
	float GetDesiredDeltaVelocity() const;
	const Vector3f& GetContactVelocity() const;
	
	//basic settors
	void AddContactVelocity(const Vector3f &contactVelocity);

	//calculation functions
	void CalculateContactBasis();
	void CalculateInternals(double duration);
	Vector3f CalculateLocalVelocity(unsigned int bodyIndex, double duration);
	void CalculateDesiredDeltaVelocity(double duration);
	void SetBodyData(RigidBody* actorA, RigidBody* actorB, float friction, float restitution);
	void ApplyPositionChange(Vector3f linearChange[2], Vector3f angularChange[2], float penetrationDepth);
	void ApplyVelocityChange(Vector3f velocityChange[2], Vector3f rotationChange[2]);

private:
	inline Vector3f CalculateFrictionlessImpulse(Matrix33f* inverseInertiaTensor);
	inline Vector3f CalculateFrictionImpulse(Matrix33f* inverseInertiaTensor);
};

#endif
