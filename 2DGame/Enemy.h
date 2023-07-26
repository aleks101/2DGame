#pragma once

#include "Object.h"
#include "AI.h"
#include "Entity.h"

class Enemy : public Object, public AI, public Entity {
public:
	Enemy(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest);
protected:

};