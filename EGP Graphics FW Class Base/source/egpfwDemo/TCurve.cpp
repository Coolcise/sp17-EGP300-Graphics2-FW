#include "TCurve.h"
#include <iostream>
#include "egpfw/egpfw.h"
#include "Interpolation.h"


TCurve::TCurve(int windowWidth, int windowHeight)
{
	mPoints.push_back(cbmath::vec2(0.0f, 0.0f));
	mPoints.push_back(cbmath::vec2(1.0f, 1.0f));
	mType = LINE_STRIP;

	mWindowHeight = windowHeight;
	mWindowWidth = windowWidth;
}

void TCurve::addPoint(cbmath::vec2 point)
{
	if (getSize() > TIME_POINTS_MAX) 
	{
		std::cout << "Max time keys reached.\n";
		return;
	}
	float t = point.x / mWindowWidth;
	float val = point.y / mWindowHeight;


	for(auto it = mPoints.begin(); it != mPoints.end(); ++it)
	{
		if (t == (*it).x) 
		{
			*it = cbmath::vec2(t,1 - val);
			break;
		}	

		if(t < (*it).x)
		{
			mPoints.insert(it, cbmath::vec2(t, 1 - val));
			break;
		}
	}
}

void TCurve::reset()
{
	mPoints.clear();
	mPoints.push_back(cbmath::vec2(0.0f, 0.0f));
	mPoints.push_back(cbmath::vec2(1.0f, 1.0f));
}

float TCurve::lineStripDeltaT(float t)
{
	cbmath::vec2 p0, p1;

	//Find beginning and end points
	for (auto it = mPoints.begin(); it != mPoints.end();)
	{
		if (t == (*it).x)
			return (*it).y;

		if (t < (*(++it)).x)
		{
			p1 = *it;
			p0 = *(--it);
			break;
		}
	}

	//Normalized sample time
	float normSampleT = (t - p0.x) / (p1.x - p0.x);

	//lerp between the two points using the normalized sample time
	return egpfwLerp(p0.y, p1.y, normSampleT);
}

//Credits to Charlie McGarey for letting me use this code
float TCurve::bezierDeltaT(float t)
{
	int i = mPoints.size();
	cbmath::vec2* vals = new cbmath::vec2[i];
	
	// Fill the array
	int j = 0;
	for(auto it = mPoints.begin(); it != mPoints.end(); ++it)
	{
		vals[j].x = (*it).x;
		vals[j].y = (*it).y;
		j++;
	}

	// Lerp between each val, recursively
	for (; i > 1; i--)
	{
		for (j = 0; j < i - 1; j++)
		{
			// vals is filled with previous values, replace the first one with the lerped value
			vals[j] = Interpolation::lerp(vals[j], vals[j + 1], t);
			// After each lerp pass there will be one less value to go through, until we eventually reach only one val
		}
	}

	// Grab the value we want
	float val = vals[0].y;
	delete[] vals;
	return val;
}

float TCurve::catmulRomDeltaT(float t)
{
	if (getSize() < 4) return lineStripDeltaT(t);

	int i = 0;

	cbmath::vec2 p0, p1, p2, p3;

	//Find beginning and end points
	for (auto it = mPoints.begin(); it != mPoints.end(); ++it)
	{
		++it;
		//if t == 0 or the t at 0 is p1
		if (t < 0.001f || (i == 0 && t < (*it).x))
		{
			p1 = *--it;
			p2 = *(++it);
			//as there is no actual point before 0.0, I assume it is the same y as p2, and as far away in the negative direction
			p0 = cbmath::vec2(p1.x - p2.x, p2.y);
			p3 = *(++it);
			break;
		}

		--it;
		if(t < (*it).x)
		{
			p2 = *it;
			
			if(i < getSize() - 2)
			{
				p3 = *(++it);
				--it; //p2
				p1 = *(--it);
				p0 = *(--it);
			}
			else
			{
				p1 = *(--it);
				p0 = *(--it);
				//p3 is assumed to be the same y as p1, and as far away as p1 in the positive direction because p2 is the last point (t == 1)
				p3 = cbmath::vec2(p2.x + (p2.x - p1.x), p1.y);
				break;
			}
		}
		i++;
	}

	//clamp and return interpolated y value
	float val = Interpolation::catmullRom(p0, p1, p2, p3, t).y;
	if (val < 0) val = 0;
	else if (val > 1) val = 1;

	return val;
}

float TCurve::cubicHermiteDeltaT(float t)
{
	return t;
}

void TCurve::getData(float* data)
{
	int i = 0;
	for(auto it = mPoints.begin(); it != mPoints.end(); ++it)
	{
		data[i] = (*it).x * mWindowWidth; i++;
		data[i] = (*it).y * mWindowHeight; i++;
		data[i] = 0.0f; i++;
		data[i] = 1.0f; i++;
	}
}

float TCurve::getDeltaT(float t)
{
	if(mType == LINE_STRIP)
		return lineStripDeltaT(t);
	else if (mType == BEZIER)
		return bezierDeltaT(t);
	else if (mType == CATMULL_ROM)
		return catmulRomDeltaT(t);
	else if (mType == CUBIC_HERMITE)
		return cubicHermiteDeltaT(t);

	std::cout << "Could not get deltaT. This should never happen\n";
	return t;
}


