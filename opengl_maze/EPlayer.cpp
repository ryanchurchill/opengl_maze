#include "EPlayer.h"

EPlayer::EPlayer(IntTuple startingGridPoint, int pixelsPerUnit, int mazePadding)
	: startingGridPoint(startingGridPoint),
	pixelsPerUnit(pixelsPerUnit),
	mazePadding(mazePadding),
	currentPixelPoint(GetPixelPointFromGridPoint(startingGridPoint)),
	speedX(0),
	speedY(0)
{
}

void EPlayer::ProcessKeypress(SDL_Keycode key)
{
	if (key == SDLK_UP) {
		TryMove(UP);
	}
	else if (key == SDLK_RIGHT) {
		TryMove(RIGHT);
	}
	else if (key == SDLK_DOWN) {
		TryMove(DOWN);
	}
	else if (key == SDLK_LEFT) {
		TryMove(LEFT);
	}
}

void EPlayer::ProcessKeyUp(SDL_Keycode key)
{
	// pretty imperfect system :shrug:
	if (key == SDLK_UP || key == SDLK_RIGHT || key == SDLK_DOWN || key == SDLK_LEFT) {
		StopMove();
	}
}

void EPlayer::LogicLoop()
{
	currentPixelPoint.x += speedX;
	currentPixelPoint.y += speedY;
}

void EPlayer::OnRender()
{
	//IntTuple pixelPoint = GetPixelPointFromGridPoint(startingGridPoint);
	int r = (pixelsPerUnit / 2) - 5; // perf: could be factored out
	DrawCircle(currentPixelPoint.x, currentPixelPoint.y, r, 100);
}

void EPlayer::TryMove(Direction d)
{
	//// TODO: validate player still in maze
	switch (d) {
	case UP:
		speedX = 0;
		speedY = -1;
		break;
	case RIGHT:
		speedX = 1;
		speedY = 0;
		break;
	case DOWN:
		speedX = 0;
		speedY = 1;
		break;
	case LEFT:
		speedX = -1;
		speedY = 0;
		break;
	}
	//currentPixelPoint = GetPixelPointFromGridPoint(startingGridPoint);
}

void EPlayer::StopMove()
{
	speedX = 0;
	speedY = 0;
}

// taken from https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl
void EPlayer::DrawCircle(float cx, float cy, float r, int num_segments) {
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
		float x = r * cosf(theta);//calculate the x component 
		float y = r * sinf(theta);//calculate the y component 
		glVertex2f(x + cx, y + cy);//output vertex 
	}
	glEnd();
}

IntTuple EPlayer::GetPixelPointFromGridPoint(IntTuple gridPoint)
{
	int x = gridPoint.x * pixelsPerUnit + mazePadding + (pixelsPerUnit / 2);
	int y = gridPoint.y * pixelsPerUnit + mazePadding + (pixelsPerUnit / 2);
	return IntTuple{ x, y };
}