#pragma once

#include "Grid.h"

class Snake
{
private:
	static constexpr int snakeLength = 100;
	Position segments[snakeLength];
	int snakeSize;

public:
	Snake( const Position& initialPos );
	void Draw( Grid& grid ) const;
	void MoveBy( const Position& deltaPos );
	bool IsOutOfGrid_andFix( Position& head );//Fixes if out of grid and returns true, false otherwise
	bool IsColliding( const Position& other ) const;
	void Grow( const Position& deltaPos );
	bool selfCollision();
	bool isSnakeBody(const Position& pos) const;
	bool wentOutOfBounds = false;

/*private:
	class Segment
	{
	private:
		Position pos;
		Color c;


	};

private:
	static constexpr int segmentsLength = 100;
	Segment segments[segmentsLength];
	int segmentsSize = 1;

public:
	Snake(const Position& pos);
	void MoveBy(const Position& deltaPos);
	void Grow();
	void Draw(Grid& grid) const;*/
};

