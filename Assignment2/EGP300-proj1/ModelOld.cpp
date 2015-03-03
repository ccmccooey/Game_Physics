#include "Model.h"
#include "ModelData.h"
#include "MeshData.h"
#include "Color.h"
#include <iostream>
/*
//constructor
Model::Model()
{
	mVerts = nullptr;
	mColors = nullptr;
	mVertexCount = 0;
	mBatchCount = 1;
	mBatch = new GLBatch*[1];
	mBatch[0] = new GLBatch();
}

void Model::reset()
{
	
}

//destructor
Model::~Model()
{
	if (mVerts != nullptr)
	{
		delete [] mVerts;
	}
	if (mColors != nullptr)
	{
		delete [] mColors;
	}
	cleanBatchData();
	//delete mBatch;
}

void Model::cleanBatchData()
{
	//for (int i = 0; i < mBatchCount; i++)
	//{
		//delete mBatch[i];
	//}
	delete [] mBatch;
}

//set the vertex data
void Model::setVertexDataToTriangle(const Color &color1, const Color &color2, const Color &color3)
{
	if (mVerts != nullptr)
	{
		delete [] mVerts;
	}
	mVerts = new GLfloat[9];
	mVerts[0] = -0.5f;
	mVerts[1] = 0.0f;
	mVerts[2] = 0.0f;
	mVerts[3] = 0.5f;
	mVerts[4] = 0.0f;
	mVerts[5] = 0.0f;
	mVerts[6] = 0.0f;
	mVerts[7] = 0.5f;
	mVerts[8] = 0.0f;

	if (mColors != nullptr)
	{
		delete [] mColors;
	}
	mColors = new GLfloat[12];
	mColors[0] = color1.R;
	mColors[1] = color1.G;
	mColors[2] = color1.B;
	mColors[3] = color1.A;
	mColors[4] = color2.R;
	mColors[5] = color2.G;
	mColors[6] = color2.B;
	mColors[7] = color2.A;
	mColors[8] = color3.R;
	mColors[9] = color3.G;
	mColors[10] = color3.B;
	mColors[11] = color3.A;

	mVertexCount = 3;

	mBatch[0]->Begin(GL_TRIANGLES, mVertexCount);
	mBatch[0]->CopyVertexData3f(mVerts);
	mBatch[0]->CopyColorData4f(mColors);
	mBatch[0]->End();
}

void Model::setVertexDataToSquare(const Color &color1, const Color &color2, const Color &color3, const Color &color4)
{
	if (mVerts != nullptr)
	{
		delete [] mVerts;
	}
	mVerts = new GLfloat[12];
	mVerts[0] = -0.5f;
	mVerts[1] = 0.5f;
	mVerts[2] = 0.0f;
	mVerts[3] = -0.5f;
	mVerts[4] = -0.5f;
	mVerts[5] = 0.0f;
	mVerts[6] = 0.5f;
	mVerts[7] = -0.5f;
	mVerts[8] = 0.0f;
	mVerts[9] = 0.5f;
	mVerts[10] = 0.5f;
	mVerts[11] = 0.0f;

	if (mColors != nullptr)
	{
		delete [] mColors;
	}
	mColors = new GLfloat[16];
	mColors[0] = color1.R;
	mColors[1] = color1.G;
	mColors[2] = color1.B;
	mColors[3] = color1.A;
	mColors[4] = color2.R;
	mColors[5] = color2.G;
	mColors[6] = color2.B;
	mColors[7] = color2.A;
	mColors[8] = color3.R;
	mColors[9] = color3.G;
	mColors[10] = color3.B;
	mColors[11] = color3.A;
	mColors[12] = color4.R;
	mColors[13] = color4.G;
	mColors[14] = color4.B;
	mColors[15] = color4.A;

	mVertexCount = 4;

	mBatch[0]->Begin(GL_QUADS, mVertexCount);
	mBatch[0]->CopyVertexData3f(mVerts);
	mBatch[0]->CopyColorData4f(mColors);
	mBatch[0]->End();
}

void Model::setVertexDataToCube(const Color &color1, const Color &color2)
{
	if (mVerts != nullptr)
	{
		delete [] mVerts;
	}
	mVerts = new GLfloat[108];

	//each group is a triangle. WOW this manual generation is really awful and rediculous
	
	//front surface
	mVerts[0] = -0.5f; mVerts[1] = 0.5f; mVerts[2] = -0.5f;
	mVerts[3] = -0.5f; mVerts[4] = -0.5f; mVerts[5] = -0.5f;
	mVerts[6] = 0.5f; mVerts[7] = -0.5f; mVerts[8] = -0.5f;

	mVerts[9] = -0.5f; mVerts[10] = 0.5f; mVerts[11] = -0.5f;
	mVerts[12] = 0.5f; mVerts[13] = 0.5f; mVerts[14] = -0.5f;
	mVerts[15] = 0.5f; mVerts[16] = -0.5f; mVerts[17] = -0.5f;

	//back surface
	mVerts[18] = -0.5f; mVerts[19] = 0.5f; mVerts[20] = 0.5f;
	mVerts[21] = -0.5f; mVerts[22] = -0.5f; mVerts[23] = 0.5f;
	mVerts[24] = 0.5f; mVerts[25] = -0.5f; mVerts[26] = 0.5f;

	mVerts[27] = -0.5f; mVerts[28] = 0.5f; mVerts[29] = 0.5f;
	mVerts[30] = 0.5f; mVerts[31] = 0.5f; mVerts[32] = 0.5f;
	mVerts[33] = 0.5f; mVerts[34] = -0.5f; mVerts[35] = 0.5f;

	//left surface
	mVerts[36] = -0.5f; mVerts[37] = -0.5f; mVerts[38] = 0.5f;
	mVerts[39] = -0.5f; mVerts[40] = -0.5f; mVerts[41] = -0.5f;
	mVerts[42] = -0.5f; mVerts[43] = 0.5f; mVerts[44] = -0.5f;

	mVerts[45] = -0.5f; mVerts[46] = -0.5f; mVerts[47] = 0.5f;
	mVerts[48] = -0.5f; mVerts[49] = 0.5f; mVerts[50] = 0.5f;
	mVerts[51] = -0.5f; mVerts[52] = 0.5f; mVerts[53] = -0.5f;

	//right surface
	mVerts[54] = 0.5f; mVerts[55] = -0.5f; mVerts[56] = 0.5f;
	mVerts[57] = 0.5f; mVerts[58] = -0.5f; mVerts[59] = -0.5f;
	mVerts[60] = 0.5f; mVerts[61] = 0.5f; mVerts[62] = -0.5f;

	mVerts[63] = 0.5f; mVerts[64] = -0.5f; mVerts[65] = 0.5f;
	mVerts[66] = 0.5f; mVerts[67] = 0.5f; mVerts[68] = 0.5f;
	mVerts[69] = 0.5f; mVerts[70] = 0.5f; mVerts[71] = -0.5f;

	//bottom surface
	mVerts[72] = -0.5f; mVerts[73] = -0.5f; mVerts[74] = 0.5f;
	mVerts[75] = -0.5f; mVerts[76] = -0.5f; mVerts[77] = -0.5f;
	mVerts[78] = 0.5f; mVerts[79] = -0.5f; mVerts[80] = -0.5f;

	mVerts[81] = -0.5f; mVerts[82] = -0.5f; mVerts[83] = 0.5f;
	mVerts[84] = 0.5f; mVerts[85] = -0.5f; mVerts[86] = 0.5f;
	mVerts[87] = 0.5f; mVerts[88] = -0.5f; mVerts[89] = -0.5f;

	//top surface
	mVerts[90] = -0.5f; mVerts[91] = 0.5f; mVerts[92] = 0.5f;
	mVerts[93] = -0.5f; mVerts[94] = 0.5f; mVerts[95] = -0.5f;
	mVerts[96] = 0.5f; mVerts[97] = 0.5f; mVerts[98] = -0.5f;

	mVerts[99] = -0.5f; mVerts[100] = 0.5f; mVerts[101] = 0.5f;
	mVerts[102] = 0.5f; mVerts[103] = 0.5f; mVerts[104] = 0.5f;
	mVerts[105] = 0.5f; mVerts[106] = 0.5f; mVerts[107] = -0.5f;


	if (mColors != nullptr)
	{
		delete [] mColors;
	}

	if (mColors != nullptr)
	{
		delete [] mColors;
	}
	int size = (108 / 3) * 4;
	mColors = new GLfloat[size];
	float ch = 1.0;
	for (int i = 0; i < size; i += 12)
	{
		mColors[i + 0] = color1.R * ch;
		mColors[i + 1] = color1.G * ch;
		mColors[i + 2] = color1.B * ch;
		mColors[i + 3] = color1.A * ch;

		mColors[i + 4] = color1.R * ch;
		mColors[i + 5] = color1.G * ch;
		mColors[i + 6] = color1.B * ch;
		mColors[i + 7] = color1.A * ch;

		mColors[i + 8] = color2.R * ch;
		mColors[i + 9] = color2.G * ch;
		mColors[i + 10] = color2.B * ch;
		mColors[i + 11] = color2.A * ch;
		ch -= 0.05f;
	}

	mVertexCount = 108 / 3;

	mBatch[0]->Begin(GL_TRIANGLES, mVertexCount);
	mBatch[0]->CopyVertexData3f(mVerts);
	mBatch[0]->CopyColorData4f(mColors);
	mBatch[0]->End();
}

void Model::setVertexDataToHouse(const Color &color1, const Color &color2, const Color &rcolor1, const Color &rcolor2)
{
	if (mVerts != nullptr)
	{
		delete [] mVerts;
	}
	int boxSize = 72;
	int boxOnlyArraySize = 72 * 2;
	int arraySize = (72 * 2) + 24;
	mVerts = new GLfloat[arraySize];

	float w = 1.0f;
	float h = 0.5f;
	float d = 0.5f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	//each iterration is a box 
	for (int i = 0; i < boxOnlyArraySize; i += boxSize)
	{
		//front surface
		mVerts[i + 0] = -w + x; mVerts[i + 1] = h + y; mVerts[i + 2] = -d + z;
		mVerts[i + 3] = -w + x; mVerts[i + 4] = -h + y; mVerts[i + 5] = -d + z;
		mVerts[i + 6] = w + x; mVerts[i + 7] = -h + y; mVerts[i + 8] = -d + z;
		mVerts[i + 9] = w + x; mVerts[i + 10] = h + y; mVerts[i + 11] = -d + z;

		//back surface
		mVerts[i + 12] = -w + x; mVerts[i + 13] = h + y; mVerts[i + 14] = d + z;
		mVerts[i + 15] = -w + x; mVerts[i + 16] = -h + y; mVerts[i + 17] = d + z;
		mVerts[i + 18] = w + x; mVerts[i + 19] = -h + y; mVerts[i + 20] = d + z;
		mVerts[i + 21] = w + x; mVerts[i + 22] = h + y; mVerts[i + 23] = d + z;

		//left surface
		mVerts[i + 24] = -w + x; mVerts[i + 25] = h + y; mVerts[i + 26] = -d + z;
		mVerts[i + 27] = -w + x; mVerts[i + 28] = -h + y; mVerts[i + 29] = -d + z;
		mVerts[i + 30] = -w + x; mVerts[i + 31] = -h + y; mVerts[i + 32] = d + z;
		mVerts[i + 33] = -w + x; mVerts[i + 34] = h + y; mVerts[i + 35] = d + z;

		//right surface
		mVerts[i + 36] = w + x; mVerts[i + 37] = h + y; mVerts[i + 38] = -d + z;
		mVerts[i + 39] = w + x; mVerts[i + 40] = -h + y; mVerts[i + 41] = -d + z;
		mVerts[i + 42] = w + x; mVerts[i + 43] = -h + y; mVerts[i + 44] = d + z;
		mVerts[i + 45] = w + x; mVerts[i + 46] = h + y; mVerts[i + 47] = d + z;

		//bottom surface
		mVerts[i + 48] = w + x; mVerts[i + 49] = -h + y; mVerts[i + 50] = -d + z;
		mVerts[i + 51] = -w + x; mVerts[i + 52] = -h + y; mVerts[i + 53] = -d + z;
		mVerts[i + 54] = -w + x; mVerts[i + 55] = -h + y; mVerts[i + 56] = d + z;
		mVerts[i + 57] = w + x; mVerts[i + 58] = -h + y; mVerts[i + 59] = d + z;

		//top surface
		mVerts[i + 60] = w + x; mVerts[i + 61] = h + y; mVerts[i + 62] = -d + z;
		mVerts[i + 63] = -w + x; mVerts[i + 64] = h + y; mVerts[i + 65] = -d + z;
		mVerts[i + 66] = -w + x; mVerts[i + 67] = h + y; mVerts[i + 68] = d + z;
		mVerts[i + 69] = w + x; mVerts[i + 70] = h + y; mVerts[i + 71] = d + z;
		
		//changes to the next box
		if (i == 0)
		{
			y += 1.0f;
			x = 0.5f;
			w = 0.50f;
		}
	}
	//roof
	int j = boxOnlyArraySize;

	//left and right shingle sides	
	mVerts[j + 0] = -w + x; mVerts[j + 1] = h + y; mVerts[j + 2] = -d + z;
	mVerts[j + 3] = -w + x; mVerts[j + 4] = h + y; mVerts[j + 5] = d + z;
	mVerts[j + 6] = 0 + x; mVerts[j + 7] = h*2 + y; mVerts[j + 8] = d + z;
	mVerts[j + 9] = 0 + x; mVerts[j + 10] = h*2 + y; mVerts[j + 11] = -d + z;

	mVerts[j + 12] = w + x; mVerts[j + 13] = h + y; mVerts[j + 14] = -d + z;
	mVerts[j + 15] = w + x; mVerts[j + 16] = h + y; mVerts[j + 17] = d + z;
	mVerts[j + 18] = 0 + x; mVerts[j + 19] = h*2 + y; mVerts[j + 20] = d + z;
	mVerts[j + 21] = 0 + x; mVerts[j + 22] = h*2 + y; mVerts[j + 23] = -d + z;


	if (mColors != nullptr)
	{
		delete [] mColors;
	}

	int colorSizeBox = (boxOnlyArraySize / 3) * 4;
	int colorSizeAll = colorSizeBox + 32;
	mColors = new GLfloat[colorSizeAll];
	float ch = 1.0;
	for (int i = 0; i < colorSizeBox; i += 16)
	{		
		mColors[i + 0] = color1.R * ch;
		mColors[i + 1] = color1.G * ch;
		mColors[i + 2] = color1.B * ch;
		mColors[i + 3] = color1.A * ch;

		mColors[i + 4] = color1.R * ch;
		mColors[i + 5] = color1.G * ch;
		mColors[i + 6] = color1.B * ch;
		mColors[i + 7] = color1.A * ch;

		mColors[i + 8] = color2.R * ch;
		mColors[i + 9] = color2.G * ch;
		mColors[i + 10] = color2.B * ch;
		mColors[i + 11] = color2.A * ch;

		mColors[i + 12] = color2.R * ch;
		mColors[i + 13] = color2.G * ch;
		mColors[i + 14] = color2.B * ch;
		mColors[i + 15] = color2.A * ch;
		ch -= 0.05f;
		if (i == 72)
		{
			ch = 1.0f;
		}		
	}
	ch = 1.0f;
	j = colorSizeBox;
	for (int i = 0; i < 32; i += 16)
	{
		mColors[j + i + 0] = rcolor1.R * ch;
		mColors[j + i + 1] = rcolor1.G * ch;
		mColors[j + i + 2] = rcolor1.B * ch;
		mColors[j + i + 3] = rcolor1.A * ch;

		mColors[j + i + 4] = rcolor2.R * ch;
		mColors[j + i + 5] = rcolor2.G * ch;
		mColors[j + i + 6] = rcolor2.B * ch;
		mColors[j + i + 7] = rcolor2.A * ch;

		mColors[j + i + 8] = rcolor1.R * ch;
		mColors[j + i + 9] = rcolor1.G * ch;
		mColors[j + i + 10] = rcolor1.B * ch;
		mColors[j + i + 11] = rcolor1.A * ch;

		mColors[j + i + 12] = rcolor2.R * ch;
		mColors[j + i + 13] = rcolor2.G * ch;
		mColors[j + i + 14] = rcolor2.B * ch;
		mColors[j + i + 15] = rcolor2.A * ch;
	}

	mVertexCount = arraySize / 3;

	mBatch[0]->Begin(GL_QUADS, mVertexCount);
	mBatch[0]->CopyVertexData3f(mVerts);
	mBatch[0]->CopyColorData4f(mColors);
	mBatch[0]->End();
	

}

//Single Mesh
void Model::setVertexDataToCustom(const MeshData &data)
{
	

	int size = data.vertextCount * 4;
	mColors = new GLfloat[size];
	for (int i = 0; i < size; i++)
	{
		mColors[i] = (float)(rand() % 100) * 0.01f;
	}
	
	mBatch[0]->Begin(data.primitiveMode, data.vertextCount, 1);
	mBatch[0]->CopyVertexData3f(data.vertexData);
	//mBatch->CopyColorData4f(mColors);
	mBatch[0]->CopyNormalDataf(data.normalData);
	mBatch[0]->CopyTexCoordData2f(data.uvData, 0);
	mBatch[0]->End();
}

//One or more Meshes
void Model::setVertexDataToCustom(const ModelData &data)
{
	mBatchCount = data.meshList.size();
	if (mBatchCount == 1)
	{
		setVertexDataToCustom(*data.meshList[0]);
		return;
	}
	//delete the old batch and create a new batch
	cleanBatchData();
	
	//pointer the the array of GLBatch pointers
	mBatch = new GLBatch*[mBatchCount];
	MeshData *currentMesh;
	for (unsigned int i = 0; i < mBatchCount; i++)
	{
		currentMesh = data.meshList[i];
		mBatch[i] = new GLBatch();
		mBatch[i]->Begin(currentMesh->primitiveMode, currentMesh->vertextCount, 1);
		mBatch[i]->CopyVertexData3f(currentMesh->vertexData);
		mBatch[i]->CopyNormalDataf(currentMesh->normalData);
		mBatch[i]->CopyTexCoordData2f(currentMesh->uvData, 0);
		mBatch[i]->End();
	}
}



//accessors
unsigned int Model::getBatchCount() const
{
	return mBatchCount;
}

//Draw the model by calling all the batch
void Model::Draw()
{
	shaderManager.UseStockShader(GLT_SHADER_SHADED, mvpMatrix);
	
	for (int i = 0; i < mBatchCount; i++)
	{
		mBatch[i]->Draw();
	}
}*/
