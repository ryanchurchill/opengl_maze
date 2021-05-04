#include "EPlayer.h"

EPlayer::EPlayer(MazeData* m, int pixelsPerUnit, int mazePadding)
	: currentGridPoint(m->GetStartingPoint()), maze(m), pixelsPerUnit(pixelsPerUnit), mazePadding(mazePadding)
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

void EPlayer::LogicLoop()
{
}

void EPlayer::OnRender()
{
	IntTuple pixelPoint = GetPixelPointFromGridPoint(currentGridPoint);
	int r = (pixelsPerUnit / 2) - 5;
	DrawCircle(pixelPoint.x, pixelPoint.y, r, 100);
}

void EPlayer::TryMove(Direction d)
{
	// TODO: validate player still in maze
	switch (d) {
	case UP:
		if (!(maze->GetCellAtPoint(currentGridPoint)->lineTop)) {
			currentGridPoint.y--;
		}
		break;
	case RIGHT:
		if (!(maze->GetCellAtPoint(currentGridPoint)->lineRight)) {
			currentGridPoint.x++;
		}
		break;
	case DOWN:
		if (!(maze->GetCellAtPoint(currentGridPoint)->lineBottom)) {
			currentGridPoint.y++;
		}
		break;
	case LEFT:
		if (!(maze->GetCellAtPoint(currentGridPoint)->lineLeft)) {
			currentGridPoint.x--;
		}
		break;
	}
}

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