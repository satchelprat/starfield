#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"

class Drawable {
public:
	Drawable(Color _c)
		:
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
	void PRender(std::vector<Vec2>* model, Graphics& gfx)
	{
		for (auto& v : *model)
		{
			v.x *= scaleX;
			v.y *= scaleY;
			v += translation;
		}
		gfx.DrawClosedPolyline(*model, c);
	}
	//void Render(std::vector<Vec2> model, Graphics& gfx)
	//{
	//	for (auto& v : model)  //here's where we apply the transforms to all vertices
	//	{
	//		v.x *= scaleX;
	//		v.y *= scaleY;
	//		v += translation;
	//	}
	//	gfx.DrawClosedPolyline(model, c);
	//}


private:
	
	Vec2 translation = { 0.0f, 0.0f };
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	Color c;

};