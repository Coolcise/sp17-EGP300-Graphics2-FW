/*
	Draw Curve - Morphing
	By Dan Buckstein
	Geometry shader that draws the path that a morphing vertex follows.
	
	Modified by: ______________________________________________________________
*/

#version 410

// ****
#define SAMPLES_MAX 128
#define SAMPLES_PER_SEGMENT 8


// geometry type layout qualifiers
layout (triangles) in;
layout (line_strip, max_vertices = SAMPLES_MAX) out;

// ****
// receive varying data
in vertexdata
{
	vec4 position0;
	vec4 position1;
	vec4 position2;
	vec4 position3;
} pass[];

// uniforms
uniform mat4 mvp;

// varying output: solid color
out vec4 passColor;


void drawLineFull(in vec4 p0, in vec4 p1)
{
	gl_Position = mvp * p0;
	EmitVertex();
	gl_Position = mvp * p1;
	EmitVertex();
	EndPrimitive();
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
// draw Catmull-Rom spline segment
void drawCatmullRomSplineSegment(in vec4 pPrev, in vec4 p0, in vec4 p1, in vec4 pNext, const int samples, const float dt)
{
	int i = 0;
	float t = 0.0;

	for(i; i <= samples; i++)
	{
		gl_Position = mvp * sampleCatmullRom(pPrev, p0, p1, pNext, t);
		EmitVertex();
		t += dt;
	}

	EndPrimitive();
}

void main()
{
	// ****
	// do line drawing

	const float dt = 1.0 / float(SAMPLES_PER_SEGMENT);

	// testing: pass solid color
	passColor = vec4(0.0, 0.5, 1.0, 1.0);


// DEBUGGING: draw a normal vector for each vertex
	const vec4 n = vec4(0.0, 0.0, 1.0, 0.0);
	
	//for(int i = 0; i < 3; i++)
	//{
	//	drawLineFull(pass[i].position0, pass[i].position1);
	//	drawLineFull(pass[i].position1, pass[i].position2);
	//	drawLineFull(pass[i].position2, pass[i].position3);
	//	drawLineFull(pass[i].position3, pass[i].position0);
	//}

	for(int i = 0; i < 3; i++)
	{
		drawCatmullRomSplineSegment(pass[i].position0, pass[i].position1, pass[i].position2, pass[i].position3, SAMPLES_PER_SEGMENT, dt);
		drawCatmullRomSplineSegment(pass[i].position1, pass[i].position2, pass[i].position3, pass[i].position0, SAMPLES_PER_SEGMENT, dt);
		drawCatmullRomSplineSegment(pass[i].position2, pass[i].position3, pass[i].position0, pass[i].position1, SAMPLES_PER_SEGMENT, dt);
		drawCatmullRomSplineSegment(pass[i].position3, pass[i].position0, pass[i].position1, pass[i].position2, SAMPLES_PER_SEGMENT, dt);
	}

}