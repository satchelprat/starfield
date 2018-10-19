#pragma once

#include "Vec2.h"
#include <vector>

class Entity {

public:
	Entity(std::vector<Vec2> model, const Vec2 _pos = { 0.0f, 0.0f }, Color _c = Colors::Yellow)
		:
		model(std::move(model)),
		pos(_pos),
		c(_c)
	{}
	Vec2 GetPos() const 
	{ 
		return pos;
	}

	void SetPos(const Vec2 &_pos) 
	{ 
		pos = _pos;
	}

	float GetScale() const 
	{ 
		return scale;
	}

	void SetScale(const float _scale) 
	{ 
		scale = _scale;
	}

	std::vector<Vec2> GetModel() const
	{
		return model;
	}

	std::vector<Vec2>* GetModelPtr()
	{
		return &model;
	}

	void TranslateBy(const Vec2 &offset) 
	{ 
		pos += offset;
	}

	Drawable GetDrawable() const
	{
		Drawable dw(c);
		dw.Scale(scale);
		dw.Translate(pos);
		return dw;
	}
	
private:
	float scale = 1.0f;
	Vec2 pos = { 0.0f, 0.0f };
	std::vector<Vec2> model;
	Color c;
};
