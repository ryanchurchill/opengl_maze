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
};

