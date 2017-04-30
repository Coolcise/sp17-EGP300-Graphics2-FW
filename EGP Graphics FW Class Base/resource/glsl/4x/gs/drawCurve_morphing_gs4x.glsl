/*
	Draw Curve - Morphing
	By Dan Buckstein
	Geometry shader that draws the path that a morphing vertex follows.
	
	Modified by: ______________________________________________________________
*/

#version 410

// ****
#define SAMPLES_MAX 128

// geometry type layout qualifiers
layout (triangles) in;
layout (line_strip, max_vertices = SAMPLES_MAX) out;

// ****
// receive varying data
in vertexdata
{
	vec4 p0;
	vec4 p1;
	vec4 p2;
	vec4 p3;
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


void drawCatmullRomSplineSegment(in vec4 pPrev, in vec4 p0, in vec4 p1, in vec4 pNext, const int samples, const float dt)
{
	float t = 0.0;
	for (int i = 0; i <= samples; i++)
	{
		gl_Position = mvp*sampleCatmullRom(pPrev, p0, p1, pNext, t);
		EmitVertex();
		t += dt;
	}
	EndPrimitive();
}

void main()
{
	// ****
	// do line drawing


	// testing: pass solid color
	passColor = vec4(0.0, 0.5, 1.0, 1.0);

	const int SAMPLES_PER_LINE = SAMPLES_MAX/16;

// DEBUGGING: draw a normal vector for each vertex
	drawCatmullRomSplineSegment(pass[0].p0, pass[0].p1, pass[0].p2, pass[0].p3, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	drawCatmullRomSplineSegment(pass[0].p1, pass[0].p2, pass[0].p3, pass[0].p0, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	drawCatmullRomSplineSegment(pass[0].p2, pass[0].p3, pass[0].p0, pass[0].p1, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	drawCatmullRomSplineSegment(pass[0].p3, pass[0].p0, pass[0].p1, pass[0].p2, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));

	drawCatmullRomSplineSegment(pass[1].p0, pass[1].p1, pass[1].p2, pass[1].p3, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	drawCatmullRomSplineSegment(pass[1].p1, pass[1].p2, pass[1].p3, pass[1].p0, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	drawCatmullRomSplineSegment(pass[1].p2, pass[1].p3, pass[1].p0, pass[1].p1, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	drawCatmullRomSplineSegment(pass[1].p3, pass[1].p0, pass[1].p1, pass[1].p2, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));

	drawCatmullRomSplineSegment(pass[2].p0, pass[2].p1, pass[2].p2, pass[2].p3, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	drawCatmullRomSplineSegment(pass[2].p1, pass[2].p2, pass[2].p3, pass[2].p0, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	drawCatmullRomSplineSegment(pass[2].p2, pass[2].p3, pass[2].p0, pass[2].p1, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	drawCatmullRomSplineSegment(pass[2].p3, pass[2].p0, pass[2].p1, pass[2].p2, SAMPLES_PER_LINE, 1.0f / float(SAMPLES_PER_LINE));
	//drawLineFull(pass[0].p0, pass[0].p1);
	//drawLineFull(pass[0].p1, pass[0].p2);
	//drawLineFull(pass[0].p2, pass[0].p3);
	//drawLineFull(pass[0].p3, pass[0].p0);

	//drawLineFull(pass[1].p0, pass[1].p1);
	//drawLineFull(pass[1].p1, pass[1].p2);
	//drawLineFull(pass[1].p2, pass[1].p3);
	//drawLineFull(pass[1].p3, pass[1].p0);

	//drawLineFull(pass[2].p0, pass[2].p1);
	//drawLineFull(pass[2].p1, pass[2].p2);
	//drawLineFull(pass[2].p2, pass[2].p3);
	//drawLineFull(pass[2].p3, pass[2].p0);
}