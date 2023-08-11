#pragma once

#include "Object.h"
#include "Entity.h"
#include "Physics.h"
#include "Log.h"

class Follower : public Entity
{
private:
	float m_attackSpeed;
	float m_searchSpeed;
	float m_damage;
	int m_wonderRadius;
	int m_searchPlayerRadius;

	bool m_isSearchPointSet;
	Vec2 m_destination;
	bool m_isPlayerInRadius;
public:
	Follower(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Entity* player, Map* map, float health, float attackPlayerSpeed, float searchSpeed, float damage, int wonderRadius, int playerRadius);
	~Follower();
	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }

	void Render();
	void Update();

	bool IsPointInRadius(Vec2 centerPoint, Vec2 randomPoint, float radius);
	Vec2 GetRandomPoint(Vec2 centerPoint, int radius);

};

