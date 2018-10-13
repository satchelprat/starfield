/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Star.h"
#include <random>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ct(gfx),
	cam(ct)

{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> xDist(-worldWidth / 2.0f, worldWidth / 2.0f);
	std::uniform_real_distribution<float> yDist(-worldHeight / 2.0f, worldHeight / 2.0f);
	std::uniform_real_distribution<float> radOutDist(starOuterRadiusMin, starOuterRadiusMax);
	std::uniform_real_distribution<float> radInDist(starInnerRadiusMin, starInnerRadiusMax);
	std::uniform_int_distribution<size_t> flareDist(starMinFlares, starMaxFlares);
	const Color colors[] = { Colors::Red,Colors::White,Colors::Blue,Colors::Cyan,Colors::Yellow,Colors::Magenta,Colors::Green };
	std::uniform_int_distribution<size_t> colorDist(0, std::end(colors) - std::begin(colors));

	while (starfield.size() < nStars)
	{
		const auto outRad = radOutDist(rng);
		const Vec2 pos = { xDist(rng), yDist(rng) };

		if (

			std::any_of(starfield.begin(), starfield.end(), [&](const StarEntity& s)
		{ return ((s.GetPos() - pos).Len() < s.GetRadius() + outRad);	}))
		{
			continue;
		}

		const auto inRad = radInDist(rng);
		const int nFlares = flareDist(rng);
		const Color color = colors[colorDist(rng)];
		starfield.emplace_back(outRad, inRad, nFlares, pos, color);
	}  


	/*starfield.emplace_back(100.0f, 50.0f, 3, Vec2({ -180.0f, -40.0f }), Colors::Red);
	starfield.emplace_back(90.0f, 30.0f, 4, Vec2({ 0.0f, 160.0f }));
	starfield.emplace_back(70.0f, 50.0f, 5, Vec2({ 0.0f, 0.0f }));
	starfield.emplace_back(100.0f, 20.0f, 6, Vec2({ -200.0f, 200.0f }));
	starfield.emplace_back(60.0f, 40.0f, 7, Vec2({ 0.0f, -200.0f }));
	starfield.emplace_back(120.0f, 10.0f, 8, Vec2({ 300.0f, -100.0f }));
	starfield.emplace_back(100.0f, 50.0f, 9, Vec2({ 200.0f, 100.0f }));*/
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float speed = 50.0f;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		cam.MoveBy({ 0.0f, -speed });
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		cam.MoveBy({ 0.0f, speed });
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		cam.MoveBy({ -speed, 0.0f });
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		cam.MoveBy({ speed, 0.0f });
	}

	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::WheelUp)
		{
			cam.SetScale(cam.GetScale() * 1.20f);
		}
		else if (e.GetType() == Mouse::Event::Type::WheelDown)
		{
			cam.SetScale(cam.GetScale() / 1.20f);
		}
	}
	if (wnd.mouse.LeftIsPressed())
	{
		const Vec2 pointerPos(float(wnd.mouse.GetPosX()), float(-wnd.mouse.GetPosY()));

		cam.MoveTo(pointerPos);  //not right at all, but will return to this
	}
}

void Game::ComposeFrame()
{
	if (wnd.mouse.LeftIsPressed())
	{
		gfx.DrawLine({ 10.0f,10.0f }, (Vec2)wnd.mouse.GetPos(), Colors::Yellow);
	}

	//ct.DrawClosedPolyline(e1.GetPolyLine(), Colors::Green);
	for (auto e : starfield)
	{
		cam.Draw(e.GetDrawable());
	}

}
