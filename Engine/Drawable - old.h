#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"

class Drawable {
public:
	Drawable(std::vector<Vec2> _model, Color _c)
		:
		model(std::move(_model)),
		c(_c)
	{}
	void Translate(const Vec2& _translation) 
	{
		translation += _translation;
	}
	void Scale(const float _scale)
	{
		scaleX *= _scale;
		scaleY *= _scale;
		//scale *= _scale;
		translation *= _scale;
	}
	void ScaleIndependent(const float _scaleX, const float _scaleY)
	{
		scaleX *= _scaleX;
		scaleY *= _scaleY;
		translation.x *= _scaleX;
		translation.y *= _scaleY;
	}
	void Render(Graphics& gfx)
	{
		for (auto& v : model)  //here's where we apply the transforms to all vertices
		{
			v.x *= scaleX;
			v.y *= scaleY;
			v += translation;
		}
		gfx.DrawClosedPolyline(model, c);
	}
private:
	std::vector<Vec2> model;
	Vec2 translation = { 0.0f, 0.0f };
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	//float scale = 1.0f;
	Color c;

};