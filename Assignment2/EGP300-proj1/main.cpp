#include "PointLight.h"
#include "MainApp.h"
#include "InputSystem.h"
#include <ctime>
#include <vector>
#include <iostream>

MainApp*		app;
PointLight*		myLight;
InputSystem*	inputSystem;
GLfloat* arr;
int mouseStateCurrent = GLUT_UP;
int mouseStatePrevious = GLUT_UP;

GLfloat pointLight[4] = {1.0f, 1.0f, 1.0f, 0.0f};
//GLuint myTexture;
const float VIEW_MOVE_SPEED = 0.75f;
const float VIEW_ROTATE_SPEED = 1.0f;

void setupWorld();

void myInit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//seed the random
	srand((unsigned int)time(NULL));

	//objects
	arr = new GLfloat[4];
	arr[0] = 0.25f;
	arr[1] = 0.25f;
	arr[2] = 0.25f;
	arr[3] = 1.00f;

	GLfloat arr2[4] = {0.0f, 1.0f, 0.25f, 1.0f};
	GLfloat arr3[4] = {0.0f, 1.0f, 0.0f, 1.0f};

	//lighting
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLightfv(GL_LIGHT0, GL_AMBIENT, arr);
	glLightfv(GL_LIGHT0, GL_POSITION, arr);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, arr);

	myLight = new PointLight(1, 2, -10);
	myLight->setColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Projection
	setupWorld();
}
void setupWorld()
{
	inputSystem = new InputSystem();

	//myTexture = new Texture("../MyTexture.tga");
	app = new MainApp();
	app->UpdateWindowSize(800, 600);
}

void RenderScene(void)
{
	//Swap Colors
	GLfloat vColor[]=  { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat vColor2[]=  { 0.0f, 1.0f, 0.25f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	app->RenderScene();

	glutSwapBuffers();
}

void KeysDown(unsigned char key, int x, int y)
{
	inputSystem->ChangeKeyState(key, true);
}
void KeysUp(unsigned char key, int x, int y)
{
	inputSystem->ChangeKeyState(key, false);
}
void SpecialKeysDown(int key, int x, int y)
{
	inputSystem->ChangeSpecialKeyState(key, true);
}
void SpecialKeysUp(int key, int x, int y)
{
	inputSystem->ChangeSpecialKeyState(key, false);
}

void Update(void)
{
	glutPostRedisplay();
}

//it woulda been nice to put this is MainApp.cpp but callbacks do not work on member type functions
void FixedUpdate(int value)
{
	double t = (double)value / 1000.0;
	app->FixedUpdate(t);
	glutTimerFunc(16, FixedUpdate, 16); //16 is for 60 frames per second
}

void Cleanup()
{
	delete inputSystem;
	delete app;
	delete arr;
	delete myLight;
}

//This happens when the openGL window size changes
void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);

	app->UpdateWindowSize(w, h);
}

//mouse is clicked
void MouseClick(int button, int state, int x, int y)
{
	//if (state == GLUT_DOWN)
	//std::cout << "clickXY (" << x << ", " << y << ")" << std::endl;
	mouseStatePrevious = mouseStateCurrent;
	mouseStateCurrent = state;
	inputSystem->UpdateMouseClick(button, state == GLUT_DOWN, x, y);
	app->CheckMouseInput(x, y, button == GLUT_LEFT, state == GLUT_DOWN);
}

//mouse is down and it moves
void MouseMotionDown(int x, int y)
{
	inputSystem->UpdateMousePosition(x, y);
	app->CheckMouseInput(x, y, true, false);
}
//mouse is up and it moves
void MouseMotionUp(int x, int y)
{
	inputSystem->UpdateMousePosition(x, y);
	app->CheckMouseInput(x, y, false, false);
}

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		std::cout << argv[1] << std::endl;
	}

	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGBA| GLUT_DEPTH | GLUT_STENCIL | GLUT_ALPHA);
	glEnable(GL_DEPTH);
	//glEnable(GL_TEXTURE);
	glutInitWindowSize(800,600);

	glutCreateWindow("Mass Aggregate System");
	glutReshapeFunc(ChangeSize); //changing the size of the window
	glutDisplayFunc(RenderScene); //rendering is all here
	glutSpecialFunc(SpecialKeysDown); //special glut keyboard input
	glutSpecialUpFunc(SpecialKeysUp);
	glutTimerFunc(16, FixedUpdate, 16); //16 is for 60 frames per second
	glutMouseFunc(MouseClick); //mouse click
	glutMotionFunc(MouseMotionDown); //mouse drag
	glutPassiveMotionFunc(MouseMotionUp); //mouse move, no click
	glutKeyboardFunc(KeysDown); //keyboard input
	glutKeyboardUpFunc(KeysUp);
	glutIdleFunc(Update); //uncontrolled update, unfixed framerate
	atexit(Cleanup);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	myInit();

	glutMainLoop();

	//Cleanup();
	
	return 0;
}

