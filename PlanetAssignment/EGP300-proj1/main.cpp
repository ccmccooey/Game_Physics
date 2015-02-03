#include "Camera.h"
#include "Model.h"
#include "Color.h"
#include "DisplayObject3D.h"
#include "PointLight.h"
#include "Material.h"
#include "Sprite2D.h"
#include "GUIImage.h"
#include "GUISystem.h"
#include "Planet.h"
#include <ctime>
#include <vector>
#include <iostream>

GLShaderManager	shaderManager;
M3DMatrix44f	mvpMatrix;
M3DMatrix44f    identity;
GLFrustum		viewFrustum3D;
GLFrustum		viewFrustum2D;
GLint			width, height;
GLfloat			rotateAroundModelZaxis;
GLfloat			rotateAroundViewZaxis;
Camera*			camera;
DisplayObject3D*		myCube;
Texture*		myTexture;
GuiSystem*		guiSystem;
//Sprite2D*		mySprite;
Material*		myMaterial;
Model*			cubeModel;
Planet			myPlanet;
PointLight*		myLight;
//GUIImage*		myGUIImage;
M3DMatrix44f    guiViewMatrix;
GLfloat* arr;

GLfloat pointLight[4] = {1.0f, 1.0f, 1.0f, 0.0f};
//GLuint myTexture;
const float VIEW_MOVE_SPEED = 0.75f;
const float VIEW_ROTATE_SPEED = 1.0f;

void setupWorld();

void myInit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	shaderManager.InitializeStockShaders();

	//seed the random
	srand((unsigned int)time(NULL));

	//objects
	m3dLoadIdentity44(identity);
	
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

	glLightfv(GL_LIGHT0, GL_AMBIENT, arr);
	glLightfv(GL_LIGHT0, GL_POSITION, arr);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, arr);


	myLight = new PointLight(1, 2, -10);
	//myLight->setColor(0.0f, 0.25f, 0.0f, 1.0f);
	myLight->setColor(1.0f, 1.0f, 1.0f, 1.0f);
	//Projection
	viewFrustum3D.SetPerspective(35.0f, (float)(width/height), 1.0f, 1000.0f);
	viewFrustum2D.SetOrthographic((GLfloat)(0), (GLfloat)(width), (GLfloat)(0), (GLfloat)(height), -10.0f, 10.0f);

	//m3dTranslationMatrix44(guiViewMatrix, (double)(-width / 2), (double)(height / 2), 0.0);
	m3dTranslationMatrix44(guiViewMatrix, (double)(-width / 2.1), (double)(height / 2.2), 0.0);

	camera = new Camera();
	camera->setRotationAxis(0.0f, 1.0f, 0.0f);

	rotateAroundModelZaxis = 0;
	rotateAroundViewZaxis = 0;
	setupWorld();
}
void setupWorld()
{
	//myTexture = new Texture("../MyTexture.tga");

	myTexture = new Texture("../GuiButtons/PlayButton.png");

	//mySprite = new Sprite2D("../GuiButtons/PlayButton.png");

	myMaterial = new Material(myTexture);

	
	guiSystem = new GuiSystem(width, height);
	//myGUIImage = new GUIImage(mySprite, 34, 34);

	m3dLoadIdentity44(identity);


	cubeModel = new Model(myMaterial, Geometry::CUBE);
	
	//create a cube
	//myCube = new DisplayObject3D(nullptr);
	myCube = new DisplayObject3D(cubeModel);

	//create my planet
	myPlanet = Planet(cubeModel);
}

