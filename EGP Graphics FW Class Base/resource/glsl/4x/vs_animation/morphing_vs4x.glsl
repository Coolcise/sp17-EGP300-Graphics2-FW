/*
	Morphing
	By Dan Buckstein
	Vertex shader that performs morph target animation.
	
	Modified by: ______________________________________________________________
*/

#version 430
#define KEYFRAME_COUNT 4

// ****
// attributes: one per morphing attribute (e.g. multiple positions)
layout (location = 0) in vec4 p0;
layout (location = 1) in vec4 p1;
layout (location = 2) in vec4 p2;
layout (location = 3) in vec4 p3;

// ****
// uniforms: animation controls
uniform mat4 mvp;
uniform float param;
uniform int index[KEYFRAME_COUNT];

// varying output: solid color
out vec4 passColor;

vec4 lerp(in vec4 p0, in vec4 p1, const float t)
{
	return p0 + (p1-p0)*t;
}

vec4 sampleCatmullRom(in vec4 pPrev, in vec4 p0, in vec4 p1, in vec4 pNext, const float t)
{
	mat4 influence = mat4(pPrev, p0, p1, pNext);
	mat4 MCR = mat4(0, -1, 2, -1, 
						2, 0, -5, 3,
						0, 1, 4, -3,
						0, 0, -1, 1);
	MCR = transpose(MCR);
	vec4 tVec = vec4(1.0f, t, t*t, t*t*t);

	return 0.5f * influence * MCR * tVec;
}

vec4 sampleCubicHermite(in vec4 p0, in vec4 m0, in vec4 p1, in vec4 m1, const float t)
{
	mat4 influence = mat4(p0, m0, p1, m1);
	mat4 MH = mat4(1, 0, 0, 0, 
					0, 1, 0, 0,
					-3, -2, 3, -1,
					2, 1, -2, 1);
	vec4 tVec = vec4(1.0f, t, t*t, t*t*t);

	return influence * MH * tVec;
}

void main()
{

	vec4 p[KEYFRAME_COUNT] = {p0, p1, p2, p3};

	//vec4 position = lerp(p[index[0]], p[index[1]], param);
	vec4 position = sampleCatmullRom(p[index[3]], p[index[0]], p[index[1]], p[index[2]], param);
	//vec4 position = sampleCubicHermite(p[index[0]], p[index[3]], p[index[1]], p[index[2]], param);

	// ****
	// do morphing, transform the correct result before assigning to output
	gl_Position = mvp * position;

	// TESTING: send position as color to give us some variance
	passColor = position*0.5+0.5;
}