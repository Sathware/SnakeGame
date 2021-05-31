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
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	: wnd(wnd), 
	gfx(wnd), 
	grid(gfx), 
	rng(std::random_device()()),
	xDist(0, Grid::getWidth() - 1), 
	yDist(0, Grid::getHeight() - 1),
	snake(Position{ (Grid::getWidth() - 1) / 2, (Grid::getHeight() - 1) / 2 }), 
	reward{ xDist(rng), yDist(rng) }, 
	deltaPos{ 0, 0 }, movementTimer(0), gameEnd(false)
{}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameEnd && gameStart)
	{
		if (snake.IsColliding(reward))
		{
			Position newRewardPos = { xDist(rng), yDist(rng) };
			while (snake.isSnakeBody(newRewardPos))
				newRewardPos = { xDist(rng), yDist(rng) };

			reward = newRewardPos;
			snake.Grow(deltaPos);
		}

		if (wnd.kbd.KeyIsPressed('W') && deltaPos.y != 1)
			deltaPos = { 0, -1 };

		if (wnd.kbd.KeyIsPressed('S') && deltaPos.y != -1)
			deltaPos = { 0, 1 };

		if (wnd.kbd.KeyIsPressed('A') && deltaPos.x != 1)
			deltaPos = { -1, 0 };

		if (wnd.kbd.KeyIsPressed('D') && deltaPos.x != -1)
			deltaPos = { 1, 0 };

		if (movementTimer == timeStep)
		{
			snake.MoveBy(deltaPos);
			movementTimer = 0;
		}
		movementTimer++;
	}
}

void Game::ComposeFrame()
{
	if (gameStart)
	{
		grid.Draw();
		grid.DrawCell(reward, Colors::White);
		snake.Draw(grid);

		if (snake.selfCollision())
		{
			gameEnd = true;
			SpriteCodex::DrawGameOver(375, 250, gfx);
			deltaPos = { 0, 0 };
		}
	}
	else
	{
		SpriteCodex::DrawTitle(300, 200, gfx);
		gameStart = wnd.kbd.KeyIsPressed(VK_RETURN);
	}
}
