#pragma once

#include "Entity.h"
#include "Bullet.h"
#include "Weapon.h"
#include "Light.h"

class Player : public Entity
{
private:
	bool m_right = false, m_left = false, m_up = false, m_down = false;
	int m_xMouse, m_yMouse;
	int m_xClick, m_yClick;
	int m_attackRange;
	const float m_speed = 5;

	SDL_Event* m_ev;
	Light m_light;
public:
	Weapon<15>* m_gun;
public:
	Player(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest, float health);
	~Player();
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

