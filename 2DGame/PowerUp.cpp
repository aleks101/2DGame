#include "PowerUp.h"

PowerUp::PowerUp(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* player, Ability ability) 
	: Object(dest), Ability(ability) {
	m_ren = ren;
	m_tex = tex;
	m_canBeDestroyed = false;
	m_isAlive = true;
	m_playerRect = player;
	for (int i = 0; i < 12; i++)
		m_particles[i] = NULL;
	Init(player);
}
PowerUp::~PowerUp() {
	for (auto& part : m_particles) {
		delete part;
	}
}
Ability PowerUp::GetAbility() {
	return Ability(m_health, m_speed, m_power, m_time);
}
SDL_Rect* PowerUp::GetDest() { 
	return &m_dest; 
}
SDL_Rect* PowerUp::GetScreen() { 
	return &m_screen; 
}
SDL_Rect* PowerUp:: GetSrc() { 
	return &m_src; 
}
void PowerUp::Render() {
	SDL_RenderCopy(m_ren, m_tex, nullptr, &m_screen);
}
void PowerUp::Update() {
	if (m_isAlive) {
		Render();
	}
	else {
		for (int i = 0; i < 12; i++) {
			if (m_particles[i] != NULL && !m_particles[i]->m_isDead) {
				m_particles[i]->Update();
				m_particles[i]->UpdatePositionRelativeToPlayer();
			}
		}
		for (int i = 0; i < 12; i++) {
			if (m_particles[i] != NULL && m_particles[i]->m_isDead)
				m_canBeDestroyed = true;
			else {
				m_canBeDestroyed = false;
				break;
			}
		}
	}
}
void PowerUp::Destroy() {
	if (m_isAlive) {
		m_isAlive = false;
		const float radius = 50.0f;
		Vec2 startPoint = { (float)m_screen.x, (float)m_screen.y };
		for (int i = 0; i < 12; i++) {
			float angle = static_cast<float>(i) * (2.0f * static_cast<float>(M_PI)) / static_cast<float>(12);

			// Calculate the position for the particle based on the angle and radius.
			float offsetX = radius * cosf(angle);
			float offsetY = radius * sinf(angle);
			Vec2 particlePos = startPoint + Vec2(offsetX, offsetY);

			m_particles[i] = new Particle(m_ren, m_tex, { static_cast<int>(particlePos.m_x), static_cast<int>(particlePos.m_y), 5, 5 }, m_playerRect, 4, Vec2(0,0), 10);
		}
	}
}