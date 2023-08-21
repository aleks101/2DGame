#pragma once

#include "Object.h"
#include "Player.h"

class Collectable : public Object
{
private:
	Player* m_player;
public:
	Collectable(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Player* player, int ammo, float health, float score);
	~Collectable();
	void Update();
	void Render();
	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }

	int m_ammo;
	float m_health;
	float m_score;
	bool m_isAlive;
};

