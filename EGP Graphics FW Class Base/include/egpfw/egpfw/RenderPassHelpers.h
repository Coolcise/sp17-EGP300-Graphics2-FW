/*
* Authors: Brandon Cote and David Horntvedt
* Course: EGP 300
*
* We certify that this work is
* entirely our own. The assessor of this project may reproduce this project
* and provide copies to other academic staff, and/or communicate a copy of
* this project to a plagiarism-checking service, which may retain a copy of the
* project on its database.
*/

//File written by Brendon Cote

#pragma once
#include "egpfw\egpfw\utils\egpfwFileUtils.h" // to get egfPileInfo
#include "egpfw\egpfw\utils\egpfwShaderProgramUtils.h" // to get egpShader
#include "egpfw\egpfw\egpfwFrameBuffer.h" // to get fbo
#include "egpfw\egpfw\utils\egpfwVertexBufferUtils.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <cbmath/cbtkMatrix.h>

struct FileInfo
{
	char* contents;
	unsigned int length;
	egpShaderType type;
};
struct RenderPassTextureData
{
	GLenum textureType;
	GLuint textureLane;
	GLuint textureHandle;

	RenderPassTextureData(GLenum type, GLuint lane, GLuint handle) : textureType(type), textureLane(lane), textureHandle(handle) {}
};

struct UniformInt
{
	int uniformIndex;
	egpUniformIntType iType;
	int count;
	const int* data;
	//float constructor

	//int constructor
	UniformInt(int index, egpUniformIntType itype, const int theCount, const int* idata)
	{
		uniformIndex = index;
		iType = itype;
		data = idata;
		count = theCount;
	}
	UniformInt() {}
};

struct UniformFloat
{
	int uniformIndex;
	egpUniformFloatType iType;
	int count;
	const float* data;
	//float constructor

	//int constructor
	UniformFloat(int index, egpUniformFloatType itype, const int theCount, const float* idata)
	{
		uniformIndex = index;
		iType = itype;
		data = idata;
		count = theCount;
	}
	UniformFloat() {}
};

struct UniformFloatMatrix
{
	int uniformIndex;
	int count;
	int transpose;
	cbmath::mat4* data;
	//float constructor

	//int constructor
	UniformFloatMatrix(int index, const int theCount, int Transpose, cbmath::mat4* idata)
	{
		uniformIndex = index;
		transpose = Transpose;
		data = idata;
		count = theCount;
	}
	UniformFloatMatrix() {}
};

struct TextureData
{
	GLenum textureType;
	GLuint textureLane;
	GLuint textureHandle;

	TextureData(GLenum type, GLuint lane, GLuint handle) : textureType(type), textureLane(lane), textureHandle(handle) {}
	TextureData() {}
};

struct FBOTargetColorTexture
{
	int fboIndex;
	unsigned int glBinding;
	int targetIndex;

	FBOTargetColorTexture(int f, unsigned int b, int t) : fboIndex(f), glBinding(b), targetIndex(t) {}
	FBOTargetColorTexture() {}
};

struct FBOTargetDepthTexture
{
	int fboIndex;
	unsigned int glBinding;


	FBOTargetDepthTexture(int f, unsigned int b) : fboIndex(f), glBinding(b) {}
	FBOTargetDepthTexture() {};
};
