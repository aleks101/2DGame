#include "Entity.h"

Entity::Entity() {
	std::cout << "ENTITY CONSTRUCTED\n";
}
Entity::~Entity() {
	std::cout << "ENTITY DECONSTRUCTED\n";
}
void Entity::AddHealth(float health) {
	m_health += health;
}
void Entity::RemoveHealth(float health) {
	m_health -= health;
	if (m_health < 0)
		m_health = 0;
}
float Entity::GetHealth() const {
	return m_health;
}
bool Entity::IsAlive() const {
	return m_isAlive;
}