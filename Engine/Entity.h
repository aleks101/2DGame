#pragma once

#include <SDL.h>

#include "Object.h"
#include "Collision.h"
#include "Vec2.h"
#include "Log.h"

class Map;

class Entity : public Object
{
private:
	Map* m_map;
protected:
	float m_health;
	bool m_isAlive;
	Entity* m_player;
public:
	Entity(SDL_Rect dest, float health);
	Entity(SDL_Rect dest, float health, Entity* player, Map* map);
	virtual ~Entity();
	void AddHealth(float health);
	void RemoveHealth(float damage);
	float GetHealth()const;
	bool IsAlive()const;
	virtual void Move();
	virtual bool CheckCollisionWithMap();
	virtual void Render() = 0;
	virtual void Update() = 0;
	Vec2 m_velocity;
};