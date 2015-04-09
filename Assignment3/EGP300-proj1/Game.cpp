#include "Game.h"

using namespace std;

//constructors
Game::Game()
{
	Initialize();
}
Game::~Game()
{
	CleanUp();
}

//initialization
void Game::Initialize()
{

}

//update all the mass aggregate graphics
void Game::Update(double t)
{
	
}

//cleanup
void Game::CleanUp()
{
	
}

//reset the mass aggregates
void Game::Reset()
{
	
}

void Game::GetDebugInfo(std::string &info) const
{
	info = "No info yet";
}