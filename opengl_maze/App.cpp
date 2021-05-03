#include "App.h"

App::App()
{
    gWindow = NULL;
    gRenderer = NULL;
    Quit = false;

    gRenderQuad = true;
}

void App::LogicLoop()
{

}

void App::RenderLoop()
{
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Render quad
    if (gRenderQuad)
    {
        //Red quad
        glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(-SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f(SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f);
        glVertex2f(SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
        glVertex2f(-SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f);
        glEnd();
    }

    //Update screen (double buffering, I think)
    SDL_GL_SwapWindow(gWindow);
}

void App::Close()
{
    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void App::ProcessEvent(SDL_Event e)
{
    //User requests quit
    if (e.type == SDL_QUIT)
    {
        Quit = true;
    }
    //Handle keypress with current mouse position
    else if (e.type == SDL_TEXTINPUT)
    {
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        HandleKeys(e.text.text[0], x, y);
    }
}

void App::HandleKeys(unsigned char key, int x, int y)
{
    //Toggle quad
    if (key == 'q')
    {
        gRenderQuad = !gRenderQuad;
    }
}

int App::OnExecute()
{
    //Start up SDL and create window
    if (!Init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //Enable text input (??)
        SDL_StartTextInput();

        // Main Loop
        while (!Quit) {
            // Handle Events on Queue
            SDL_Event e;
            while (SDL_PollEvent(&e) != 0)
            {
                ProcessEvent(e);
            }

            LogicLoop();
            RenderLoop();
        }

        //Disable text input (??)
        SDL_StopTextInput();

        Close();
    }

    return 0;
}

bool App::Init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create context
            gContext = SDL_GL_CreateContext(gWindow);
            if (gContext == NULL)
            {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Use Vsync
                if (SDL_GL_SetSwapInterval(1) < 0)
                {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }

                //Initialize OpenGL
                if (!InitGlHelper())
                {
                    printf("Unable to initialize OpenGL!\n");
                    success = false;
                }
            }
        }
    }

    return success;
}
bool App::InitGlHelper()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

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
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        // "error" will be cryptic without gluErrorString
        printf("Error initializing OpenGL! %s\n", error);
        success = false;
    }

    return true;
}

int main(int argc, char* args[])
{
    App app;
    return app.OnExecute();

    //Maze m = Maze::GetDummyMaze();
    //m.DrawAsAscii();

    //vector<PathSegment> path = PathGenerator().GeneratePath(Point{ 0,0 }, Point{ 3,3 });

    //MazeGenerator mg;
    //Maze m = mg.GenerateMaze();
    //m.DrawAsAscii();

    return 0;
}