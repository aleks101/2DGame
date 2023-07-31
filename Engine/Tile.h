#pragma once

#include "Object.h"

class Tile : public Object
{
private:

public:
	Tile(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* player, bool isSolid);
	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }

	void Update();
	void Render();
};

