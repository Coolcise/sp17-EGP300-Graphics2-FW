/*
	Morphing
	By Dan Buckstein
	Vertex shader that performs morph target animation.
	
	Modified by: ______________________________________________________________
*/

#version 410


// ****
// attributes: one per morphing attribute (e.g. multiple positions)
layout (location = 0) in vec4 position0;
layout (location = 1) in vec4 position1;
layout (location = 2) in vec4 position2;
layout (location = 3) in vec4 position3;

// ****
// uniforms: animation controls
uniform mat4 mvp;
uniform float param;
uniform int index[4];

// varying output: solid color
out vec4 passColor;

// ****
// LERP
vec4 lerp(in vec4 p0, in vec4 p1, const float t)
{
	return (p0 + (p1 - p0) * t);
}

// ****
// Catmull-Rom spline interpolation
vec4 sampleCatmullRom(in vec4 pPrev, in vec4 p0, in vec4 p1, in vec4 pNext, const float t)
{
	mat4 inVecs;
	inVecs[0] = pPrev;
	inVecs[1] = p0;
	inVecs[2] = p1;
	inVecs[3] = pNext;

	mat4 kernel;
	kernel[0] = vec4(0,  2,  0,  0);
	kernel[1] = vec4(-1, 0,  1,  0);
	kernel[2] = vec4(2,  -5,  4, -1);
	kernel[3] = vec4(-1,  3, -3,  1);


	vec4 time = vec4(1, t, t*t, t*t*t);

	return (0.5f * inVecs * kernel * time);
}

// ****
// cubic Hermite spline interpolation
vec4 sampleCubicHermite(in vec4 p0, in vec4 m0, in vec4 p1, in vec4 m1, const float t)
{
	mat4 inVecs;
	inVecs[0] = p0;
	inVecs[1] = m0;
	inVecs[2] = p1;
	inVecs[3] = m1;

	mat4 kernel;
	kernel[0] = vec4( 1,  0,  0,  0);
	kernel[1] = vec4( 0,  1,  0,  0);
	kernel[2] = vec4(-3, -2,  3, -1);
	kernel[3] = vec4( 2,  1, -2,  1);


	vec4 time = vec4(1, t, t*t, t*t*t);

	return (0.5f * inVecs * kernel * time);
}

vec4 sampleBezier3(in vec4 p0, in vec4 p1, in vec4 p2, in vec4 p3, const float t)
{
	vec4 lerp0 = lerp(p0, p1, t);
	vec4 lerp1 = lerp(p1, p2, t);
	vec4 lerp2 = lerp(p2, p3, t);
	
	vec4 lerp01 = lerp(lerp0, lerp1, t);
	vec4 lerp12 = lerp(lerp1, lerp2, t);

	return lerp(lerp01, lerp12, t);
}

void main()
{

	vec4 p[4];
	p[0] = position0;
	p[1] = position1;
	p[2] = position2;
	p[3] = position3;
	
	vec4 position; 
	//position =	lerp(p[index[0]], p[index[1]], param);
	//position =	lerp(p[index[1]], p[index[2]], param);
	//position =	lerp(p[index[2]], p[index[3]], param);

	position = sampleCatmullRom(p[index[0]], p[index[1]], p[index[2]], p[index[3]], param);
	//position = sampleCubicHermite(p[index[0]], p[index[1]], p[index[2]], p[index[3]], param);
	//position = sampleBezier3(p[index[0]], p[index[1]], p[index[2]], p[index[3]], param);

	

	// ****
	// do morphing, transform the correct result before assigning to output
	gl_Position = mvp * position;


	// TESTING: send position as color to give us some variance
	passColor = position*0.5+0.5;
}