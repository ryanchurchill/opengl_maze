#include "OpenGLUtil.h"

bool OpenGLUtil::AreRectanglesColliding(Rect a, Rect b)
{
	//If any of the sides from A are outside of B
	if (a.y2 <= b.y1)
	{
		return false;
	}

	if (a.y1 >= b.y2)
	{
		return false;
	}

	if (a.x2 <= b.x1)
	{
		return false;
	}

	if (a.x1 >= b.x2)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
