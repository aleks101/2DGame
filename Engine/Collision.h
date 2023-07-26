#pragma once

#include <SDL.h>
#include <iostream>

namespace coll {
	bool CheckCollisionAABB(SDL_Rect A, SDL_Rect B);
	bool CheckCollisionX(SDL_Rect A, SDL_Rect B);
	bool CheckCollisionY(SDL_Rect A, SDL_Rect B);
}