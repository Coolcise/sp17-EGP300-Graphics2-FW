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


#include "KeyframeEditor.h"
#include <iostream>
#include <iomanip>
#include "egpfw/egpfw.h"

// Simple lerp with floats
float KeyframeEditor::lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

// Same function with vec2s
cbmath::vec2 KeyframeEditor::lerp(cbmath::vec2 a, cbmath::vec2 b, float t)
{
	return a + t * (b - a);
}

// Gets all the keychannel data to be sent to the shader
void KeyframeEditor::getData(int type, float* data)
{
	int i = 0;
	// grab the min and max values
	float min = type < 3 ? POS_MIN_VAL : ROT_MIN_VAL; 
	float max = type < 3 ? POS_MAX_VAL : ROT_MAX_VAL;

	for (auto it = mKeyChannels[type].begin(); it != mKeyChannels[type].end(); ++it)
	{
		data[i] = (*it)->x * mWinWidth;   ++i; // xVal (0-1) * width
		data[i] = (((*it)->y - min)/(max - min)) * mWinHeight;     ++i; // yVal (0-1) normalized between min and max * height
		data[i] = 0.0f;       ++i;
		data[i] = 1.0f;       ++i;
	}
}

// Gets the designated line color (HARDCODED)
cbmath::vec4 KeyframeEditor::getColor(int type)
{
	return mColors[type];
}

// Gets the size of channel (# of keyframes)
int KeyframeEditor::getSize(int type) const
{
	return static_cast<int>(mKeyChannels[type].size());
}

// Gets the value at a specific t using linestrips
float KeyframeEditor::getValLine(KeyType key, const float& t) const
{
	cbmath::vec2* a;
	cbmath::vec2* b;

	// Find the 2 frames we are between
	for (auto it = mKeyChannels[key].begin(); it != mKeyChannels[key].end(); ++it)
	{
		b = *it;
		if ((*it)->x >= t)
		{
			// if we are at the first frame, return the y value
			if (it == mKeyChannels[key].begin())
			{
				return (*it)->y;
			}

			a = *--it; // Get the previous keyframe
			return lerp(a->y , b->y,  (t - a->x)/(b->x - a->x)); // Return a lerp between the values using a normalized T value
		}
	}

	// Should never get here
	printf("WTFWTFWTFWTFWTFWTFWTF\n");
	return -200.0f;
}

// Gets the value at a specific t using Bezier curves
float KeyframeEditor::getValBezier(KeyType key, const float& t) const
{
	int i = static_cast<int>(mKeyChannels[key].size());
	// New/Deleting things kinda sucks but I can't come up with a better solution
	cbmath::vec2* vals = new cbmath::vec2[i];
	
	// Fill the array
	for (int j = 0; j < i; j++)
	{
		vals[j].x = mKeyChannels[key][j]->x;
		vals[j].y = mKeyChannels[key][j]->y;
	}

	// Lerp between each val, recursively
	for (; i > 1; i--)
	{
		for (int j = 0; j < i - 1; j++)
		{
			// vals is filled with previous values, replace the first one with the lerped value
			vals[j] = lerp(vals[j], vals[j + 1], t);
			// After each lerp pass there will be one less value to go through, until we eventually reach only one val
		}
	}

	// Grab the value we want
	float val = vals[0].y;
	delete[] vals;
	return val;
}


