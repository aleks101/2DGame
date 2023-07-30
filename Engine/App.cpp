#include "App.h"

SDL_Window* App::window = NULL;
SDL_Renderer* App::renderer = NULL;

void App::ApplicationStart(std::string gameName) {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	window = SDL_CreateWindow(gameName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}
void App::ApplicationQuit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
bool App::ApplicationCheckQuit(SDL_Event event) {
	if (event.type == SDL_QUIT) {
		return true;
	}
	return false;
}
void App::ApplicationRender() {
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}