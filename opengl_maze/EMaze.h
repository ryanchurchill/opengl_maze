#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include "MazeData.h"
#include "OpenGLUtil.h"

class EMaze
{
public:
	EMaze(MazeData*, int screenWidth, int screenHeight);
	MazeData* maze;

	void Render();

	int GetPixelsPerUnit();
	int GetMazePadding();

	vector<Rect> GetColliders();

private:
	const int PIXELS_PER_UNIT = 40;
	const int MAZE_PADDING = 30;

	int screenWidth;
	int screenHeight;
	
	void DrawLine(IntTuple p1, IntTuple p2);

	void GenerateColliders();
	void GenerateColliders(const MazeCell* mc);
	vector<Rect> colliders;
};

