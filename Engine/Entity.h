#pragma once

#include <SDL.h>

#include "Vec2.h"

class Entity
{
private:

protected:
	float m_health;
	bool m_isAlive;
	Vec2 m_velocity;
public:
	Entity();
	~Entity();
	void AddHealth(float health);
	void RemoveHealth(float health);
	float GetHealth()const;
	bool IsAlive()const;
	virtual void Move()=0;
};