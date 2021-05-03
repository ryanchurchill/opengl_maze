#include "EPlayer.h"

EPlayer::EPlayer(MazeData* m) : currentGridPoint(m->GetStartingPoint()), maze(m)
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
}

void EPlayer::TryMove(Direction d)
{
}
