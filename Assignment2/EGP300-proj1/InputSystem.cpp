/**********************************************************************
*	Author:  Christopher McCooey
*	Filename:  InputSystem.cpp
*
*	Description:
*		This class stores keyboard states and is used to make input easier. The keyboard states are changed using glut callback functions.
*
**********************************************************************/

#include "InputSystem.h"
#include <iostream>

#define KEYS_COUNT 256
#define SPECIAL_COUNT 21

InputSystem* InputSystem::msInstance = nullptr;

InputSystem::InputSystem()
{
	//singleton
	if (msInstance != nullptr)
	{
		delete msInstance;
		std::cerr << "WARNING! Two input systems were created" << std::endl;
	}
	msInstance = this;


	int i;

	//regular keys
	mKeysCurrent = new bool[KEYS_COUNT];
	mKeysPrevious = new bool[KEYS_COUNT];

	for (i = 0; i < KEYS_COUNT; i++)
	{
		mKeysCurrent[i] = false;
		mKeysPrevious[i] = false;
	}
	mCharQueue = std::queue<unsigned char>();

	//special keys
	mSpecialCurrent = new bool[SPECIAL_COUNT];
	mSpecialPrevious = new bool[SPECIAL_COUNT];
	for (i = 0; i < SPECIAL_COUNT; i++)
	{
		mSpecialCurrent[i] = false;
		mSpecialPrevious[i] = false;
	}
	mSpecialQueue = std::queue<int>();
}
InputSystem::~InputSystem()
{
	delete [] mKeysCurrent;
	delete [] mKeysPrevious;
}

//called in glut callbacks
void InputSystem::UpdateMousePosition(int x, int y)
{
	mMouseX = x;
	mMouseY = y;
}
void InputSystem::UpdateMouseClick(int button, int state, int x, int y)
{
	mMouseX = x;
	mMouseY = y;
}
void InputSystem::ChangeKeyState(unsigned char key, bool state)
{
	mKeysPrevious[key] = mKeysCurrent[key];
	mKeysCurrent[key] = state;
	mCharQueue.push(key);
}
void InputSystem::ChangeSpecialKeyState(int specialKey, bool state)
{
	if (specialKey > 0x000C)
		specialKey -= (0x0064 - 0x000C);
	else
		specialKey -= 0x0001;

	mSpecialPrevious[specialKey] = mSpecialCurrent[specialKey];
	mSpecialCurrent[specialKey] = state;
	mSpecialQueue.push(specialKey);
}

//checking input
bool InputSystem::KeyDown(unsigned char key)
{
	return msInstance->mKeysCurrent[key];
}
bool InputSystem::KeyUp(unsigned char key)
{
	return !msInstance->mKeysCurrent[key];
}
bool InputSystem::KeyPressed(unsigned char key)
{
	return msInstance->mKeysCurrent[key] && (msInstance->mKeysCurrent[key] != msInstance->mKeysPrevious[key]);
}
bool InputSystem::KeyReleased(unsigned char key)
{
	return !msInstance->mKeysCurrent[key] && (msInstance->mKeysCurrent[key] != msInstance->mKeysPrevious[key]);
}
bool InputSystem::KeyDown(SpecialKeyCode key)
{
	return msInstance->mSpecialCurrent[(int)key];
}
bool InputSystem::KeyUp(SpecialKeyCode key)
{
	return !msInstance->mSpecialCurrent[(int)key];
}
bool InputSystem::KeyPressed(SpecialKeyCode key)
{
	return msInstance->mSpecialCurrent[(int)key] && (msInstance->mSpecialCurrent[(int)key] != msInstance->mSpecialPrevious[(int)key]);
}
bool InputSystem::KeyReleased(SpecialKeyCode key)
{
	return !msInstance->mSpecialCurrent[(int)key] && (msInstance->mSpecialCurrent[(int)key] != msInstance->mSpecialPrevious[(int)key]);
}

//finish update for dealing with key press/release
void InputSystem::FinishUpdate()
{
	while (mCharQueue.size() > 0)
	{
		char key = mCharQueue.front();
		mCharQueue.pop();

		mKeysPrevious[key] = mKeysCurrent[key];		
	}

	while (mSpecialQueue.size() > 0)
	{
		int key = mSpecialQueue.front();
		mSpecialQueue.pop();

		mSpecialPrevious[key] = mSpecialCurrent[key];		
	}
}