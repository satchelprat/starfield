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
	cam(ct),
	camCtl(wnd.mouse, cam)

{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> xDist(-worldWidth / 2.0f, worldWidth / 2.0f);
	std::uniform_real_distribution<float> yDist(-worldHeight / 2.0f, worldHeight / 2.0f);
	std::uniform_real_distribution<float> radOutDist(starOuterRadiusMin, starOuterRadiusMax);
	std::uniform_real_distribution<float> radInDist(starInnerRadiusMin, starInnerRadiusMax);
	std::uniform_real_distribution<float> pulseDist(pulseMin, pulseMax);
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
		const size_t nFlares = flareDist(rng);
		const Color color = colors[colorDist(rng)];
		const float pulse = pulseDist(rng);
		starfield.emplace_back(outRad, inRad, nFlares, pos, color, pulse);
	}  

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
	camCtl.Update();
}

void Game::ComposeFrame()
{
	
	for (auto& e : starfield)
	{
		cam.Draw(e.GetModelPtr(), e.GetDrawable());
	}

}
