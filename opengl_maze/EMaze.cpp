#include "EMaze.h"

EMaze::EMaze(MazeData* maze) : maze(maze) {}

void EMaze::Render(float screenWidth, float screenHeight)
{
    for (int x = 0; x < maze->GetSize().x; x++) {
        for (int y = 0; y < maze->GetSize().y; y++) {
            RenderCell(maze->GetCellAtPoint(IntTuple{ x,y }));
        }
    }

    //Red quad
    /*glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(-screenWidth / 4.f, -screenHeight / 4.f);
        glVertex2f(screenWidth / 4.f, -screenHeight / 4.f);
        glVertex2f(screenWidth / 4.f, screenHeight / 4.f);
        glVertex2f(-screenWidth / 4.f, screenHeight / 4.f);
    glEnd();*/
}

int EMaze::GetPixelsPerUnit()
{
	return PIXELS_PER_UNIT;
}

int EMaze::GetMazePadding()
{
	return MAZE_PADDING;
}

void EMaze::RenderCell(const MazeCell *mc)
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
		DrawLine(IntTuple{ x1, y1 }, IntTuple{ x2, y2 });
	}
	if (mc->lineLeft) {
		x1 = upperLeftPos.x;
		x2 = x1;
		y1 = upperLeftPos.y;
		y2 = upperLeftPos.y + PIXELS_PER_UNIT;
		DrawLine(IntTuple{ x1, y1 }, IntTuple{ x2, y2 });
	}
	// only draw bottom on bottom row
	if (mc->gridCoord.y == maze->GetSize().x - 1 && mc->lineBottom) {
		x1 = upperLeftPos.x;
		x2 = x1 + PIXELS_PER_UNIT;
		y1 = upperLeftPos.y + PIXELS_PER_UNIT;
		y2 = y1;
		DrawLine(IntTuple{ x1, y1 }, IntTuple{ x2, y2 });
	}
	// only draw right on rightmost column
	if (mc->gridCoord.x == maze->GetSize().y - 1 && mc->lineRight) {
		x1 = upperLeftPos.x + PIXELS_PER_UNIT;
		x2 = x1;
		y1 = upperLeftPos.y;
		y2 = upperLeftPos.y + PIXELS_PER_UNIT;
		DrawLine(IntTuple{ x1, y1 }, IntTuple{ x2, y2 });
	}

    
}

void EMaze::DrawLine(IntTuple p1, IntTuple p2)
{
	glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
	glEnd();
}