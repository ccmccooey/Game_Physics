#ifndef _LEVEL_H
#define _LEVEL_H

class ObjectSpawner;

#include "Vector3f.h"
#include <string>

//loads level data from a text file and will spawn all the objects specfied in the data file
class Level
{
private:
	struct LNode
	{
		LNode(){}
		~LNode(){}

		Vector3f position;
		char type;
	};

public:
	static bool Level::LoadLevel(const std::string &dataFile, ObjectSpawner* spawner);
};

#endif

/* //Data Format: (each line represents one mass aggregate)

geometry, positionX, positionY, positionZ
geometry, positionX, positionY, positionZ
geometry, positionX, positionY, positionZ
geometry, positionX, positionY, positionZ
...

*/


