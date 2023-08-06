#pragma once

#include <SDL.h>

#include "Object.h"
#include "Collision.h"
#include "Vec2.h"
#include "Log.h"

class Entity : public Object
{
private:

protected:
	float m_health;
	bool m_isAlive;
	Entity* m_player;
public:
	Entity(SDL_Rect dest, float health);
	Entity(SDL_Rect dest, float health, Entity* player);
	virtual ~Entity();
	void AddHealth(float health);
	void RemoveHealth(float damage);
	float GetHealth()const;
	bool IsAlive()const;
	virtual void Move();
	virtual void Render() = 0;
	virtual void Update() = 0;
	Vec2 m_velocity;
};