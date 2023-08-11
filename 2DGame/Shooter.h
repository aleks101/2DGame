#pragma once

#include "Entity.h"
#include "Bullet.h"

class Shooter : public Entity, private Timer
{
private:
	int m_magazine;
	Bullet** m_bullets;
	Uint32 m_shootDelay;
	float m_searchAreaRadius;
	float m_searchPlayerRadius;
	float m_speed;
	float m_bulletSpeed;
	float m_bulletDamage;

	int m_currMagPos;
	bool m_isSearchPointSet;
	Vec2 m_destination;
public:
	Shooter(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Entity* player, Map* map, const int magazine, float searchAreaRadius, float searchPlayerRadius, Uint32 shootDelay, float speed, float bulletSpeet, float bulletDamage, float health);
	~Shooter();
	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }
	void Render();
	void Update();

	bool IsPointInRadius(Vec2 centerPoint, Vec2 randomPoint, float radius);
	Vec2 GetRandomPoint(Vec2 centerPoint, int radius);
	void Attack();
};

