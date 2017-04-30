/*
	Morphing - Pass Keyframes
	By Dan Buckstein
	Vertex shader that passes keyframes for morphing to geometry shader.
	
	Modified by: ______________________________________________________________
*/

#version 410


// ****
// attributes: one per morphing attribute (e.g. multiple positions)
layout (location = 0) in vec4 p0;
layout (location = 1) in vec4 p1;
layout (location = 2) in vec4 p2;
layout (location = 3) in vec4 p3;

// ****
// varying output: pass all attributes
out vertexdata
{
	vec4 p0;
	vec4 p1;
	vec4 p2;
	vec4 p3;
} pass;

void main()
{
	// ****
	// pass data along
	pass.p0 = p0;
	pass.p1 = p1;
	pass.p2 = p2;
	pass.p3 = p3;

}