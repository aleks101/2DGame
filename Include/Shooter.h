#pragma once

#include "Entity.h"
#include "Bullet.h"
#include "Timer.h"
#include "Ray.h"

#include <cmath>

class Shooter : public Entity
{
private:
	int m_magazine;
	Bullet** m_bullets;
	Uint32 m_shootDelay;
	float m_searchAreaRadius;
	float m_searchPlayerRadius;
	float m_distanceFromPlayerForDodging;
	bool m_isDodging;
	float m_speed;
	float m_bulletSpeed;
	float m_bulletDamage;
	Timer m_timer;
	Timer m_dodgingTimer;

	int m_currMagPos;
	bool m_isSearchPointSet;
	Vec2 m_destination;

	float angle;
public:
	Shooter(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Entity* player, Map* map, const int magazine, float searchAreaRadius, float searchPlayerRadius, Uint32 shootDelay, float speed, float bulletSpeet, float bulletDamage, float health, float score);
	~Shooter();
	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }
	void Render();
	void Update();

	bool IsPointInRadius(Vec2 centerPoint, Vec2 randomPoint, float radius);
	Vec2 GetRandomPoint(Vec2 centerPoint, int radius);
	bool IsPathBlocked();
	void MoveAroundEnemy(Vec2 center, float radius, float rotateSpeed);
	void Attack();
};

