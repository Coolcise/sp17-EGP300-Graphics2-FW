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

#pragma once
#include "egpfw\egpfw\utils\egpfwFileUtils.h" // to get egfPileInfo
#include "egpfw\egpfw\utils\egpfwShaderProgramUtils.h" // to get egpShader
#include "egpfw\egpfw\egpfwFrameBuffer.h" // to get fbo
#include "egpfw\egpfw\utils\egpfwVertexBufferUtils.h"
#include <stdlib.h>
#include <GL/glew.h>
//#include "../project/VS2015/egpfwDemoFreeglut/RenderPassHelpers.h"
#include "RenderPassHelpers.h"

const int MAX_FILE_INFO = 8;
const int MAX_PROGRAMS = 16;
const int MAX_FBO = 14;
const unsigned long int MAX_STRING_LENGTH = 100000; //2048 ^2
const int MAX_UNIFORMS = 8;

//Class written by Brandon Cote
//Modified by David Horntvedt fixing some bugs

class RenderPass
{
public:
	egpFrameBufferObjectDescriptor* desiredBuffer;
	egpVertexArrayObjectDescriptor* mVAO = nullptr;

	int programIndex = 0;

	UniformInt uniformInts[MAX_UNIFORMS];
	UniformFloat uniformFloats[MAX_UNIFORMS];
	UniformFloatMatrix uniformFloatMatrix[MAX_UNIFORMS];


	int uniformIntCount = 0;
	int uniformFloatCount = 0;
	int uniformFloatMatrixCount = 0;
	int pipelineStage = 0;

	FBOTargetDepthTexture mTexDepth[MAX_FILE_INFO];
	int depthCount = 0;
	FBOTargetColorTexture mTexColor[MAX_FILE_INFO];
	int colorCount = 0;
	TextureData mTex[MAX_FILE_INFO];
	int texCount = 0;
	egpProgram* currentProgram;

	RenderPass();
	RenderPass(egpFrameBufferObjectDescriptor* fbo, egpProgram* program);
	~RenderPass();
	void finalize();
	//void loadShaderFromFile(egpShaderType shaderType, const char input[MAX_STRING_LENGTH]);
	void setBuffer(egpFrameBufferObjectDescriptor &buffer);
	void addColorTarget(FBOTargetColorTexture& color);
	void addTexture(TextureData& tex);
	void addDepthTarget(FBOTargetDepthTexture& depth);
	void addUniform(UniformInt& uniformIndex);
	void addUniform(UniformFloat& uniformIndex);
	void addUniform(UniformFloatMatrix& uniformIndex);
	void finalizeUniforms();
	void setCurrentProgram(int index);
	void setPipelineStage(int stage);
	void setVAO(egpVertexArrayObjectDescriptor* vao);

private:
	int numFiles = 0;
	bool hasVAO = false;
};

