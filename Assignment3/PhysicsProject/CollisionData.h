#ifndef _COLLISION_DATA_H
#define _COLLISION_DATA_H

class Contact;

struct CollisionData 
{
	Contact *contactArray;

	/** Holds the contact array to write into. */
	Contact *contacts;

	/** Holds the maximum number of contacts the array can take. */
	int mContactsLeft;

	/** Holds the number of contacts found so far. */
	unsigned int mContactCount;

	/** Holds the friction value to write into any collisions. */
	float mGlobalFriction;

	/** Holds the restitution value to write into any collisions. */
	float mGlobalRestitution;

	/**
	* Holds the collision tolerance, even uncolliding objects this
	* close should have collisions generated.
	*/
	float mTolerance;
};

#endif