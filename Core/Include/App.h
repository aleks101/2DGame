#pragma once

#include <iostream>
#include <SDL.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT  720

class App
{
public:
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static void ApplicationStart(std::string gameName);
	static void ApplicationQuit();
	static bool ApplicationCheckQuit(SDL_Event event);
	static void ApplicationRender();
};