#ifndef _CONTACT_RESOLVER_H
#define _CONTACT_RESOLVER_H

class Contact;

class ContactResolver
{
private:
	unsigned int mPositionIterationsUsed;
	unsigned int mVelocityIterationsUsed;

	unsigned int mPositionIterations;
	unsigned int mVeloictyIterations;

	float mVelocityEpsilon;
	float mPositionEpsilon;

public:
	ContactResolver();
	~ContactResolver();

	void ResolveContacts(Contact *contacts, unsigned int numContacts, double duration);

	void PrepareContacts(Contact* contacts, unsigned int numContacts, float duration);

	void ResolvePositions(Contact *contact, unsigned int numContacts, float duration);
	void ResolveVelocities(Contact *contact, unsigned int numContacts, float duration);
};

#endif