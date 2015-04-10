#include "Object3DManager.h"
#include "Object3D.h"
#include "Model.h"

using namespace std;

Object3DManager::Object3DManager()
{

}

Object3DManager::~Object3DManager()
{

}

//add an object
Object3D* Object3DManager::addNewObject(Model* model, float xPosition, float yPosition, float zPosition)
{
	Object3D* obj = new Object3D(model);
	obj->setPosition(xPosition, yPosition, zPosition);
	mObjectList.push_back(obj);
	return obj;
}

//remove an object
void Object3DManager::removeObject(Object3D* obj)
{
	vector<Object3D*>::iterator iter = mObjectList.begin();
	for (iter = mObjectList.begin(); iter != mObjectList.end(); iter++)
	{
		if ((*iter) == obj)
		{
			mDeleteQueue.insert(mDeleteQueue.begin(), obj);
			mObjectList.erase(iter);
			break;
		}
	}
}
void Object3DManager::flushDeleteQueue()
{
	list<Object3D*>::iterator iter = mDeleteQueue.begin();
	while (iter != mDeleteQueue.end())
	{
		delete (*iter);
		++iter;
	}
	mDeleteQueue.clear();
}

void Object3DManager::Update()
{
	vector<Object3D*>::iterator iter = mObjectList.begin();
	for (iter = mObjectList.begin(); iter != mObjectList.end(); iter++)
	{
		(*iter)->update();
	}
}

void Object3DManager::Draw(M3DMatrix44f &mvpMatrix)
{
	//M3DMatrix44f mModelView;

	vector<Object3D*>::iterator iter = mObjectList.begin();
	for (iter = mObjectList.begin(); iter != mObjectList.end(); iter++)
	{
		(*iter)->draw(mvpMatrix);
	}
}