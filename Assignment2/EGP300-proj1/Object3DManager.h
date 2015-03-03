class Object3D;
class Model;
#include "GLfiles.h"
#include <list>
#include <vector>

class Object3DManager
{
public:
	Object3DManager();
	~Object3DManager();
	Object3D* addNewObject(Model* model, float xPosition, float yPosition, float zPosition);
	void removeObject(Object3D* object);
	void removeAllObjects();

	void Update();
	void Draw(M3DMatrix44f &mvpMatrix);

private:
	void flushDeleteQueue();

private:
	std::vector<Object3D*> mObjectList;
	std::list<Object3D*> mDeleteQueue;
};