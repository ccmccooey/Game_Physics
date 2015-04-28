#ifndef _COLLISION_DATA_H
#define _COLLISION_DATA_H

class Contact;

struct CollisionData 
{
public:
	CollisionData(unsigned int capacity);
	~CollisionData();

	Contact *mContactArray;

	/** Holds the contact array to write into. */
	Contact *mContacts;

	/** Holds the maximum number of contacts the array can take. */
	int mContactsLeft;

	/** Holds the number of contacts found so far. */
	unsigned int mContactCount;

	unsigned int mMaxContacts;

	/** Holds the friction value to write into any collisions. */
	float mGlobalFriction;

	/** Holds the restitution value to write into any collisions. */
	float mGlobalRestitution;

	/**
	* Holds the collision tolerance, even uncolliding objects this
	* close should have collisions generated.
	*/
	float mTolerance;

public:
	void AddContacts(unsigned int count); //adds a specified number of contacts
	void AddContact(); //adds a single contact

	void ResetContacts();
};

#endif