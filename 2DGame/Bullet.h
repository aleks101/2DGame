#pragma once

#include <math.h>
#include "Object.h"
#include "Timer.h"
#include "Physics.h"

class Bullet : public Object, public Timer
{
private:
	Uint32 m_lifeTime;

	const float constantVelocity;
	Vec2 m_velocity;
	Vec2 m_point;
	int m_speedModifier;
public:
	Bullet(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect destPos, SDL_Rect* playerDest, Vec2 screenPos, Vec2 point, float velocity, float damage, int speedModifier, unsigned int lifeTime);
	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }
	void Update();
	void Render();
	void Destroy();
	void Move();
	bool m_alive;
	float m_damage;
};

