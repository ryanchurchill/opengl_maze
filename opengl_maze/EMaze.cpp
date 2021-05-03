#include "EMaze.h"

EMaze::EMaze(MazeData* maze) : maze(maze) {}

void EMaze::Render(float screenWidth, float screenHeight)
{
    //Red quad
    glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(-screenWidth / 4.f, -screenHeight / 4.f);
        glVertex2f(screenWidth / 4.f, -screenHeight / 4.f);
        glVertex2f(screenWidth / 4.f, screenHeight / 4.f);
        glVertex2f(-screenWidth / 4.f, screenHeight / 4.f);
    glEnd();
}