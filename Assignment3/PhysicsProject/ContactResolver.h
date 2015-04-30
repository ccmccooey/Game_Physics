#ifndef _CONTACT_RESOLVER_H
#define _CONTACT_RESOLVER_H

class VisualContactSystem;
class Contact;

class ContactResolver
{
private:
	unsigned int mPositionIterationsUsed;
	unsigned int mVelocityIterationsUsed;

	unsigned int mPositionIterations;
	unsigned int mVelocityIterations;

	float mVelocityEpsilon;
	float mPositionEpsilon;

	VisualContactSystem* mVisualContactSystem;

public:
	ContactResolver();
	~ContactResolver();


	void SetIterations(unsigned int velocityIterations, unsigned int positionIterations);
    void SetIterations(unsigned int iterations); //applies to velocity and position
    void SetEpsilon(float velocityEpsilon, float positionEpsilon);

	void ResolveContacts(Contact *contacts, unsigned int numContacts, double duration);

	void PrepareContacts(Contact* contacts, unsigned int numContacts, float duration);

	void ResolvePositions(Contact *contact, unsigned int numContacts, float duration);
	void ResolveVelocities(Contact *contact, unsigned int numContacts, float duration);
};

#endif