#include "DisplayObject3DManager.h"
#include "DisplayObject3D.h"
#include "Model.h"
#include "Material.h"
#include "DrawData.h"

typedef std::forward_list<DisplayObject3D*>::const_iterator ListConstIter;
typedef std::forward_list<DisplayObject3D*>::iterator ListIter;

using namespace std;

DisplayObject3DManager::DisplayObject3DManager()
{
	mObjects = forward_list<DisplayObject3D*>();
	mDeleteQueue = queue<DisplayObject3D*>();
	mObjectsCount = 0;
}
DisplayObject3DManager::~DisplayObject3DManager()
{
	RemoveAllObjects();
	FlushDeleteQueue();
}

//accessors
int DisplayObject3DManager::GetObjectCount() const
{
	return mObjectsCount;
}
bool DisplayObject3DManager::Contains(DisplayObject3D* object) const
{
	bool found = false;

	ListConstIter iter = mObjects.begin();
	ListConstIter back = mObjects.end();

	while (iter != back)
	{
		if (*iter == object)
		{
			found = true;
			break;
		}
		++iter;
	}
	return found;
}

//adding and removing objects
void DisplayObject3DManager::AddObject(DisplayObject3D* object)
{
	mObjects.push_front(object);
}
void DisplayObject3DManager::AddObject(Model* model)
{
	mObjects.push_front(new DisplayObject3D(model));
}
void DisplayObject3DManager::AddObject(Model* model, Material* material)
{
	DisplayObject3D* obj = new DisplayObject3D(model);
	obj->SetMaterial(material);
	mObjects.push_front(obj);
}
void DisplayObject3DManager::AddObjectMany(DisplayObject3D** objects, int count)
{
	for (int i = 0; i < count; i++)
	{
		this->AddObject(objects[i]);
	}
}
void DisplayObject3DManager::RemoveObject(DisplayObject3D* object)
{
	ListConstIter iter = mObjects.begin();
	ListConstIter iterPrevious = mObjects.before_begin();

	while (iter != mObjects.end())
	{
		if (*iter == object)
		{
			mObjects.push_front(object);
			mObjects.erase_after(iterPrevious);
			break;
		}
		++iter;
		++iterPrevious;
	}
}
void DisplayObject3DManager::RemoveAllObjects()
{
	DisplayObject3D* obj;
	while (!mObjects.empty())
	{
		obj = mObjects.front();
		mDeleteQueue.push(obj);
		mObjects.pop_front();
	}
}

void DisplayObject3DManager::Draw(DrawData* data)
{
	ListConstIter iter = mObjects.begin();
	ListConstIter back = mObjects.end();

	while (iter != back)
	{
		(*iter)->Draw(data);
		++iter;
	}
	FlushDeleteQueue();
}

void DisplayObject3DManager::FlushDeleteQueue()
{
	if (mDeleteQueue.size() > 0)
	{
		DisplayObject3D* obj;
		while (mDeleteQueue.size() > 0)
		{
			obj = mDeleteQueue.front();
			delete obj;
			mDeleteQueue.pop();
		}
	}
}