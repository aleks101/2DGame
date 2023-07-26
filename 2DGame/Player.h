#pragma once

#include "Object.h"
#include "Bullet.h"

class Player : public Object
{
private:
	int m_xSpeed;
	int m_ySpeed;
	bool m_right = false, m_left = false, m_up = false, m_down = false;
	int m_xMouse, m_yMouse;
	int m_xClick, m_yClick;
	int m_attackRange;

	Bullet* m_bullets[30];
	SDL_Event* m_ev;
public:
	Player(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest);
	void Update();
	void Render();

	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }
	std::vector<Bullet*> GetBullets();

	void Move();
	bool CheckForAttack();
	void Attack();
};

