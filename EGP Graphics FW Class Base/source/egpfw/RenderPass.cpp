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

//Class written by Brendon Cote
//Modified by David Horntvedt fixing some bugs
#include "egpfw/egpfw/RenderPass.h"
#include <cstring>


RenderPass::RenderPass()
{
	uniformIntCount = 0;
	uniformFloatCount = 0;
	uniformFloatMatrixCount = 0;
	depthCount = 0;
	colorCount = 0;
	texCount = 0;

	mVAO = nullptr;
}

RenderPass::RenderPass(egpFrameBufferObjectDescriptor * fbo, egpProgram * program)
{
	desiredBuffer = fbo;
	currentProgram = program;
}


RenderPass::~RenderPass()
{
}

//sendstring to load shader into memory
//void RenderPass::loadShaderFromFile(egpShaderType shaderType, const char input[MAX_STRING_LENGTH])
//{
//	//convert to a struct that contains shader type to skip a step later
//	egpFileInfo tempFileInfo = egpLoadFileContents(input);
//	fileInfo[numFiles].contents = (char*)malloc(tempFileInfo.length + 1);
//	strcpy_s(fileInfo[numFiles].contents, tempFileInfo.length + 1, tempFileInfo.contents);
//	//fileInfo[numFiles].contents = tempFileInfo.contents;
//	fileInfo[numFiles].length = tempFileInfo.length;
//	fileInfo[numFiles].type = shaderType;
//	numFiles++;
//
//	egpReleaseFileContents(&tempFileInfo);
//}

// use to set the desired fbo
void RenderPass::setBuffer(egpFrameBufferObjectDescriptor & buffer)
{
	*desiredBuffer = buffer;
}

void RenderPass::addColorTarget(FBOTargetColorTexture & color)
{
	mTexColor[colorCount] = color;
	colorCount++;
}

void RenderPass::addTexture(TextureData & tex)
{
	mTex[texCount] = tex;
	texCount++;
}

void RenderPass::addDepthTarget(FBOTargetDepthTexture & depth)
{
	mTexDepth[depthCount] = depth;
	depthCount++;
}

void RenderPass::addUniform(UniformInt & uniformIndex)
{
	uniformInts[uniformIntCount] = uniformIndex;
	uniformFloatCount++;
}

void RenderPass::addUniform(UniformFloat & uniformIndex)
{
	uniformFloats[uniformFloatCount] = uniformIndex;
	uniformFloatCount++;
}

void RenderPass::addUniform(UniformFloatMatrix & uniformIndex)
{
	uniformFloatMatrix[uniformFloatMatrixCount] = uniformIndex;
	uniformFloatMatrixCount++;
}

//use to add uniforms to the rendered object (are sent in renderpath.draw())
void RenderPass::finalizeUniforms()
{
	for (size_t l = 0; l < colorCount; l++)
	{	
		egpfwBindColorTargetTexture(desiredBuffer + mTexColor[l].fboIndex, mTexColor[l].glBinding, mTexColor[l].targetIndex);
	}

	for (size_t m = 0; m < depthCount; m++)
	{
		egpfwBindDepthTargetTexture(desiredBuffer + mTexDepth[m].fboIndex, mTexDepth[m].glBinding);
	}

	for (size_t i = 0; i < uniformIntCount; i++)
	{
		egpSendUniformInt(uniformInts[i].uniformIndex, uniformInts[i].iType, uniformInts[i].count, uniformInts[i].data);
	}

	for (size_t j = 0; j < uniformFloatCount; j++)
	{
		egpSendUniformFloat(uniformFloats[j].uniformIndex, uniformFloats[j].iType, uniformFloats[j].count, uniformFloats[j].data);
	}

	for (size_t k = 0; k < uniformFloatMatrixCount; k++)
	{
		egpSendUniformFloatMatrix(uniformFloatMatrix[k].uniformIndex, UNIF_MAT4 , uniformFloatMatrix[k].count, uniformFloatMatrix[k].transpose, uniformFloatMatrix[k].data->m);
	}

	for (size_t n = 0; n < texCount; n++)
	{
		glActiveTexture(mTex[n].textureLane);
		glBindTexture(mTex[n].textureType, mTex[n].textureHandle);
	}
}

void RenderPass::setCurrentProgram(int index)
{
	programIndex = index;
}

// use to set the desired FBO index
void RenderPass::setPipelineStage(int stage)
{
	pipelineStage = stage;
}

void RenderPass::setVAO(egpVertexArrayObjectDescriptor* vao)
{
	mVAO = vao;
	hasVAO = true;
}



//call finalize after you are done adjusting components
void RenderPass::finalize()
{
	if (programIndex != MAX_PROGRAMS)
		egpActivateProgram(currentProgram + programIndex);

	//Activate our target FBO (if we have one)
	if (pipelineStage != MAX_FBO)
		egpfwActivateFBO(desiredBuffer + pipelineStage);

	//Activate our target VAO (if we have one)
	if (hasVAO)
		egpActivateVAO(mVAO);
}

