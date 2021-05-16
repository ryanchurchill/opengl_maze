#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

struct Rect
{
	int x1, y1, x2, y2;
};

struct IntTuple {
	int x;
	int y;
};

struct FloatTuple {
	float x;
	float y;
};

class OpenGLUtil
{
public:
	static bool AreRectanglesColliding(Rect, Rect);
	static void DrawCircle(float cx, float cy, float r, int num_segments);
	static void DrawLine(IntTuple p1, IntTuple p2);
};

