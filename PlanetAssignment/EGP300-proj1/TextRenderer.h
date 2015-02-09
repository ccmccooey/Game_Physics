#ifndef _TEXT_RENDERER_H
#define _TEXT_RENDERER_H

class TextField;
class Texture;

#include "GLfiles.h"
#include <string>
#include <queue>
#include <list>
#include <vector>
#include "Vector3f.h"

class TextRenderer
{
private:
	std::queue<std::string> mDrawQueue;
	std::vector<int> mIndexArray;
	//std::list<TextField*> mTextFieldVector;
	Texture* mFontSheet;
	
	GLBatch** mMeshes;
	int mMeshCount;
	
	//for the shader
	GLuint mShader;
	GLint mLocMVP; //location of remote "mvpMatrix"
	GLint mLocTexture; //location of "text"

	//for rendering
	M3DMatrix44f mModelView;
	M3DMatrix44f mvpMatrix;

public:
	TextRenderer();
	~TextRenderer();

	GLBatch* GetBatchForChar(char theChar) const;

	void DrawTextField(TextField* textField, const M3DMatrix44f &projection, M3DMatrix44f &view);
	void DrawTextField(const std::string &text, const Vector3f &position, const M3DMatrix44f &projection, M3DMatrix44f &view); //slower than drawing textfields

private:
	void Initialize();
	void InitialzeCharacterSourceInformation();
	void CleanUp();
};

#endif