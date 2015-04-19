#ifndef _CONTACT_RESOLVER_H
#define _CONTACT_RESOLVER_H

class Contact;

class ContactResolver
{
	void ResolveContacts(Contact *contacts, unsigned numContacts, double duration);

	void PrepareContacts(Contact* contacts, unsigned int numContacts, float duration);

};

#endif