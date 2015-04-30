#ifndef _VISUAL_CONTACT_SYSTEM_H
#define _VISUAL_CONTACT_SYSTEM_H

#include <list>

class DisplayObject3D;

class VisualContactSystem
{
private:
	struct ListNode
	{
		unsigned int mDuration;
		DisplayObject3D* mObject;

		ListNode(unsigned int duration, DisplayObject3D* object);
		~ListNode();
	};
	typedef std::list<VisualContactSystem::ListNode*>::const_iterator ListConstIter;

private:
	std::list<ListNode*> mVisualContacts;

public:
	VisualContactSystem();
	~VisualContactSystem();

	void CreateContact(float x, float y, float z);

	void Update(double t);

	void RemoveAllContacts();
};

#endif