#pragma once

#include "CoordinateTransformer.h"
#include "Drawable.h"

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
	void SetScale(float _s)
	{
		scale = _s;
	}
	float GetScale()const
	{
		return scale;
	}
	void Draw(Drawable& dw) 
	{
			dw.Translate(-pos);  //???? Not positive?
			dw.Scale(scale);
			ct.Draw(dw);
	}
private:
	Vec2 pos = { 0.0f, 0.0f };
	float scale = 1.0f;
	CoordinateTransformer& ct;

};