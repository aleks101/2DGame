#include "Entity.h"

Entity::Entity(SDL_Rect dest, float health) 
	: Object(dest), m_health(health), m_isAlive(true), m_velocity(Vec2(0,0)), m_player(nullptr) {
	std::cout << "ENTITY CONSTRUCTED\n";
}
Entity::Entity(SDL_Rect dest, float health, Entity* player) 
	: m_player(player), m_health(health), m_isAlive(true), m_velocity(Vec2(0,0)), Object(dest, player->GetDest()) {
	std::cout << "ENTITY CONSTRUCTED\n";
}
Entity::~Entity() {
	std::cout << "ENTITY DECONSTRUCTED\n";
}
void Entity::AddHealth(float health) {
	m_health += health;
}
void Entity::RemoveHealth(float damage) {
	m_health -= damage;
	if (m_health < 0)
		m_health = 0;
}
float Entity::GetHealth() const {
	return m_health;
}
bool Entity::IsAlive() const {
	return m_isAlive;
}
void Entity::Move() {
	ChangeDestPosFor(m_velocity);
	ChangeScreenPosFor(m_velocity);
}