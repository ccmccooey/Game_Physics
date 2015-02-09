#include "TextRenderer.h"
#include "BasicGeometry.h"
#include "TextField.h"
#include "Transform.h"
#include "Texture.h"

using namespace std;

TextRenderer::TextRenderer()
{
	Initialize();
}
TextRenderer::~TextRenderer()
{
	CleanUp();
}

void TextRenderer::Initialize()
{
	//shader stuff
	mShader = gltLoadShaderPairWithAttributes(	"shaders/textShader.vp", "shaders/textShader.fp",
														2,
														GLT_ATTRIBUTE_VERTEX, "inVertex",
														GLT_ATTRIBUTE_TEXTURE0, "inUV");

	mLocMVP = glGetUniformLocation(mShader, "mvpMatrix");

	mLocTexture = glGetUniformLocation(mShader, "tex");

	glUseProgram(mShader);
	glUniform1i(mLocTexture, 0);

	//load the texture
	mFontSheet = new Texture("../Text/TextSheet.png");
	//mFontSheet = new Texture("../Text/test.png");

	//spritesheet data
	int width = mFontSheet->getWidth();
	int height = mFontSheet->getHeight();
	int letterWidth = width / 16;
	int letterHeight = height / 16;

	//gl batches
	mMeshCount = 11;

	mMeshes = new GLBatch*[mMeshCount];
	int x = 0;
	int y = 0;

	for (int i = 0; i < mMeshCount; i++)
	{
		GLBatch* batch = new GLBatch();
		BasicGeometry::setDataToQuad(batch, (float)x / (float)width, (float)y / (float)height, (float)letterWidth / (float)width, (float)letterWidth / (float)height);

		x += letterWidth;
		if (x >= letterWidth * 16)
		{
			x = 0;
			y += letterHeight;
		}

		mMeshes[i] = batch;
	}
	InitialzeCharacterSourceInformation();
}
void TextRenderer::InitialzeCharacterSourceInformation()
{
	int size = mFontSheet->getWidth() * mFontSheet->getHeight() / 16;
	mIndexArray = vector<int>(size);
}


GLBatch* TextRenderer::GetBatchForChar(char theChar) const
{
	if (theChar == 'l')
		return mMeshes[4];
	return mMeshes[3];
}


void TextRenderer::CleanUp()
{
	//delete the meshes
	for (int i = 0; i < mMeshCount; i++)
	{
		delete mMeshes[i];
	}
	delete [] mMeshes;

	//delete texture
	delete mFontSheet;
	mFontSheet = nullptr;
}

void TextRenderer::DrawTextField(const std::string &text, const Vector3f &position, const M3DMatrix44f &projection, M3DMatrix44f &view)
{
	TextField tmp = TextField(position, text);
	this->DrawTextField(&tmp, projection, view);
}
void TextRenderer::DrawTextField(TextField* current, const M3DMatrix44f &projection, M3DMatrix44f &view)
{
	
	//bind texture and use shader
	
	glUseProgram(mShader);
	mFontSheet->BindTexture();

	//iterate through the textfield
	string text = current->GetText();;
	float fontSize = current->GetFontSize();
	Vector3f originalPosition = current->GetPosition();;
	GLBatch* batch;
	unsigned int j;
	unsigned int eolCount = 0; //end of line marker count
	

	//draw each character of the textfield
	for (j = 0; j < text.length(); j++)
	{
		//only need to draw the batch if its not a space
		if (text[j] == '\n')
		{
			current->GetTransform()->SetPosition(originalPosition.x, originalPosition.y + (eolCount * fontSize), originalPosition.z);
			eolCount++;
		}
		else
		{
			if (text[j] != ' ')
			{
				m3dMatrixMultiply44(mModelView, view, current->GetTransform()->GetModelMatrix());
				m3dMatrixMultiply44(mvpMatrix, projection, mModelView);

				batch = this->GetBatchForChar(text[j]);
				
				glUniformMatrix4fv(mLocMVP, 1, GL_FALSE, mvpMatrix);						
				if (batch != nullptr)
				{
					batch->Draw();
				}
			}
			current->GetTransform()->Translate(0.75f, 0.0f, 0.0f);
		}
	}

	current->SetPosition(originalPosition);
}


