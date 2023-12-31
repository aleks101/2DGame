#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect destPos, SDL_Rect* playerDest, Vec2 screenPos, Vec2 point, float velocity, float damage, int speedModifier, unsigned int lifeTime) :
	Object(m_dest, playerDest), m_point(point), constantVelocity(velocity), m_damage(damage), m_speedModifier(speedModifier), m_lifeTime(lifeTime), m_alive(true), m_timer() {
	m_ren = ren;
	m_tex = tex;
	m_screen = destPos;
	m_screen.x = screenPos.x;
	m_screen.y = screenPos.y;
	m_velocity = physics::CalculateVelocity(Vec2(m_screen.x, m_screen.y), point, constantVelocity);
	m_timer.Start();
}
void Bullet::Render() {
	if (!CheckIfObjectOutOfScreen())
		SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Bullet::Update() {
	if (m_alive) {
		if (m_timer.GetSec() >= m_lifeTime)
			Destroy();
		Move();
		Render();
	}
}
void Bullet::Destroy() {
	m_alive = false;
	m_timer.Stop();
}
void Bullet::Move() {
	ChangeDestPosFor(m_velocity);
	ChangeScreenPosFor(m_velocity);
}