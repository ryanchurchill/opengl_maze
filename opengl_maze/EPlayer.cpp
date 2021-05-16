#include "EPlayer.h"

EPlayer::EPlayer(IntTuple startingGridPoint, int pixelsPerUnit, int mazePadding)
	:
	//startingGridPoint(startingGridPoint),
	startingGridPoint(IntTuple{ 0,0 }),
	pixelsPerUnit(pixelsPerUnit),
	mazePadding(mazePadding),
	currentPixelPoint(GetPixelPointFromGridPoint(this->startingGridPoint)),
	speedX(0),
	speedY(0)
{
	radius = (pixelsPerUnit / 2) - 5;
}

void EPlayer::LogicLoop(vector<Rect> colliders)
{
	IntTuple targetPoint{ currentPixelPoint.x + speedX, currentPixelPoint.y + speedY };
	if (WouldCollide(targetPoint, colliders)) {
		speedX = 0;
		speedY = 0;
		return;
	}

	currentPixelPoint = targetPoint;
}

bool EPlayer::WouldCollide(IntTuple targetPoint, vector<Rect> colliders)
{
	for (auto it = colliders.begin(); it != colliders.end(); it++) {
		if (WouldCollide(targetPoint, *it)) {
			return true;
		}
	}
	return false;
}

bool EPlayer::WouldCollide(IntTuple targetPoint, Rect collider)
{
	Rect playerCollider{ targetPoint.x - radius, targetPoint.y - radius, targetPoint.x + radius, targetPoint.y + radius };

	return OpenGLUtil::AreRectanglesColliding(collider, playerCollider);
}

void EPlayer::OnRender()
{
	OpenGLUtil::DrawCircle(currentPixelPoint.x, currentPixelPoint.y, radius, 100);

	// Draw Mouth
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
	// system seems a bit better now, but i'm winging it
	if ((key == SDLK_UP && moveAttemptDirection == UP)
		|| (key == SDLK_RIGHT && moveAttemptDirection == RIGHT)
		|| (key == SDLK_DOWN && moveAttemptDirection == DOWN)
		|| (key == SDLK_LEFT && moveAttemptDirection == LEFT)
	) {
		StopMove();
	}
}

void EPlayer::TryMove(Direction d)
{
	//// TODO: validate player still in maze
	switch (d) {
	case UP:
		moveAttemptDirection = UP;
		facingDirection = UP;
		speedX = 0;
		speedY = -1;
		break;
	case RIGHT:
		moveAttemptDirection = RIGHT;
		facingDirection = RIGHT;
		speedX = 1;
		speedY = 0;
		break;
	case DOWN:
		moveAttemptDirection = DOWN;
		facingDirection = DOWN;
		speedX = 0;
		speedY = 1;
		break;
	case LEFT:
		moveAttemptDirection = LEFT;
		facingDirection = LEFT;
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

IntTuple EPlayer::GetPixelPointFromGridPoint(IntTuple gridPoint)
{
	int x = gridPoint.x * pixelsPerUnit + mazePadding + (pixelsPerUnit / 2);
	int y = gridPoint.y * pixelsPerUnit + mazePadding + (pixelsPerUnit / 2);
	return IntTuple{ x, y };
}