void RenderScene(void)
{
	//Swap Colors
	GLfloat vColor[]=  { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat vColor2[]=  { 0.0f, 1.0f, 0.25f, 1.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	DisplayObject3D *current;
	current = myCube;
	current->Draw(shaderManager, viewFrustum3D.GetProjectionMatrix(), camera->getView());

	myPlanet.Draw(shaderManager, viewFrustum3D.GetProjectionMatrix(), camera->getView());
	

	//myGUIImage->Draw(&shaderManager, camera->getView(), viewFrustum3D.GetProjectionMatrix());
	//myGUIImage->Draw(&shaderManager, camera->getView(), viewFrustum3D.GetProjectionMatrix());
	//myGUIImage->Draw(&shaderManager, viewFrustum3D.GetProjectionMatrix());
	//myGUIImage->Draw(&shaderManager, viewFrustum2D.GetProjectionMatrix());
	//myGUIImage->Draw(&shaderManager, guiViewMatrix, viewFrustum2D.GetProjectionMatrix());
	guiSystem->DrawGUI(&shaderManager);
	//guiSystem->DrawGUI(&shaderManager, guiViewMatrix, viewFrustum2D.GetProjectionMatrix());

	/*
	M3DMatrix44f &model = current->getTransform()->GetModelMatrix();
	m3dMatrixMultiply44(mModelView, camera->getView(), model);
	m3dMatrixMultiply44(mvpMatrix, viewFrustum.GetProjectionMatrix(), mModelView);
	shaderManager.UseStockShader(GLT_SHADER_SHADED, mvpMatrix);
	current->Draw(mvpMatrix);*/

	/*
	for (unsigned int i = 0; i < objectList.size(); i++)
	{
		current = objectList[i];
		current->getModelMatrix();
		m3dMatrixMultiply44(mModelView, camera->getView(), current->getModelMatrix());
		m3dMatrixMultiply44(mvpMatrix, viewFrustum.GetProjectionMatrix(), mModelView);
		//shaderManager.UseStockShader(GLT_SHADER_SHADED, mvpMatrix);
		//shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, mModelView, viewFrustum.GetProjectionMatrix(), pointLight, vColor);
		//shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, mModelView, viewFrustum.GetProjectionMatrix(), pointLight, vColor, myTexture);
		//shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, mModelView, viewFrustum.GetProjectionMatrix(), pointLight, vColor);	
		//shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, mModelView, viewFrustum.GetProjectionMatrix(), myLight->getPositionData(), myLight->getColorData());

		//NO TEXTURE WHEN THIS NOTHING APPEARS ON THE SCREEN HELP!!
		glBindTexture(GL_TEXTURE_2D, myTexture);
		//shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE, mvpMatrix, myLight->getColorData(), 0);
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, mModelView, viewFrustum.GetProjectionMatrix(), myLight->getPositionData(), myLight->getColorData(), 0);

		//shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, mModelView, viewFrustum.GetProjectionMatrix(), myLight->getPositionData(), myLight->getColorData());
		current->draw(mvpMatrix);
	}*/

	glutSwapBuffers();
}

void Keys(unsigned char key, int x, int y)
{
	if ((key == 'Z')||(key == 'z'))
	{
		rotateAroundModelZaxis += 10.0f;
	}

	if ((key == 'X')||(key=='x'))
	{
		rotateAroundModelZaxis -= 10.f;
	}
	if (key == 'C' || key == 'c')
	{
		myLight->setColor((float)(rand() % 100) * 0.01f, (float)(rand() % 100) * 0.01f, (float)(rand() % 100) * 0.01f, 1.0f);	
	}
	if (key == 'V' || key == 'v')
	{
		myLight->setPosition((float)(rand() % 100), (float)(rand() % 100), (float)(rand() % 100) * -1);
	}

	
}

void SpecialKeys(int key, int x, int y)
{
	

	if (key == GLUT_KEY_LEFT)
	{
		//rotateAroundViewZaxis+=10.0f;
		camera->rotateCamera(-VIEW_ROTATE_SPEED);
		//camera->moveCamera(VIEW_MOVE_SPEED, 0.0f, 0.0f);
	}
	if (key == GLUT_KEY_RIGHT)
	{
		//rotateAroundViewZaxis-=10.f;
		camera->rotateCamera(VIEW_ROTATE_SPEED);
		//camera->moveCamera(-VIEW_MOVE_SPEED, 0.0f, 0.0f);
	}
	if (key == GLUT_KEY_UP)
	{
		float angle = camera->getRotationAngle();
		m3dDegToRad(angle);
		float xMove = cos(angle) * VIEW_MOVE_SPEED;
		float yMove = sin(angle) * VIEW_MOVE_SPEED;
		camera->moveCamera(yMove, 0.0f, xMove);
		//camera->moveCamera(0.0f, 0.0f, VIEW_MOVE_SPEED);
	}
	if (key == GLUT_KEY_DOWN)
	{
		float angle = camera->getRotationAngle();
		m3dDegToRad(angle);
		float xMove = cos(angle) * -VIEW_MOVE_SPEED;
		float yMove = sin(angle) * -VIEW_MOVE_SPEED;
		camera->moveCamera(yMove, 0.0f, xMove);
		//camera->moveCamera(0.0f, 0.0f, -VIEW_MOVE_SPEED);
	}
	if (key == GLUT_KEY_PAGE_DOWN)
	{
		//myCube->getTransform()->Scale(0.25f, 0.0f, 0.0f);
		myCube->getTransform()->Translate(1, 0, 0);
	}
}

void Update(void)
{
	glutPostRedisplay();
}

void Cleanup()
{
	delete myCube;
	delete camera;
	delete arr;
	delete myLight;
	delete myTexture;
	delete myMaterial;
	delete guiSystem;
	//delete myGUIImage;
	//delete mySprite;
}

//This happens when the openGL window size changes
void ChangeSize(int w, int h)
{
	width = w;
	height = h;

	glViewport(0,0,width, height);


	viewFrustum3D.SetPerspective(35.0f, (float)(width/height), 1.0f, 1000.0f);

	guiSystem->UpdateWindowSize(width, height);

	//viewFrustum2D.SetOrthographic((GLfloat)(-width / 2), (GLfloat)(width / 2), (GLfloat)(-height / 2), (GLfloat)(height / 2), -10.0f, 10.0f);

}

//clicking
void MouseClick(int x1, int y1, int x, int y)
{
	std::cout << "clickXY (" << x << ", " << y << ")" << std::endl;


	M3DMatrix44f projectionInverse;
	m3dInvertMatrix44(projectionInverse, viewFrustum3D.GetProjectionMatrix());
	float screenSpaceX = (float)x;
	float screenSpaceY = -(float)y; //this should be negative
	screenSpaceX = screenSpaceX / width;
	screenSpaceY = screenSpaceY / height;

	//pull into screen coordinates
	screenSpaceX = (screenSpaceX * 2) - 1;
	screenSpaceY = (screenSpaceY * 2) - 1;
	Vector3f vec3n = Vector3f(screenSpaceX, screenSpaceY, -1);
	Vector3f vec3p = Vector3f(screenSpaceX, screenSpaceY, 1);


	Vector3f viewSpaceVec1 = vec3n * projectionInverse;
	Vector3f viewSpaceVec2 = vec3p * projectionInverse;

	M3DMatrix44f viewInverse;
	m3dInvertMatrix44(viewInverse, camera->getView());

	Vector3f worldSpaceVec1 = viewSpaceVec1 * viewInverse;
	Vector3f worldSpaceVec2 = viewSpaceVec2 * viewInverse;
}
void MouseMotionDown(int x, int y)
{
	std::cout << "mouseXY (" << x << ", " << y << ")" << std::endl;
	if (guiSystem != nullptr)
		guiSystem->CheckMouse(x, y, true);
}
void MouseMotionUp(int x, int y)
{
	std::cout << "mouseXY (" << x << ", " << y << ")" << std::endl;
	if (guiSystem != nullptr)
		guiSystem->CheckMouse(x, y, false);
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
	width = 800;
	height = 600;
	glutInitWindowSize(800,600);

	glutCreateWindow("IT FINALLY WORKS");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
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

