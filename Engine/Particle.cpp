#include "Particle.h"

Particle::Particle(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* player, float velocity, Vec2 targetPos, unsigned int lifeTime) :
	Object(dest, player) {
	m_ren = ren;
	m_tex = tex;
	m_lifetime = lifeTime;
	m_velocity = physics::calculateVelocity(Vec2(dest.x, dest.y), targetPos, velocity);
	std::cout << m_velocity.m_x << " : " << m_velocity.m_y << std::endl;
	m_isDead = false;
	m_timer.Start();
}
Particle::~Particle() {
	m_timer.Stop();
}
void Particle::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Particle::Update() {
	if (m_lifetime > m_timer.GetSec()) {
		Move();
		Render();
	}
	else {
		m_isDead = true;
	}
}
void Particle::Move() {
	ChangeDestPosFor(m_velocity);
	ChangeScreenPosFor(m_velocity);
}