// Don't know why this doesnt work - probably going to ask about it in class
float KeyframeEditor::getValCatmullRom(KeyType key, const float& t) const
{
	if (mKeyChannels[key].size() < 3) return (*mKeyChannels[key].begin())->y;

	bool deletePrev, deleteNext;
	deleteNext = deletePrev = false;

	cbmath::vec2* pPrev;
	cbmath::vec2* p0;
	cbmath::vec2* p1;
	cbmath::vec2* pNext;
	std::vector<cbmath::vec2*>::const_iterator p1It, p0It, pPrevIt, pNextIt;
	// Get All Data
	for (auto it = mKeyChannels[key].begin(); it != mKeyChannels[key].end(); ++it)
	{
		p1It = it;
		p1 = *p1It;
		if ((*it)->x >= t)
		{
			// if we are at the first frame, return the y value
			if (it == mKeyChannels[key].begin())
			{
				return (*it)->y;
			}

			p0It = --it; // it = p0It
			p0 = *p0It;
			// These values are guarateed to be good because of the begin check

			// If p0 is the first frame (0, 0), pPrev should be the SECOND to last frame, shifted by the vec (-1, 0)
			// The last frame would be (1, 0), and this would result in p0 and pPrev having the same value AKA some wonky behavior
			if (p0It == mKeyChannels[key].begin())
			{
				pPrevIt = ----mKeyChannels[key].end(); // One -- to get to real values, another to avoid prev and p0 having the same values
				pPrev = new cbmath::vec2((*pPrevIt)->x - 1.0f, (*pPrevIt)->y);
				deletePrev = true;
			}
			else
			{
				pPrevIt = --it;
				pPrev = *pPrevIt;
			}

			pNextIt = p1It;
			++pNextIt;

			if (pNextIt == mKeyChannels[key].end())
			{
				pNextIt = ++mKeyChannels[key].begin();
				deleteNext = true;
				pNext = new cbmath::vec2((*pNextIt)->x + 1.0f, (*pNextIt)->y);
			}
			else
			{
				pNext = *pNextIt;
			}
			break;
		}
	}

	float val = egpfwCatmullRom(pPrev->y, p0->y, p1->y, pNext->y, (t - p0->x) / (p1->x - p0->x));
	if (deleteNext) delete pNext;
	if (deletePrev) delete pPrev;
	return val;
}

float KeyframeEditor::getValCubicHermite(KeyType key, const float& t) const
{
		//Need 4 points to work
		if (mKeyChannels[key].size() < 4) return getValLine(key, t);

		cbmath::vec2 p0, h0, p1, h1;

		//Find beginning and end points
		for (auto it = mKeyChannels[key].begin(); it != mKeyChannels[key].end(); ++it)
		{
			//it t == 0 (with a margin of float errors)
			if (t < 0.001)
			{
				p0 = **it;
				h0 = **++it;
				p1 = **++it;
				h1 = **++it;
				break;
			}

			//t==1 or it is the last point
			if (t > 0.999 || *it == mKeyChannels[key].back())
			{
				p1 = *(mKeyChannels[key].back());

				//Get the last iterator to be able to manipulate it
				it = mKeyChannels[key].end();
				--it;

				//Second to last point is used as handles for both points
				h0 = h1 = **--it;

				p0 = **--it;
				break;
			}


			if (t < (**it).x)
			{
				//Check if next to last. If so make it a handle
				++it;

				if (*it == mKeyChannels[key].back())
				{
					//same as t == 1
					p1 = **it;
					h0 = h1 = **--it;
					p0 = **--it;
					break;
				}

				//revert after checking the above
				--it;

				p0 = **it;
				h0 = **++it;

				//Checking if next is last point
				++it;

				if (*it == mKeyChannels[key].back())
				{
					p1 = **it;
					h1 = **--it;
					break;
				}
				else
				{
					h1 = **it;
					p1 = **--it;
					break;
				}

			}
		}
		float sampleT = (t - p0.x) / (p1.x - p0.x);

		float val = egpfwCubicHermite(p0.y, h0.y, p1.y, h1.y, sampleT);
		if (val < 0) val = 0;
		else if (val > 1) val = 1;

		return val;
}

// Add the keyframes (0, 0) and (1, 0)
void KeyframeEditor::addBaseFrames()
{
	for (int i = 0; i < NUM_KEYTYPES; i++)
	{
		mKeyChannels[i].push_back(new cbmath::vec2(0.0f, 0.0f));
		mKeyChannels[i].push_back(new cbmath::vec2(1.0f, 0.0f));
	}
}

KeyframeEditor::KeyframeEditor(int winWidth, int winHeight)
{
	mWinWidth = winWidth;
	mWinHeight = winHeight;
	for (int i = 0; i < NUM_KEYTYPES; i++)
	{
		mKeyChannels[i] = std::vector<cbmath::vec2*>();
	}
	addBaseFrames();

	// I know it would be great to customize this but our legend is a PNG and making that change with the customization would be obnoxious
	mColors[X_POS] = cbmath::vec4(0, 1, 0, 1);
	mColors[Y_POS] = cbmath::vec4(1, 0, 0, 1);
	mColors[Z_POS] = cbmath::vec4(0, 0, 1, 1);
	mColors[X_ROT] = cbmath::vec4(0, 0.5f, 0, 1);
	mColors[Y_ROT] = cbmath::vec4(0.5f, 0, 0, 1);
	mColors[Z_ROT] = cbmath::vec4(0, 0, 0.5f, 1);

	mCurveType = LINE_STRIP;
}

