/**********************************************************************
*	Author:  Christopher McCooey
*	Filename:  InputSystem.h
*
*	Description:
*		This class stores keyboard states and is used to make input easier. The keyboard states are changed using glut callback functions.
*
**********************************************************************/

#ifndef _INPUT_SYSTEM_H
#define _INPUT_SYSTEM_H

#include "SpecialKeyCode.h"
#include <queue>

class InputSystem
{
private:
	bool mMouseDown;
	bool mMouseDownPrevious;
	int mMouseX;
	int mMouseY;
	bool* mKeysCurrent;
	bool* mKeysPrevious;

	bool* mSpecialCurrent;
	bool* mSpecialPrevious;

	std::queue<unsigned char> mCharQueue;
	std::queue<int> mSpecialQueue;

	static InputSystem* msInstance;

public:
	InputSystem();
	~InputSystem();

	//these should be called in glut callback functions
	void UpdateMousePosition(int x, int y);
	void UpdateMouseClick(int button, int state, int x, int y);
	void ChangeKeyState(unsigned char key, bool state);
	void ChangeSpecialKeyState(int specialKey, bool state);

	//call this at the end of the glut update callback
	void FinishUpdate();

	//use these for character keys
	static bool KeyDown(unsigned char key); //the key is held down
	static bool KeyUp(unsigned char key); //the key is up
	static bool KeyPressed(unsigned char key); //the key changed from being up to being down
	static bool KeyReleased(unsigned char key); //the key changed from being down to being up

	//use these for special keys such as arrow keys
	static bool KeyDown(SpecialKeyCode key);
	static bool KeyUp(SpecialKeyCode key);
	static bool KeyPressed(SpecialKeyCode key);
	static bool KeyReleased(SpecialKeyCode key);
};

#endif
