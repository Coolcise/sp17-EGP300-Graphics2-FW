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
float egpfwCatmullRom(const float vPrev, const float v0, const float v1, const float vNext, const float param)
{

	return 0.0f;
}


// ****
// Cubic hermite spline interpolation
float egpfwCubicHermite(const float v0, const float dv0, const float v1, const float dv1, const float param)
{
	//...
	return 0.0f;
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
