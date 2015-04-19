/**********************************************************************
*	Author:  Christopher McCooey
*	Filename:  GraphicsSystem.h
*
*	Description:
*		This is a singleton class stores all the assets and display objects related to graphics. This class prevents the need to have a large number of includes 
*		througout the rest of the project.
*
**********************************************************************/

#ifndef _GRAPHICS_SYSTEM_H
#define _GRAPHICS_SYSTEM_H

#include "ShaderType.h"
#include <string>

class TextureManager;
class ShaderManager;
class MaterialManager;
class ModelManager;
class DisplayObject3DManager;
class DisplayObject3D;
class TextRenderer;
class Camera;

class Texture;
class Material;
class ShaderBase;
class Model;

class GLShaderManager;
class GLFrustum;

struct DrawData;

class GraphicsSystem
{
private:
	//singleton
	static GraphicsSystem* msSystem;

	//asset managers
	TextureManager* mTextureManager;
	ShaderManager* mShaderManager;
	MaterialManager* mMaterialManager;
	ModelManager* mModelManager;
	DisplayObject3DManager* mDisplayList;

	//for rendering text
	TextRenderer* mTextRenderer;
	GLFrustum* mViewFrustum3D;
	DrawData* mDrawData;

	//openGL stuff
	GLShaderManager* mStockShaders;

	int mWindowWidth;
	int mWindowHeight;
	float mNear;
	float mFar;

private:
	GraphicsSystem();
	~GraphicsSystem();

public:
	//creating and destroy the graphics
	static void CreateSystem(); //creates the graphics system, only one can be created at a time
	static void DestroySystem(); //destroys the graphics system

	//non-static accessors may be removed later
	GLShaderManager* GetStockShaders() const;
	TextRenderer* GetTextRenderer() const;
	DrawData* GetDrawData() const;

	//static accessors
	static Texture* GetTexture(const std::string &key); //find a texture asset using a key
	static Material* GetMaterial(const std::string &key); //find a material using a key
	static Model* GetModel(const std::string &model); //find a model using a key
	static ShaderBase* GetShader(ShaderType type); //find a shader pointer using the enum as the key
	static DisplayObject3DManager* GetDisplayObjectManager(); //get the display list

	//adding and removing graphics objects
	static void AddDisplayObject(DisplayObject3D* object); //add a display object to the display list
	static void RemoveDisplayObject(DisplayObject3D* object); //remove a display object from the display list
	static void RemoveAllDisplayObjects(); //remove all display objects from the display list

	//update the window width and height when it is resized
	void UpdateWindowSize(int w, int h);

	//change the perspective of the view frustum
	void ChangePersective(float near, float far);

	//draw call
	static void RenderScene(Camera* camera); //render the scene, this should be called once in the render function
	static GraphicsSystem* Instance();

public:
	void LoadContent(); //load all assets including textures, materials, and models

private:
	void Initialize(); //initializes the graphics system
	
	void CleanDisplayList(); //remove all display objects from the display list
	void CleanUp(); //deletes the assets and all memory used by the graphics system

	void Draw(Camera* camera) const; //private draw function used by the RenderScene function
};

#endif