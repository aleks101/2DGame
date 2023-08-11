#pragma once

#include "Object.h"
#include "Particle.h"
#include "Timer.h"
#include "Player.h"

struct Ability {
	Ability() : m_health(0), m_speed(0), m_power(0), m_time(0) {}
	Ability(int health, int speed, int power, unsigned int time) : m_health(health), m_speed(speed), m_power(power), m_time(time) {}
	Ability(const Ability& ability) {
		m_health = ability.m_health;
		m_speed = ability.m_speed;
		m_power = ability.m_power;
		m_time = ability.m_time;
	}
	int m_health;
	int m_speed;
	int m_power;
	unsigned int m_time;
};
class PowerUp : public Object, public Ability, private Timer {
private:
	Player* m_player;
	bool m_isAlive;
	Particle* m_particles[24];
	bool m_addedHealth;

	Vec2 m_orSpeed;
	float m_orDamage;
	bool m_activatePower;
public:
	PowerUp(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Player* player, Ability ability);
	~PowerUp();
	SDL_Rect* GetDest();
	SDL_Rect* GetScreen();
	SDL_Rect* GetSrc();
	void Render();
	void Update();

	void ActivateAbility();
	void ApplyAbility();
	void Destroy();

	bool m_canBeDestroyed;
};