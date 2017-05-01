/*
EGP Graphics Framework
(c) 2017 Dan Buckstein
Interpolation utilities by Dan Buckstein

Modified by: David Horntvedt
*/
//Added a seperate interpolation class in c++ as I could not get the c file to work with cbmath
//All functions are copied from the c file (and populated by me)
#pragma once

namespace cbtk {namespace cbmath {
	union vec2;
}
}

class Interpolation
{
public:
	static float lerp(const float v0, const float v1, const float param);
	static cbtk::cbmath::vec2 lerp(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 p1, const float param);
	
	static float lerpInv(const float v0, const float v1, const float v);
	
	static cbtk::cbmath::vec2 catmullRom(const cbtk::cbmath::vec2 pPrev, const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 p1, const cbtk::cbmath::vec2 pNext, const float t);
	
	static cbtk::cbmath::vec2 cubicHermite(const cbtk::cbmath::vec2 handle0, const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 handle1, const cbtk::cbmath::vec2 p1, const float t);
	
	static cbtk::cbmath::vec2 bezier0(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 param);
	
	static cbtk::cbmath::vec2 bezier1(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 p1, const float param);
	
	static cbtk::cbmath::vec2 bezier2(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 p1, const cbtk::cbmath::vec2 p2, const float param);
	
	static cbtk::cbmath::vec2 bezier3(const cbtk::cbmath::vec2 p0, const cbtk::cbmath::vec2 p1, const cbtk::cbmath::vec2 p2, const cbtk::cbmath::vec2 p3, const float param);
};