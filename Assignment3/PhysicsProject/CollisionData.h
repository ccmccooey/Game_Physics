#ifndef _COLLISION_DATA_H
#define _COLLISION_DATA_H

class Contact;

struct CollisionData 
{
  Contact *contacts; // Pointer to fixed size array of contacts.
  int contactsGenerated; // Number of contacts presently used.
};

#endif