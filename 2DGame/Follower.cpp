#include "Follower.h"

Follower::Follower(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* playerDest,float health, float speed, float damage, int radius, int playerRadius) :
	Object(dest, playerDest), Entity(health), m_speed(speed), m_damage(damage), m_wonderRadius(radius), m_searchPlayerRadius(playerRadius), m_enemyDest(playerDest) {
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
	if (m_health <= 0)
		m_isAlive = false;
	if (m_isAlive) {
		Vec2 enemyCenter(m_enemyDest->x + m_enemyDest->w / 2, m_enemyDest->y + m_enemyDest->h / 2);
		Vec2 enemyPos(m_enemyDest->x, m_enemyDest->y);

		if (IsPointInRadius(enemyCenter, m_searchPlayerRadius)) {
			//Player is in radius
			m_isSearchPointSet = false;
			if(m_destination != physics::CalculateVelocity(Vec2(m_dest.x, m_dest.y), enemyPos, m_speed))
				m_destination = physics::CalculateVelocity(Vec2(m_dest.x, m_dest.y), enemyPos, m_speed);
		}
		else if(!m_isSearchPointSet){
			m_destination = physics::CalculateVelocity(Vec2(m_dest.x, m_dest.y), GetRandomPoint(m_wonderRadius), m_speed);
			m_isSearchPointSet = true;
		}
		else if(IsPointInRadius(Vec2(m_dest.x, m_dest.y), 30)){
			m_isSearchPointSet = false;
		}
		Move();
		Render();
	}
}
void Follower::Move() {
	ChangeDestPosFor(m_destination);
	ChangeScreenPosFor(m_destination);
}
bool Follower::IsPointInRadius(Vec2 point, float radius) {
	if (point.x > GetCenter().x - radius && point.x < GetCenter().x + radius &&
		point.y > GetCenter().y - radius && point.y < GetCenter().y + radius) {
		return true;
	}
	return false;
}
Vec2 Follower::GetRandomPoint(int radius) {
	int x = rand() % ((int)GetCenter().x - radius) + radius;
	int y = rand() % ((int)GetCenter().y - radius) + radius;

	return Vec2(x, y);
}