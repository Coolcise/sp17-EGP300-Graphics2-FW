#pragma once
#include <list>
#include "KeyframeEditor.h"

class TCurve
{
	std::vector<cbmath::vec2> mPoints;
	CurveType mType;

	int mWindowWidth;
	int mWindowHeight;

	const int TIME_POINTS_MAX = 8;

	const cbmath::vec4 COLOR = cbmath::vec4(1, 0, 0, 1);

public:
	TCurve(int windowWidth, int windowHeight);
	~TCurve(){}

	CurveType getCurveType() const { return mType; }
	void setCurveType(CurveType type) { mType = type; }

	int getSize() const { return static_cast<int>(mPoints.size()); }
	cbmath::vec4 getColor() const  { return COLOR; }

	void getData(float* data);
	float getDeltaT(const float t);

	void addPoint(const cbmath::vec2 point);

	void reset();

	float lineStripDeltaT(const float t);
	float bezierDeltaT(const float t);
	float catmulRomDeltaT(const float t);
	float cubicHermiteDeltaT(const float t);

};
