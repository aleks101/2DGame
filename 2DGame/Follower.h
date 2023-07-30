#pragma once

#include "Object.h"
#include "Entity.h"
#include "Physics.h"

class Follower : public Object, public Entity
{
private:
	float m_speed;
	float m_damage;
	int m_wonderRadius;
	int m_searchPlayerRadius;

	bool m_isSearchPointSet;
	Vec2 m_destination;
	bool m_isPlayerInRadius;

	SDL_Rect* m_enemyDest;
public:
	Follower(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* playerDest, float speed, float damage, int wonderRadius, int playerRadius);
	~Follower();
	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }

	void Render();
	void Update();
	void Move();
	bool IsPointInRadius(Vec2 point, float radius);
	Vec2 GetRandomPoint();
};

