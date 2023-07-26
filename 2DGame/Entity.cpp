#include "Entity.h"

Entity::Entity(SDL_Rect dest) : Object(dest) {
	std::cout << "ENTITY CONSTRUCTED\n";
}
Entity::Entity(SDL_Rect dest, SDL_Rect* playerDest) : Object(dest, playerDest) {
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