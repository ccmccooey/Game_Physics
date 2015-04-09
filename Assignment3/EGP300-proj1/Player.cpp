#include "Player.h"
#include "InputSystem.h"

Player::Player()
{

}
Player::~Player()
{

}
void Player::FixedUpdate(double t)
{
	if (InputSystem::KeyDown('a') || InputSystem::KeyDown('A'))
	{
		
	}
	else if (InputSystem::KeyDown('d') || InputSystem::KeyDown('D'))
	{
		
	}
	if (InputSystem::KeyDown('s') || InputSystem::KeyDown('S'))
	{
		
	}
	else if (InputSystem::KeyDown('w') || InputSystem::KeyDown('W'))
	{
		
	}
	if (InputSystem::KeyPressed(' '))
	{
		
	}
}