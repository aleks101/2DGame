#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect destPos, Vec2 point, float velocity, int damage, int speedModifier, unsigned int lifeTime) :
	Object(m_dest), m_point(point), constantVelocity(velocity), m_damage(damage), m_speedModifier(speedModifier), m_lifeTime(lifeTime), m_alive(true) {
	m_ren = ren;
	m_tex = tex;
	m_dest = destPos;
	m_screen = destPos;
	m_velocity = physics::calculateVelocity(Vec2(m_dest.x, m_dest.y), point, constantVelocity);
	Start();
}
void Bullet::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Bullet::Update() {
	if (m_alive) {
		if (GetSec() >= m_lifeTime)
			Destroy();
		Move();
		Render();
	}
}
void Bullet::Destroy() {
	m_alive = false;
	Stop();
}
void Bullet::Move() {
	ChangeDestPosFor(m_velocity);
	Vec2 vec2 = CalculateDestScreenChange();
	ChangeScreenPosFor(vec2);
}