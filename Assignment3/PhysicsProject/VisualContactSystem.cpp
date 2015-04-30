#include "VisualContactSystem.h"
#include "DisplayObject3D.h"
#include "GraphicsSystem.h"

#define CONTACT_STEPS 100
#define CONTACT_SCALE 1.25f
#define CONTACT_MAX_COUNT 20

VisualContactSystem::VisualContactSystem()
{
	mVisualContacts = std::list<ListNode*>();
}
VisualContactSystem::~VisualContactSystem()
{
	RemoveAllContacts();
}

VisualContactSystem::ListNode::ListNode(unsigned int duration, DisplayObject3D* object)
{
	mDuration = duration;
	mObject = object;
}
VisualContactSystem::ListNode::~ListNode()
{
	
}


void VisualContactSystem::CreateContact(float x, float y, float z)
{
	if (mVisualContacts.size() < CONTACT_MAX_COUNT)
	{
		DisplayObject3D* contact = new DisplayObject3D(GraphicsSystem::GetModel("Cube"));
		contact->SetMaterial(GraphicsSystem::GetMaterial("ContactDisplay"));
		contact->getTransform()->SetPosition(x, y, z);
		contact->getTransform()->SetScale(CONTACT_SCALE);
		GraphicsSystem::AddDisplayObject(contact);

		ListNode* node = new ListNode(0, contact);
		mVisualContacts.push_back(node);
	}
}

void VisualContactSystem::Update(double t)
{
	ListConstIter iter = mVisualContacts.begin();
	ListConstIter back = mVisualContacts.end();

	ListNode* node;

	while (iter != back)
	{
		node = *iter;
		node->mDuration++;
		if (node->mDuration >= CONTACT_STEPS)
		{
			GraphicsSystem::RemoveDisplayObject(node->mObject);
			delete node;		
			mVisualContacts.erase(iter);
			break;
		}

		++iter;
	}
}

void VisualContactSystem::RemoveAllContacts()
{
	ListNode* node;
	while (!mVisualContacts.empty())
	{
		node = mVisualContacts.front();
		GraphicsSystem::RemoveDisplayObject(node->mObject);
		delete node;
		mVisualContacts.pop_front();
	}
}