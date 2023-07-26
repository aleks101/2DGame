#pragma once

#include "Object.h"
#include "AI.h"

class Enemy : public Object, public AI {
public:
	Enemy(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest);
protected:

};