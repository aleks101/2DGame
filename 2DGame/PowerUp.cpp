#include "PowerUp.h"

PowerUp::PowerUp(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* player, Ability ability) 
	: Object(dest, player), Ability(ability) {
	m_ren = ren;
	m_tex = tex;
	m_canBeDestroyed = false;
	m_isAlive = true;
	m_playerRect = player;
	for (int i = 0; i < 24; i++)
		m_particles[i] = NULL;
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
		for (int i = 0; i < 24; i++) {
			if (m_particles[i] != NULL && !m_particles[i]->m_isDead) {
				m_particles[i]->Update();
				m_particles[i]->UpdatePositionRelativeToPlayer();
			}
		}
		for (int i = 0; i < 24; i++) {
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
		// Calculate the angle step for each particle
		float angleStep = 2 * M_PI / 24; // Divide the full circle (2 * pi radians) into 12 parts
		float distance = 1;

		int xCenter = m_dest.x + m_dest.w / 2;
		int yCenter = m_dest.y + m_dest.h / 2;

		float timeToLive, speedValue;
		int size;

		for (int i = 0; i < 24; ++i)
		{
			timeToLive = 0.4 - (float)(rand() % 15) / 100;
			size = 7 - rand()%4;
			speedValue = 4 - (float)(rand()%8)/100;
			// Calculate the angle for the current particle
			float angle = i * angleStep;

			float targetX = xCenter + std::cos(angle) * distance;
			float targetY = yCenter + std::sin(angle) * distance;

			// Calculate the normalized direction vector towards the target position
			Vec2 direction(targetX - xCenter, targetY - yCenter);
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			direction = direction * (1.0f / distance);

			// Set the velocity vector with a constant speed value
			Vec2 velocity = direction*speedValue;

			// Set the initial position of the particle (same as the center point)
			SDL_Rect dest = { xCenter, yCenter, size, size };
			SDL_Rect screen = { m_screen.x, m_screen.y, size, size };

			// Create the particle with the calculated velocity and position
			m_particles[i] = new Particle(m_ren, m_tex, dest, {m_screen.x+m_screen.w/2, m_screen.y+m_screen.h/2, size, size}, m_playerRect, velocity, timeToLive);

		}
	}
}