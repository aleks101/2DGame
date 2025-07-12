#pragma once

#include "Entity.h"
#include "Timer.h"
#include "Ray.h"
#include "Bullet.h"

class EnemyTurret : public Entity
{
private:
	Bullet** m_bullets;
	float m_shootDelay;
	float m_shootCycle;
	float m_bulletDamage;
	float m_bulletSpeed;
	float m_attackRadius;
	bool m_attackCycleReady;

	bool m_hasTimerStarted;
	bool m_hasTimerStopped;
	Timer m_timer;
	Timer m_timer2;
public:
	EnemyTurret(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Entity* player, float health, Map* map, float attackRadius, float shootDelay, float shootCycleDelay, float bulletDamage, float bulletSpeed, float score);
	~EnemyTurret();

	SDL_Rect* GetDest();
	SDL_Rect* GetSrc();
	SDL_Rect* GetScreen();
	void Render();
	void Update();

	void Attack();
	bool IsPointInRadius(Vec2 centerPoint, Vec2 randomPoint, float radius);
	bool IsPathBlocked();
};

