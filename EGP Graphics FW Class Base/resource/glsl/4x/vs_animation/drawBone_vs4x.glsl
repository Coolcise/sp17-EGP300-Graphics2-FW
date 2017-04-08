/*
	Draw Bone
	By Dan Buckstein
	Vertex shader that renders an instanced primitive and adds scale.
	
	Modified by: ______________________________________________________________
*/

#version 410


layout (location = 0) in vec4 position;

uniform mat4 mvp;

#define BONES_MAX 64

// ****
// other uniform data
uniform mat4 bones_world[BONES_MAX];
uniform float boneLengths[BONES_MAX];


void main()
{
	// ****
	// calculate final bone transform
	mat4 bones = bones_world[gl_InstanceID];
	bones[2] *= boneLengths[gl_InstanceID];

	// ****
	// transform by bone transform before MVP
	
	vec4 pos = bones * position;
	gl_Position = mvp * pos;
}