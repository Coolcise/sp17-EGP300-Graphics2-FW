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
#include "egpfw/egpfw/RenderPath.h"


RenderPath::RenderPath()
{
}


RenderPath::~RenderPath()
{

}

// add a pass (queue like functionality)
void RenderPath::addPass(RenderPass pass, int desiredIterations)
{
	passes[count] = pass;
	passIterationCount[count] = desiredIterations;
	count++;
}

// performs draw related calls and dynamically iterates through render passes
void RenderPath::draw()
{
	for (size_t i = 0; i < count; i++)
	{
		passes[i].finalize();
		passes[i].finalizeUniforms();
		egpDrawActiveVAO();
	}
}

//call once done using to clean up all pointers
void RenderPath::cleanup()
{

}
