#include "EMaze.h"

EMaze::EMaze(MazeData* maze, int screenWidth, int screenHeight) : maze(maze), screenWidth(screenWidth), screenHeight(screenHeight) {
	GenerateColliders();
}

int EMaze::GetPixelsPerUnit()
{
	return PIXELS_PER_UNIT;
}

int EMaze::GetMazePadding()
{
	return MAZE_PADDING;
}

void EMaze::GenerateColliders()
{
	for (int x = 0; x < maze->GetSize().x; x++) {
		for (int y = 0; y < maze->GetSize().y; y++) {
			GenerateColliders(maze->GetCellAtPoint(IntTuple{ x,y }));
		}
	}
}

void EMaze::GenerateColliders(const MazeCell* mc)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	IntTuple upperLeftPos{ mc->gridCoord.x * PIXELS_PER_UNIT + MAZE_PADDING, mc->gridCoord.y * PIXELS_PER_UNIT + MAZE_PADDING };
	// always draw top and left
	if (mc->lineTop) {
		x1 = upperLeftPos.x;
		x2 = x1 + PIXELS_PER_UNIT;
		y1 = upperLeftPos.y;
		y2 = y1;
		//colliders.push_back(SDL_Rect{ x1, y1, PIXELS_PER_UNIT, 1 });
		colliders.push_back(Rect{ x1, y1, x2, y2 });
	}
	if (mc->lineLeft) {
		x1 = upperLeftPos.x;
		x2 = x1;
		y1 = upperLeftPos.y;
		y2 = upperLeftPos.y + PIXELS_PER_UNIT;
		//colliders.push_back(SDL_Rect{ x1, y1, 1, PIXELS_PER_UNIT });
		colliders.push_back(Rect{ x1, y1, x2, y2 });
	}
	// only draw bottom on bottom row
	if (mc->gridCoord.y == maze->GetSize().x - 1 && mc->lineBottom) {
		x1 = upperLeftPos.x;
		x2 = x1 + PIXELS_PER_UNIT;
		y1 = upperLeftPos.y + PIXELS_PER_UNIT;
		y2 = y1;
		//colliders.push_back(SDL_Rect{ x1, y1, PIXELS_PER_UNIT, 1 });
		colliders.push_back(Rect{ x1, y1, x2, y2 });
	}
	// only draw right on rightmost column
	if (mc->gridCoord.x == maze->GetSize().y - 1 && mc->lineRight) {
		x1 = upperLeftPos.x + PIXELS_PER_UNIT;
		x2 = x1;
		y1 = upperLeftPos.y;
		y2 = upperLeftPos.y + PIXELS_PER_UNIT;
		//colliders.push_back(SDL_Rect{ x1, y1, 1, PIXELS_PER_UNIT });
		colliders.push_back(Rect{ x1, y1, x2, y2 });
	}
}

void EMaze::Render()
{
	for (const Rect &collider : colliders) {
		//glRectd(collider.x1, collider.y1, collider.x2, collider.y2);
		OpenGLUtil::DrawLine(IntTuple{ collider.x1, collider.y1 }, IntTuple{ collider.x2, collider.y2 });
	}
}

vector<Rect> EMaze::GetColliders()
{
	return colliders;
}
