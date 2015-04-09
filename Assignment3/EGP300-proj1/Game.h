#ifndef _GAME_H
#define _GAME_H

#include <string>

class Game
{
private:
	
private:

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