#include "LOpenGL.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const int SCREEN_FPS = 60;

bool init();
bool initGl();

void runMainLoop(int val);
void update();
void render();
void handleKeys(unsigned char key, int x, int y);

void update()
{
    
}

void render()
{
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Reset modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Move to center of the screen
    glTranslatef(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f);

    glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f(SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
        glVertex2f(-SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
    glEnd();

    //Update screen
    glutSwapBuffers();
}

void handleKeys(unsigned char key, int x, int y)
{

}

bool init()
{
    //Create OpenGL 2.1 context
    glutInitContextVersion(2, 1);

    //Create Double Buffered Window
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("OpenGL");

    //Do post window/context creation initialization
    if (!initGl())
    {
        printf("Unable to initialize graphics library!\n");
        return 1;
    }

    //Set keyboard handler
    glutKeyboardFunc(handleKeys);

    //Set rendering function
    glutDisplayFunc(render);

    //Set main loop
    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, 0);

    //Start GLUT main loop
    glutMainLoop();

    return 0;
}

bool initGl()
{
    //Set the viewport
    glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

    //Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Save the default modelview matrix
    //glPushMatrix();

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    //Check for error
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        printf("Error initializing OpenGL! %s\n", gluErrorString(error));
        return false;
    }

    return true;
}

void runMainLoop(int val)
{
    //Frame logic
    update();
    render();

    //Run frame one more time
    glutTimerFunc(1000 / SCREEN_FPS, runMainLoop, val);
}

int main(int argc, char* args[])
{
    //Initialize FreeGLUT
    glutInit(&argc, args);
    init();
}