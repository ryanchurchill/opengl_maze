#pragma once

#include "MazeData.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include "OpenGLUtil.h"

class EPlayer
{
public:
	EPlayer(IntTuple startingGridPoint, int pixelsPerUnit, int mazePadding);

	void ProcessKeypress(SDL_Keycode key);
	void ProcessKeyUp(SDL_Keycode key);
	void LogicLoop(vector<Rect> colliders);
	void OnRender();

private:
	int pixelsPerUnit;
	int mazePadding;
	float radius;

	float speedX;
	float speedY;
	// TODO: consider supporting movement in multiple directions
	Direction moveAttemptDirection = INVALID;
	Direction facingDirection = RIGHT;

	// Bad practice?
	//MazeData* maze;

	IntTuple startingGridPoint;
	IntTuple currentPixelPoint;

	void DrawCircle(float cx, float cy, float r, int num_segments);

	IntTuple GetPixelPointFromGridPoint(IntTuple gridPoint);
	void TryMove(Direction d);
	void StopMove();
	bool WouldCollide(IntTuple targetPoint, vector<Rect> colliders);
	bool WouldCollide(IntTuple targetPoint, Rect collider);
};

