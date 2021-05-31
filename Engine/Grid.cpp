#include "Grid.h"
#include <cassert>

Grid::Grid(Graphics& graphics)
	: gfx(graphics)
{
}

void Grid::DrawCell(const Position& pos, Color c)
{
	assert(pos.x >= 0 && pos.x < width);
	assert(pos.y >= 0 && pos.y < height);
	gfx.DrawRectDim(pos.x * dimension, pos.y * dimension, dimension, dimension, c);
}

void Grid::DrawCellWithBorder(const Position& pos, Color c, Color borderColor)
{
	assert(pos.x >= 0 && pos.x < width);
	assert(pos.y >= 0 && pos.y < height);
	gfx.DrawRectDim(pos.x * dimension, pos.y * dimension, dimension, dimension, borderColor);
	gfx.DrawRectDim(pos.x * dimension + padding, pos.y * dimension + padding,
		dimension - 2*padding, dimension - 2*padding, c);
}

void Grid::Draw()
{
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			Position pos = { x, y };
			int rgb = ((x + y) % 2) * 25 + 10;
			Color c( rgb , rgb, rgb );
			DrawCellWithBorder(pos, c, Colors::Black);
		}
}
