#include "Snake.h"
#include <cassert>

Snake::Snake(const Position& initialPos)
	: segments{ initialPos }, snakeSize(1)
{
}

void Snake::Draw(Grid& grid) const
{
	for (int i = 0; i < snakeSize; i++)
		grid.DrawCell(segments[i], Color(150 * i / snakeSize, 255 - 255 * i / snakeSize, 0));
}

bool Snake::IsOutOfGrid_andFix(Position& head)
{
	if (head.x < 0)
	{
		head.x = 0;
		return true;
	}
	if (head.x > Grid::getWidth() - 1)
	{
		head.x = Grid::getWidth() - 1;
		return true;
	}
	if (head.y < 0)
	{
		head.y = 0;
		return true;
	}
	if (head.y > Grid::getHeight() - 1)
	{
		head.y = Grid::getHeight() - 1;
		return true;
	}

	return false;
}

void Snake::MoveBy(const Position& deltaPos)
{
	for (int i = snakeSize - 1; i > 0; --i)
		segments[i] = segments[i - 1];

	segments[0] = { segments[0].x + deltaPos.x, segments[0].y + deltaPos.y };
	wentOutOfBounds = IsOutOfGrid_andFix(segments[0]);
}

bool Snake::IsColliding(const Position& other) const
{
	return segments[0] == other;
}

void Snake::Grow( const Position& deltaPos )
{
	segments[snakeSize] = { segments[snakeSize - 1].x - deltaPos.x, segments[snakeSize - 1].y - deltaPos.y };
	Snake::IsOutOfGrid_andFix( segments[snakeSize] );
	snakeSize++;
}

bool Snake::isSnakeBody(const Position& pos) const
{
	for (int i = 0; i < snakeSize; i++)
		if (segments[i] == pos)
			return true;

	return false;
}

bool Snake::selfCollision()
{
	if (snakeSize == 1)
		return wentOutOfBounds;

	for (int i = 1; i < snakeSize; i++)
		if (IsColliding(segments[i]))
			return true;

	return false;
}

