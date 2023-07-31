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
	Entity(float health);
	~Entity();
	void AddHealth(float health);
	void RemoveHealth(float damage);
	float GetHealth()const;
	bool IsAlive()const;
	virtual void Move()=0;
	virtual void Render() = 0;
	virtual void Update() = 0;
};