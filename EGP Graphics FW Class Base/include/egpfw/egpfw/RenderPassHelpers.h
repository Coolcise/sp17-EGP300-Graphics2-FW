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
