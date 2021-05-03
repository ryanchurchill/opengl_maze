#pragma once

#include "Tuple.h"
#include "MazeData.h"

#include <SDL.h>
#include <SDL_opengl.h>

class EPlayer
{
public:
	EPlayer(MazeData* m);

	void ProcessKeypress(SDL_Keycode key);
	void LogicLoop();
	void OnRender();

private:
	void TryMove(Direction d);

	// Bad practice?
	MazeData* maze;

	IntTuple currentGridPoint;
};

