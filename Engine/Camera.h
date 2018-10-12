#pragma once

#include "CoordinateTransformer.h"

class Camera
{
public:
	Camera(CoordinateTransformer& _ct)
		: ct(_ct)
	{}
	Vec2 GetPos() const
	{
		return pos;
	}
	void MoveBy(const Vec2& offset)
	{
		pos += offset;
	}
	void MoveTo(const Vec2& _pos)
	{
		pos = _pos;
	}
	void DrawClosedPolyline(std::vector<Vec2> poly, Color c) {
	
		for (auto &v : poly) {
			
			v -= pos;
		}
		ct.DrawClosedPolyline(std::move(poly), c);
	}
private:
	Vec2 pos = { 0.0f, 0.0f };
	CoordinateTransformer& ct;

};