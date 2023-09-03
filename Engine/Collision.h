#pragma once

#include <SDL.h>
#include <iostream>
#include "Vec2.h"

namespace coll {
	bool CheckCollisionAABB(const SDL_Rect* const A, const SDL_Rect* const B);
	bool CheckCollisionX(const SDL_Rect* const A, const SDL_Rect* const B);
	bool CheckCollisionY(const SDL_Rect* const A, const SDL_Rect* const B);
	bool CheckCollisionPoint(const SDL_Rect* const A, const Vec2 B);
}