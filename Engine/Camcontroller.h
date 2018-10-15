#pragma once
#include "Mouse.h"
#include "Camera.h"
//#include "Vec2.h"

class CamController
{
public:
	CamController(Mouse& _mouse, Camera& _cam)
		:
		mouse(_mouse),
		cam(_cam)
	{}
	void Update()
	{
		while (!mouse.IsEmpty())
		{
			const auto e = mouse.Read();
			if (e.GetType() == Mouse::Event::Type::WheelUp)
			{
				cam.SetScale(cam.GetScale() * zoomFactor);
			}
			else if (e.GetType() == Mouse::Event::Type::WheelDown)
			{
				cam.SetScale(cam.GetScale() / zoomFactor);
			}
			else if (e.GetType() == Mouse::Event::Type::LPress) {
				isActive = true;
				oldPos = (Vec2)e.GetPos();
			}
			else if (e.GetType() == Mouse::Event::Type::LRelease) {
				isActive = false;
			}
			if (isActive)
			{
				curPos = (Vec2)mouse.GetPos();
				auto delta = curPos - oldPos;
				delta.x = -delta.x;
				cam.MoveBy(delta / cam.GetScale());
				oldPos = curPos;
			}
		}
	}

private:
	static constexpr float zoomFactor = 1.20f;
	Mouse& mouse;
	Camera& cam;
	Vec2 curPos = { 0.0f, 0.0f };
	Vec2 oldPos = { 0.0f, 0.0f };
	bool isActive = false;
};