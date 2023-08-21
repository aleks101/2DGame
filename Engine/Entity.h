#pragma once

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
	Entity(SDL_Rect dest, float health, float score, Entity* player, Map* map);
	virtual ~Entity();
	virtual void AddHealth(float health);
	virtual void RemoveHealth(float damage);
	virtual float GetHealth()const;
	virtual bool IsAlive()const;
	virtual void Move();
	virtual bool CheckCollisionDestWithMap(Object* object);
	virtual bool CheckCollisionScreenWithMap(Object* object);
	virtual bool CheckCollisionDirectionWithMap(Object* object, bool destOrScreen, bool XorY);
	void SetMap(Map* map);

	virtual void Render() = 0;
	virtual void Update() = 0;

	Vec2 m_velocity;
	float m_score;
};