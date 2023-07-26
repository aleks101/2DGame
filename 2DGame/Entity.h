#pragma once

#include "Object.h"

class Entity : public Object
{
private:

protected:
	float m_health;
	bool m_isAlive;
	Vec2 m_velocity;
public:
	Entity(SDL_Rect dest);
	Entity(SDL_Rect dest, SDL_Rect* playerDest);
	~Entity();
	void AddHealth(float health);
	void RemoveHealth(float health);
	float GetHealth()const;
	bool IsAlive()const;
	virtual void Move()=0;
};