#pragma once

#include "Object.h"
#include "Player.h"

class Ammo : public Object
{
private:
	Player* m_player;
public:
	Ammo(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Player* player, int ammo);
	~Ammo();
	void Update();
	void Render();
	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }

	int m_ammo;
	bool m_isAlive;
};

