#include "Camera.h"
#include "Model.h"
#include "Color.h"
#include "DisplayObject3D.h"
#include "PointLight.h"
#include "Material.h"
#include "Sprite2D.h"
#include "GUIImage.h"
#include "GUISystem.h"
#include "PlanetManager.h"
#include "ParticleSystem.h"
#include "TextRenderer.h"
#include "MainApp.h"
#include "Planet.h"
#include <ctime>
#include <vector>
#include <iostream>

MainApp*		app;
PointLight*		myLight;
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
	//myLight->setColor(0.0f, 0.25f, 0.0f, 1.0f);
	myLight->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	//Projection
	setupWorld();
}
void setupWorld()
{
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

void Keys(unsigned char key, int x, int y)
{
	app->CheckKeyboardInput(key);
}

void SpecialKeys(int key, int x, int y)
{
	app->CheckSpecialKeyboardInput(key, x, y);
}

void Update(void)
{
	glutPostRedisplay();
}

//it woulda been nice to put this is MainApp.cpp but callbacks do not seem to work on member type functions
void FixedUpdate(int value)
{
	double t = (double)value / 1000.0;
	/*
	double val = 3.0e3;
	for (int i = 0; i < 1000; i++)
	{
		particleSystem->FixedUpdate(t * val);
		planetManager->FixedUpdate(t * val);
	}*/
	
	double val = 3.0e5;
	app->FixedUpdate(t);

	glutTimerFunc(16, FixedUpdate, 16); //16 is for 60 frames per second
}

void Cleanup()
{
	delete app;
	delete arr;
	delete myLight;
}

//This happens when the openGL window size changes
void ChangeSize(int w, int h)
{
	app->UpdateWindowSize(w, h);
}

//clicking
void MouseClick(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	std::cout << "clickXY (" << x << ", " << y << ")" << std::endl;
	mouseStatePrevious = mouseStateCurrent;
	mouseStateCurrent = state;
	app->CheckMouseInput(x, y, state == GLUT_DOWN, state == GLUT_DOWN);
}
void MouseMotionDown(int x, int y)
{
	//std::cout << "mouseXY (" << x << ", " << y << ")" << std::endl;
	app->CheckMouseInput(x, y, true, false);
}
void MouseMotionUp(int x, int y)
{
	//std::cout << "mouseXY (" << x << ", " << y << ")" << std::endl;
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

	glutCreateWindow("Please make this work HELP");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	glutTimerFunc(16, FixedUpdate, 16); //16 is for 60 frames per second
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMotionDown);
	glutPassiveMotionFunc(MouseMotionUp);
	glutKeyboardFunc(Keys);
	glutIdleFunc(Update);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	myInit();

	glutMainLoop();

	Cleanup();
	
	return 0;
}

