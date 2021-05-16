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

// taken from https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
void OpenGLUtil::DrawCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

void OpenGLUtil::DrawLine(IntTuple p1, IntTuple p2)
{
	glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
	glEnd();
}