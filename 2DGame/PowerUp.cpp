#include "PowerUp.h"

PowerUp::PowerUp(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Player* player, Ability ability) 
	: Object(dest, player->GetDest()), Ability(ability), m_player(player) {
	m_ren = ren;
	m_tex = tex;
	m_canBeDestroyed = false;
	m_isAlive = true;
	m_addedHealth = false;
	m_activatePower = false;
	for (int i = 0; i < 24; i++)
		m_particles[i] = NULL;
}
PowerUp::~PowerUp() {
	for (auto& part : m_particles) {
		delete part;
	}
}
void PowerUp::ActivateAbility() {
	if (!m_activatePower) {
		Start();
		Destroy();
		if (m_player->m_gun != NULL)
			m_orDamage = m_player->m_gun->m_damage;
		m_orSpeed = m_player->m_velocity;
	}
	m_activatePower = true;
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
	if(!CheckIfObjectOutOfScreen())
		SDL_RenderCopy(m_ren, m_tex, nullptr, &m_screen);
}
void PowerUp::Update() {
	if (m_isAlive) {
		if (coll::CheckCollisionAABB(GetDest(), m_player->GetDest()))
			ActivateAbility();
		Render();
	}
	else {
		for (int i = 0; i < 24; i++) {
			if (m_particles[i] != NULL && !m_particles[i]->m_isDead) {
				m_particles[i]->Update();
				m_particles[i]->UpdatePositionRelativeToPlayer();
			}
		}
		if (m_activatePower && GetSec() < m_time) {
			ApplyAbility();
		}
		else
			m_canBeDestroyed = true;
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
			timeToLive = 0.4 - static_cast<float>(rand() % 15) / 100;
			size = 7 - rand()%4;
			speedValue = 4 - static_cast<float>(rand()%8)/100;
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
void PowerUp::ApplyAbility() {
	m_player->m_velocity = m_orSpeed * m_speed;
	if (!m_addedHealth) {
		m_player->AddHealth(m_health);
		m_addedHealth = true;
	}
	if (m_player->m_gun != NULL)
		m_player->m_gun->m_damage = m_orDamage * m_power;
}