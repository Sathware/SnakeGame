#pragma once

#include "Graphics.h"
#include "Position.h"


class Grid
{
private:
	static constexpr int dimension = 10;
	static constexpr int width = 800 / dimension;
	static constexpr int height = 600 / dimension;
	Graphics& gfx;
	static constexpr int padding = 1;

public:
	Grid(Graphics& graphics);
	void DrawCell(const Position& pos, Color c);
	void DrawCellWithBorder(const Position& pos, Color c, Color borderColor);
	static int getWidth() { return width; }
	static int getHeight() { return height; }
	static int getDimension() { return dimension; }
	void Draw();
};

