#include "Interpolation.h"
#include <cbmath/cbtkMatrix.h>
#include <cbmath/cbtkMathUtils.h>

float Interpolation::lerp(const float v0, const float v1, const float param)
{
	return (v0 + (v1 - v0) * param);
}



float Interpolation::lerpInv(const float v0, const float v1, const float v)
{
	return (1.0f / ((v1 - v0) * v));
}

cbmath::vec2 Interpolation::lerp(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 p1, const float param)
{
	return (p0 + (p1 - p0) * param);

}

// Catmull-Rom spline interpolation
cbmath::vec2 Interpolation::catmullRom(const cbmath::vec2 pPrev, const cbmath::vec2 p0, const cbmath::vec2 p1, const cbmath::vec2 pNext, const float t)
{
	cbmath::mat4 inVecs;
	inVecs.set(
		pPrev.x, p0.x, p1.x, pNext.x,
		pPrev.y, p0.y, p1.y, pNext.y,
		      0,    0,    0,       0,
		      1,    1,    1,       1);
	
	cbmath::mat4 kernel;
	kernel.set(
		0,-1, 2,-1,
		2, 0,-5, 3,
		0, 1, 4,-3,
		0, 0,-1, 1);


	cbmath::vec4 time = cbmath::vec4(1, t, t*t, t*t*t);
	cbmath::vec4 temp = kernel * time;
	temp = inVecs * temp;
	return (0.5f * temp.xy);
}

cbmath::vec2 Interpolation::cubicHermite(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 h0, const cbtk::cbmath::vec2 p1, const cbtk::cbmath::vec2 h1, const float t)
{
	cbmath::mat4 inVecs;
	inVecs.set(
		p0.x, h0.x, p1.x, h1.x,
		p0.y, h0.y, p1.y, h1.y,
		   0,    0,    0,    0,
		   1,    1,    1,    1);

	cbmath::mat4 kernel;
	kernel.set(
		1, 0,-3, 2,
		0, 1,-2, 1,
		0, 0, 3,-2,
		0, 0,-1, 1);


	cbmath::vec4 time = cbmath::vec4(1, t, t*t, t*t*t);

	cbmath::vec4 temp = kernel * time;
	temp = inVecs * temp;
	return (0.5f * temp.xy);
}

// Bezier spline interpolation
cbmath::vec2 Interpolation::bezier0(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 param)
{
	// this function is complete!
	return p0;
}

cbmath::vec2 Interpolation::bezier1(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 p1, const float param)

{
	return lerp(p0, p1, param);
}

cbmath::vec2 Interpolation::bezier2(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 p1, const cbtk::cbmath::vec2 p2, const float param)
{
	cbmath::vec2 lerp0 = lerp(p0, p1, param);
	cbmath::vec2 lerp1 = lerp(p1, p2, param);

	return lerp(lerp0, lerp1, param);
}

cbmath::vec2 Interpolation::bezier3(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 p1, const cbtk::cbmath::vec2 p2, const cbtk::cbmath::vec2 p3, const float param)
{
	cbmath::vec2 lerp0 = lerp(p0, p1, param);
	cbmath::vec2 lerp1 = lerp(p1, p2, param);
	cbmath::vec2 lerp2 = lerp(p2, p3, param);

	cbmath::vec2 lerp01 = lerp(lerp0, lerp1, param);
	cbmath::vec2 lerp12 = lerp(lerp1, lerp2, param);

	return lerp(lerp01, lerp12, param);
}