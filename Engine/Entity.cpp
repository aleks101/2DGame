#include "Entity.h"

Entity::Entity(float health) : m_health(health), m_isAlive(true), m_velocity(Vec2(0,0)) {
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