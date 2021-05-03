#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#include <stdio.h>
#include <string>

class App
{

public:
	App();

	int OnExecute();

	//Starts up SDL, creates window, and initializes OpenGL
	bool Init();

	void LogicLoop();
	void RenderLoop();

	void Close();

private:
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 1000;
	const int SCREEN_FPS = 60;

	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The window renderer
	SDL_Renderer* gRenderer;

	//OpenGL context
	SDL_GLContext gContext;

	// Main Loop flag
	bool Quit;

	bool InitGlHelper();
	void ProcessEvent(SDL_Event e);
	void HandleKeys(unsigned char key, int x, int y);

	bool gRenderQuad;
};
