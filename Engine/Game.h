/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "CoordinateTransformer.h"
#include "Entity.h"
#include "StarEntity.h"
#include "Camera.h"
#include "Camcontroller.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	CoordinateTransformer ct;
	Camera cam; 
	CamController camCtl;
	//std::vector<Entity> entities;
	std::vector<StarEntity> starfield;
	static constexpr int nStars = 400;
	static constexpr float worldWidth = 10000.0f;
	static constexpr float worldHeight = 7500.0f;
	static constexpr float starInnerRadiusMin = 30.0f;
	static constexpr float starInnerRadiusMax = 80.0f;
	static constexpr float starOuterRadiusMin = 50.0f;
	static constexpr float starOuterRadiusMax = 300.0f;
	static constexpr int starMinFlares = 3;
	static constexpr int starMaxFlares = 12;
	static constexpr float pulseMin = 0.25f;
	static constexpr float pulseMax = 1.0f;
	static constexpr float pulseRatio = 0.5f;
		
	/********************************/
	/*  User Variables              */
	/********************************/
};