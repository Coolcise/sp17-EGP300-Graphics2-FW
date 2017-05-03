/*
	Written by Charlie McGarey with assistance from David Hortvedt and Tyler Chermely
*/

#version 430

// Waypoints*Segments > Verticies
#define WAYPOINTS_MAX 9
#define SAMPLES_PER_SEGMENT 14
#define VERTICES_MAX 128

// Drawing modes
#define LINE_STRIP 0
#define BEZIER 1
#define CATMULL_ROM 2
#define CUBIC_HERMITE 3

layout(points) in;
layout(line_strip, max_vertices = VERTICES_MAX) out;

// uniforms
uniform mat4 mvp;

uniform vec4 waypoint[WAYPOINTS_MAX];
uniform int waypointCount;
uniform vec4 color;
uniform float paramX;
uniform int curveType;

// varyings
out vec4 passColor;


// ****
// LERP
vec4 lerp(in vec4 p0, in vec4 p1, const float t)
{
	return p0 + (p1-p0)*t;
}

// ****
void drawLineFull(in vec4 p0, in vec4 p1)
{
	gl_Position = mvp*p0;
	EmitVertex();
	gl_Position = mvp*p1;
	EmitVertex();
	EndPrimitive();
}

void drawLineStrips()
{
	for (int i = 1; i < waypointCount; i++)
	{
		drawLineFull(waypoint[i-1], waypoint[i]);
	}
}

// Samples CatmullRom
vec4 sampleCatmullRom(in vec4 pPrev, in vec4 p0, in vec4 p1, in vec4 pNext, const float t)
{
	mat4 influence = mat4(pPrev, p0, p1, pNext);
	mat4 MCR = mat4(	0, -1, 2, -1, 
						2, 0, -5, 3,
						0, 1, 4, -3,
						0, 0, -1, 1);
	MCR = transpose(MCR);
	vec4 tVec = vec4(1.0f, t, t*t, t*t*t);

	return 0.5f * influence * MCR * tVec;
}

// Recursion via for loop
vec4 sampleBezier(float t)
{
	int i = waypointCount;
	vec4 vals[WAYPOINTS_MAX] = waypoint;

	for (;i > 1; i--)
	{
		for (int j = 0; j < i - 1; j++)
		{
			vals[j] = lerp(vals[j], vals[j+1], t);
		}
	}
	return vals[0];
}

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

	return (inVecs * kernel * time);
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

void drawBezierCurve(const int samples, const float dt)
{
	float t = 0.0;
	for (int i = 0; i <= samples; i++)
	{
		gl_Position = mvp*sampleBezier(t);
		EmitVertex();
		t += dt;
	}
	EndPrimitive();
}


void drawCatmullRomCurve(const int samples, const float dt)
{
	// If needed to render lines that have less than 3 waypoints - can't use catmull rom
	if (waypointCount < 3)
	{
		drawLineFull(waypoint[0], waypoint[1]);
	}
	else
	{
		vec4 pPrev, p0, p1, pNext;
		// Draw First Segment
		pPrev = waypoint[waypointCount - 2];
		pPrev.x -= waypoint[waypointCount - 1].x;
		p0 = waypoint[0];
		p1 = waypoint[1];
		pNext = waypoint[2];
		drawCatmullRomSplineSegment(pPrev, p0, p1, pNext, samples, dt);


		// Draw In Between Segments
		int last, i0, i1, next;
		last = 0;
		i0 = 1;
		i1 = 2;
		next = 3;
		for (; next < waypointCount; last = i0, i0 = i1, i1 = next, next++)
		{
			pPrev = waypoint[last];
			p0 = waypoint[i0];
			p1 = waypoint[i1];
			pNext = waypoint[next];
			drawCatmullRomSplineSegment(pPrev, p0, p1, pNext, samples, dt);
		}

		// Draw Last Segment
		pPrev = waypoint[waypointCount - 3];
		p0 = waypoint[waypointCount - 2];
		p1 = waypoint[waypointCount - 1];
		pNext = waypoint[1];
		pNext.x += p1.x;
		drawCatmullRomSplineSegment(pPrev, p0, p1, pNext, samples, dt);
	}
}

void drawCubicHermiteSplineSegment(in vec4 p0, in vec4 m0, in vec4 p1, in vec4 m1, const int samples, const float dt)
{
	int i = 0;
	float t = 0.0;

	for(i; i <= samples; i++)
	{
		gl_Position = mvp * sampleCubicHermite(p0, m0, p1, m1, t);
		EmitVertex();
		t += dt;
	}

	EndPrimitive();
}

void drawCubicHermiteCurve(const int samples, const float dt)
{
	if(waypointCount < 4)
	{
		drawLineFull(waypoint[0], waypoint[waypointCount -1]);
		return;
	}
	
	drawCubicHermiteSplineSegment(waypoint[0], waypoint[1], waypoint[2], waypoint[3], samples, dt);
	
	if(waypointCount == 4)
		return;
	else
	{
		for(int i = 2; i < waypointCount - 3; i+=2)
			drawCubicHermiteSplineSegment(waypoint[i], waypoint[i+1], waypoint[i+2], waypoint[i+3], samples, dt);

		if(waypointCount % 2 == 0)
			drawCubicHermiteSplineSegment(waypoint[waypointCount - 4], waypoint[waypointCount - 3], waypoint[waypointCount - 2], waypoint[waypointCount - 1], samples, dt);
		else
			drawCubicHermiteSplineSegment(waypoint[waypointCount - 3], waypoint[waypointCount - 2], waypoint[waypointCount - 1], waypoint[waypointCount - 2], samples, dt);
	}
}

void main()
{
	passColor = color;
	const int samples = SAMPLES_PER_SEGMENT;
	const float dt = 1.0 / float(SAMPLES_PER_SEGMENT);
	switch (curveType)
	{
		case LINE_STRIP:
			drawLineStrips();
			break;
		case BEZIER:
			drawBezierCurve(samples, dt);
			break;
		case CATMULL_ROM:
			drawCatmullRomCurve(samples, dt);
			break;
		case CUBIC_HERMITE:
			drawCubicHermiteCurve(samples, dt);
			break;
		default:
			break;
	}

	// Draw T line
	passColor = vec4(1, 1, 1, 1);
	drawLineFull(vec4(paramX, 0, 0, 1), vec4(paramX, 4000, 0, 1));
}