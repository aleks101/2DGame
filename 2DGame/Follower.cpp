#include "Follower.h"

Follower::Follower(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* playerDest, float speed, float damage, int radius, int playerRadius) :
	Object(dest, playerDest), Entity(), m_speed(speed), m_damage(damage), m_wonderRadius(radius), m_searchPlayerRadius(playerRadius), m_enemyDest(playerDest) {
	m_ren = ren;
	m_tex = tex;
	m_isSearchPointSet = false;
	m_destination = Vec2();
	m_isAlive = true;
	m_isPlayerInRadius = false;
	std::cout << "FOLLOWER CREATED\n";
}
Follower::~Follower() {
	std::cout << "FOLLOWER DESTROYED\n";
}
void Follower::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Follower::Update() {
	if (m_isAlive) {
		//Get player center
		Vec2 enemyCenter(m_enemyDest->x + m_enemyDest->w / 2, m_enemyDest->y + m_enemyDest->h / 2);
		m_destination = physics::CalculateVelocity(GetCenter(), enemyCenter, m_speed);
		//Check if player is in follow player radius
		//m_isPlayerInRadius = IsPointInRadius(enemyCenter, m_searchPlayerRadius);
		//if (m_isPlayerInRadius) {
		//	m_destination = physics::CalculateVelocity(GetCenter(), enemyCenter, m_speed);
		//		//AI::Follow(m_speed, Vec2(m_enemyDest->x, m_enemyDest->y));
		//	std::cout << m_destination.m_x << " : " << m_destination.m_y << std::endl;
		//	m_isSearchPointSet = false;
		//}
		////if player is not in search player radius, get random point and search for player there
		//if (!m_isPlayerInRadius && !m_isSearchPointSet) {
		//	m_currSearchPoint = GetRandomPoint();
		//	m_isSearchPointSet = true;
		//}
		////if not searching for player, then check if the enemy is near enough to the search point
		//if (m_isSearchPointSet && IsPointInRadius(m_currSearchPoint, 30)) {
		//	m_isSearchPointSet = false;
		//	std::cout << "IS IN RADIUS OF POINT\n";
		//}
		Move();
		Render();
	}
}
void Follower::Move() {
	ChangeDestPosFor(m_destination);
	ChangeScreenPosFor(m_destination);
}
bool Follower::IsPointInRadius(Vec2 point, float radius) {
	if (point.m_x > GetCenter().m_x - radius && point.m_x < GetCenter().m_x + radius &&
		point.m_y > GetCenter().m_y - radius && point.m_y < GetCenter().m_y + radius) {
		return true;
	}
	return false;
}
Vec2 Follower::GetRandomPoint() {
	float x = rand() % ((int)GetCenter().m_x - m_wonderRadius) + m_wonderRadius;
	float y = rand() % ((int)GetCenter().m_y - m_wonderRadius) + m_wonderRadius;
	std::cout << x << " : " << y << std::endl;
	return Vec2(x, y);
}