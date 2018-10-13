#pragma once

#include "Star.h"
#include "Entity.h"
#include "Vec2.h"
#include <vector>

class StarEntity : public Entity
{
public:
	StarEntity(float outerRadius, float innerRadius, int nFlares, const Vec2 _pos = { 0.0f, 0.0f }, Color _c = Colors::Yellow)
		:
		Entity(Star::Make(outerRadius, innerRadius, nFlares), _pos, _c),
		radius(outerRadius)
	{}
	
	float GetRadius() const { return radius; }

private:
	const float radius;

};