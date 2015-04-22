#ifndef _GAME_H
#define _GAME_H

class Ground;

#include <string>
#include <vector>

class GameObject;

class Game
{
private:
	std::vector<GameObject*> mGameObjects;
	Ground* mGround;

public:
	Game();
	~Game();

	void GetDebugInfo(std::string &info) const;

	void Update(double t);

	void Reset();

private:
	void Initialize();
	void CleanUp();
};

#endif