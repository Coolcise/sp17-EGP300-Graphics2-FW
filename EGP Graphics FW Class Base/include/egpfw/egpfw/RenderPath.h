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
//Modified by David Horntvedt fixing some bugs and making some optimizations
#pragma once
#include "RenderPass.h"
#include "egpfw\egpfw\utils\egpfwVertexBufferUtils.h"
#include "egpfw\egpfw\egpfwFrameBuffer.h"

const int MAX_PASSES = 32;

class RenderPath
{
public:

	RenderPath();
	~RenderPath();

	//add passes in order of desired rendering
	void addPass(RenderPass pass, int desiredIterations = 1);
	
	void draw();
	void cleanup();
	
	RenderPass getPass(int index) { return passes[index]; }

private:
	RenderPass passes[MAX_PASSES];

	int passIterationCount[MAX_PASSES];
	int count = 0;
};

