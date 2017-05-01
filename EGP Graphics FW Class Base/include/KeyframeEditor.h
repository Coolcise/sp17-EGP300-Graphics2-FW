/*
* Authors: Charlie McGarey and David Horntvedt
* Course: EGP 300
*
* We certify that this work is
* entirely our own. The assessor of this project may reproduce this project
* and provide copies to other academic staff, and/or communicate a copy of
* this project to a plagiarism-checking service, which may retain a copy of the
* project on its database.
*/

#pragma once
#include <vector>
#include <cbmath/cbtkMatrix.h>

struct egpProgram;

enum KeyType
{
	X_POS,
	Y_POS,
	Z_POS,
	X_ROT,
	Y_ROT,
	Z_ROT,
	NUM_KEYTYPES
};

enum CurveType
{
	LINE_STRIP,
	BEZIER,
	CATMULL_ROM,
	CUBIC_HERMITE
};

class KeyframeEditor
{
private:
	std::vector<cbmath::vec2*> mKeyChannels[NUM_KEYTYPES];
	cbmath::vec4 mColors[NUM_KEYTYPES];

	int mWinWidth;
	int mWinHeight;

	const int MAX_KEYS = 8;

	CurveType mCurveType;

	const float POS_MAX_VAL = 2.0f;
	const float POS_MIN_VAL = -2.0f;
	const float ROT_MAX_VAL = 3.14159f;
	const float ROT_MIN_VAL = -3.14159f;

	static float lerp(float a, float b, float t);
	static cbmath::vec2 lerp(cbmath::vec2 a, cbmath::vec2 b, float t);

	float getValLine(KeyType key, const float& t) const;
	float getValBezier(KeyType key, const float& t) const;
	float getValCatmullRom(KeyType key, const float& t) const;

	void addBaseFrames();
public:
	KeyframeEditor(int winWidth, int winHeight);
	virtual ~KeyframeEditor();

	void addKeyframe(float tVal, float val, KeyType type);

	void switchCurveType(CurveType c);
	int getCurveType() const;

	void getData(int type, float* data);
	cbmath::vec4 getColor(int type);
	int getSize(int type) const;

	cbmath::mat4 updateModelMatrix(const float& t) const;

	void reset();
};