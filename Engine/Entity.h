#pragma once

#include "Vec2.h"
#include <vector>

class Entity {

public:
	Entity(std::vector<Vec2> model) : model(std::move(model)) {}
	Vec2 GetPos() const { return pos; }
	void SetPos(const Vec2 &_pos) { pos = _pos; }
	float GetScale() const { return scale; }
	void SetScale(const float _scale) { scale = _scale; }
	void TranslateBy(const Vec2 &offset) { pos += offset; }
	std::vector<Vec2> GetPolyLine() const {
		auto poly = model;
		for (auto &v : poly) {
			v *= scale;
			v += pos;
		}
		return poly;
	}

private:
	float scale = 1.0f;
	Vec2 pos = { 0.0f, 0.0f };
	std::vector<Vec2> model;
};
