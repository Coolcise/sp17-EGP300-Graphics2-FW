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

//Class written by David Horntvedt (looked at James Keats' code for reference with permission)

#include "NetworkOverlayGraph.h"


NetworkOverlayGraph::NetworkOverlayGraph(egpFrameBufferObjectDescriptor* fboDescriptors, egpVertexArrayObjectDescriptor* quadVAO, egpProgram* programArray, int* textureUniformData)
{
	mFBODescriptors = fboDescriptors;
	mQuadVAO = quadVAO;
	mProgramArray = programArray;
	mTextureUniformData = textureUniformData;
}

void NetworkOverlayGraph::addGraphPanel(FBOTargetColorTexture panelFBO)
{
	panelFBO.glBinding = 0;
	mGraphFBOs.push_back(panelFBO);
}

void NetworkOverlayGraph::populateTransforms()
{
	mPanelTransformMats.clear();
	

}

void NetworkOverlayGraph::clearPanels()
{
	mGraphFBOs.clear();
}

void NetworkOverlayGraph::renderGraph()
{
}
