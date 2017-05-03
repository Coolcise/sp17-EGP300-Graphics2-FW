// By Dan Buckstein
// Modified by: David Horntvedt
#include "egpfw/egpfw/egpfwInterpolation.h"


#include <math.h>


// ****
// lerp and lerp inverse
float egpfwLerp(const float v0, const float v1, const float param)
{
	return (v0 + (v1 - v0) * param);
}

// ****
float egpfwLerpInv(const float v0, const float v1, const float v)
{
	return (1.0f / ((v1 - v0) * v));
}


// ****
// Catmull-Rom spline interpolation
float egpfwCatmullRom(const float vPrev, const float v0, const float v1, const float vNext, const float t)
{
	float t2 = t*t;
	float t3 = t*t*t;

	//From powerpoint (kt -> kernel * time)
	float kt1 = -t + 2 * t2 - t3;
	float kt2 = 2 - 5 * t2 + 3 * t3;
	float kt3 = t + 4 * t2 - 3 * t3;
	float kt4 = -t2 + t3;

	float result = kt1 * vPrev + kt2 * v0 + kt3 * v1 + kt4 * vNext;

	return result * 0.5f;
}


// ****
// Cubic hermite spline interpolation
float egpfwCubicHermite(const float v0, const float dv0, const float v1, const float dv1, const float t)
{
	float t2 = t*t;
	float t3 = t*t*t;

	//From powerpoint (kt -> kernel * time)
	float kt1 = 1 - 3 * t2 + 2 * t3;
	float kt2 = t - 2 * t2 + t3;
	float kt3 = 3 * t2 - 2 * t3;
	float kt4 = -t2 + t3;

	float result = kt1 * v0 + kt2 * dv0 + kt3 * v1 + kt4 * dv1;

	return result;
}


// Bezier spline interpolation
float egpfwBezier0(const float v0, const float param)
{
	// this function is complete!
	return v0;
}

// ****
float egpfwBezier1(const float v0, const float v1, const float param)
{
	return egpfwLerp(v0, v1, param);
}

// ****
float egpfwBezier2(const float v0, const float v1, const float v2, const float param)
{
	float lerp0 = egpfwLerp(v0, v1, param);
	float lerp1 = egpfwLerp(v1, v2, param);

	return egpfwLerp(lerp0, lerp1, param);
}

// ****
float egpfwBezier3(const float v0, const float v1, const float v2, const float v3, const float param)
{
	float lerp0 = egpfwLerp(v0, v1, param);
	float lerp1 = egpfwLerp(v1, v2, param);
	float lerp2 = egpfwLerp(v2, v3, param);

	float lerp01 = egpfwLerp(lerp0, lerp1, param);
	float lerp12 = egpfwLerp(lerp1, lerp2, param);

	return egpfwLerp(lerp01, lerp12, param);
}

// ****
float egpfwBezier4(const float v0, const float v1, const float v2, const float v3, const float v4, const float param)
{
	//...
	return 0.0f;
}

// ****
float egpfwBezier(const float *v, unsigned int order, const float param)
{
	//...
	return 0.0f;
}


// ****
// vector interpolation
void egpfwLerpVector(const float *v0, const float *v1, const float param, const unsigned int numElements, float *v_out)
{
	//...
}

// ****
void egpfwCatmullRomVector(const float *vPrev, const float *v0, const float *v1, const float *vNext, const float param, const unsigned int numElements, float *v_out)
{
	//...
}

// ****
void egpfwCubicHermiteVector(const float *v0, const float *dv0, const float *v1, const float *dv1, const float param, const unsigned int numElements, float *v_out)
{
	//...
}

// ****
void egpfwBezierVector(const float *v, unsigned int order, const float param, const unsigned int numElements, float *v_out)
{
	//...
}


// ****
// table sampling
unsigned int egpfwSearchSampleTable(const float *sampleTable, const float *paramTable, const float searchParam, unsigned int numElements, float *param_out)
{
	//...
	return 0;
}


// ****
// calculate arc length
float egpfwComputeArcLengthCatmullRom(const float *vPrev, const float *v0, const float *v1, const float *vNext, unsigned int numElements, unsigned int numSamples, int autoNormalize, float *prevSamplePtr, float *currentSamplePtr, float *sampleTable_out, float *paramTable_out)
{
	//...
	return 0.0f;
}

// ****
float egpfwComputeArcLengthCubicHermite(const float *v0, const float *dv0, const float *v1, const float *dv1, unsigned int numElements, unsigned int numSamples, int autoNormalize, float *prevSamplePtr, float *currentSamplePtr, float *sampleTable_out, float *paramTable_out)
{
	//...
	return 0.0f;
}

// ****
float egpfwComputeArcLengthBezier(const float *v, unsigned int order, unsigned int numElements, unsigned int numSamples, int autoNormalize, float *prevSamplePtr, float *currentSamplePtr, float *sampleTable_out, float *paramTable_out)
{
	//...
	return 0.0f;
}
