#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include "MazeData.h"

class EMaze
{
public:
	EMaze(MazeData*);
	MazeData* maze;

	void Render(float screenWidth, float screenHeight);

	int GetPixelsPerUnit();
	int GetMazePadding();

private:
	const int PIXELS_PER_UNIT = 40;
	const int MAZE_PADDING = 30;
	
	void RenderCell(const MazeCell *mc, const IntTuple gridPoint);
	void DrawLine(IntTuple p1, IntTuple p2);
};