KeyframeEditor::~KeyframeEditor()
{
	// Delete all the keyframes
	for (int i = 0; i < NUM_KEYTYPES; i++)
	{
		for (auto it = mKeyChannels[i].begin(); it != mKeyChannels[i].end(); ++it)
		{
			delete *it;
		}
		mKeyChannels[i].clear();
	}
}

// Add a keyframe
void KeyframeEditor::addKeyframe(float tVal, float val, KeyType type)
{
	// Can only have 9 keys (helps with the geometry shader)
	if (mKeyChannels[type].size() > MAX_KEYS)
	{
		printf("Reached the Maximum number of Keys!\n");
		return;
	}
	// grab the min and max values
	float min = type < 3 ? POS_MIN_VAL : ROT_MIN_VAL;
	float max = type < 3 ? POS_MAX_VAL : ROT_MAX_VAL;

	// Get the tval
	tVal /= mWinWidth;
	// find the value between the min and max
	val = lerp(min, max, (mWinHeight - val) / mWinHeight);

	for (auto it = mKeyChannels[type].begin(); it != mKeyChannels[type].end(); ++it)
	{
		// If no keyframe exists insert a new one
		if (tVal < (*it)->x)
		{
			mKeyChannels[type].insert(it, new cbmath::vec2(tVal, val));
			return;
		}
		// Otherwise replace the value
		if (tVal == (*it)->x)
		{
			(*it)->y = val;
			return;
		}

	}
	// should never reach this with a keyframe at (1, 0) but just in case
	mKeyChannels[type].push_back(new cbmath::vec2(tVal, val));
}

void KeyframeEditor::switchCurveType(CurveType c)
{
	mCurveType = c;
}

int KeyframeEditor::getCurveType() const
{
	return static_cast<int>(mCurveType);
}

cbmath::mat4 KeyframeEditor::updateModelMatrix(const float& t) const
{
	// Updates the model matrix of the curve object based on the desired curve type
	switch (mCurveType)
	{
	case LINE_STRIP:
		return makeRotateTranslate(
			cbmath::makeRotationEuler3XYZ(getValLine(X_ROT, t), getValLine(Y_ROT, t), getValLine(Z_ROT, t)),
			cbmath::vec3(getValLine(X_POS, t), getValLine(Y_POS, t), getValLine(Z_POS, t)));
	case BEZIER:
		return makeRotateTranslate(
			cbmath::makeRotationEuler3XYZ(getValBezier(X_ROT, t), getValBezier(Y_ROT, t), getValBezier(Z_ROT, t)),
			cbmath::vec3(getValBezier(X_POS, t), getValBezier(Y_POS, t), getValBezier(Z_POS, t)));
	case CATMULL_ROM:
		return makeRotateTranslate(
			cbmath::makeRotationEuler3XYZ(getValCatmullRom(X_ROT, t), getValCatmullRom(Y_ROT, t), getValCatmullRom(Z_ROT, t)),
			cbmath::vec3(getValCatmullRom(X_POS, t), getValCatmullRom(Y_POS, t), getValCatmullRom(Z_POS, t)));
	case CUBIC_HERMITE:
		return makeRotateTranslate(
			cbmath::makeRotationEuler3XYZ(getValCubicHermite(X_ROT, t), getValCubicHermite(Y_ROT, t), getValCubicHermite(Z_ROT, t)),
			cbmath::vec3(getValCubicHermite(X_POS, t), getValCubicHermite(Y_POS, t), getValCubicHermite(Z_POS, t)));
	default:
		return cbmath::mat4();
	}
	
}

void KeyframeEditor::reset()
{
	for (int i = 0; i < NUM_KEYTYPES; i++)
	{
		for (auto it = mKeyChannels[i].begin(); it != mKeyChannels[i].end(); ++it)
		{
			delete *it;
		}
		mKeyChannels[i].clear();
	}
	addBaseFrames();
}
