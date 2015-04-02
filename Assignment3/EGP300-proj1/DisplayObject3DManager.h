#ifndef _DISPLAY_OBJECT_3D_MANAGER_H
#define _DISPLAY_OBJECT_3D_MANAGER_H

class Model;
class Material;
class DisplayObject3D;
struct DrawData;

#include <forward_list>
#include <queue>

class DisplayObject3DManager
{
private:
	std::forward_list<DisplayObject3D*> mObjects;
	std::queue<DisplayObject3D*> mDeleteQueue;
	int mObjectsCount;

public:
	DisplayObject3DManager();
	~DisplayObject3DManager();

	//accessors
	int GetObjectCount() const;
	bool Contains(DisplayObject3D* object) const;

	//adding and removing objects
	void AddObject(DisplayObject3D* object);
	void AddObject(Model* model);
	void AddObject(Model* model, Material* material);
	void AddObjectMany(DisplayObject3D** objects, int count);
	void RemoveObject(DisplayObject3D* object);
	void RemoveAllObjects();

	void Draw(DrawData* data);

private:
	void FlushDeleteQueue();
};

#endif