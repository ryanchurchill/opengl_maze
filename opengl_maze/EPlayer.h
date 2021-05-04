#pragma once

#include "Tuple.h"
#include "MazeData.h"

#include <SDL.h>
#include <SDL_opengl.h>

class EPlayer
{
public:
	EPlayer(MazeData* m, int pixelsPerUnit, int mazePadding);

	void ProcessKeypress(SDL_Keycode key);
	void LogicLoop();
	void OnRender();

private:
	int pixelsPerUnit;
	int mazePadding;

	// Bad practice?
	MazeData* maze;

	IntTuple currentGridPoint;
	IntTuple currentPixelPoint;

	void DrawCircle(float cx, float cy, float r, int num_segments);

	IntTuple GetPixelPointFromGridPoint(IntTuple gridPoint);
	void TryMove(Direction d);
};

