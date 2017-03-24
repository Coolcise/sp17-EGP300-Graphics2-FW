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

//Class written by David Horntvedt
#pragma once
#include "egpfwFrameBuffer.h"
#include "utils/egpfwVertexBufferUtils.h"
#include "utils/egpfwShaderProgramUtils.h"
#include "RenderPassHelpers.h"
#include <vector>

class NetworkOverlayGraph
{
private:
	std::vector<FBOTargetColorTexture> mGraphFBOs;
	std::vector<cbmath::mat4> mPanelTransformMats;

	egpFrameBufferObjectDescriptor* mFBODescriptors;
	egpVertexArrayObjectDescriptor* mQuadVAO;
	egpProgram* mProgramArray;
	int* mTextureUniformData;

	void populateTransforms();

public:
	NetworkOverlayGraph(egpFrameBufferObjectDescriptor* fboDescriptors, egpVertexArrayObjectDescriptor* quadVAO, egpProgram* programArray, int* textureUniformData);
	~NetworkOverlayGraph(){}

	void addGraphPanel(FBOTargetColorTexture panelFBO);
	void clearPanels();

	void renderGraph();
};
