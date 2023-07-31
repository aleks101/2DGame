#include "Follower.h"

Follower::Follower(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* playerDest,float health, float speed, float damage, int radius, int playerRadius) :
	Object(dest, playerDest), Entity(health), m_speed(speed), m_damage(damage), m_wonderRadius(radius), m_searchPlayerRadius(playerRadius), m_enemyDest(playerDest) {
	m_ren = ren;
	m_tex = tex;
	m_isSearchPointSet = false;
	m_destination = Vec2();
	m_velocity = Vec2();
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
	else {
		Vec2 enemyCenter(m_enemyDest->x + m_enemyDest->w / 2, m_enemyDest->y + m_enemyDest->h / 2);
		Vec2 enemyPos(m_enemyDest->x, m_enemyDest->y);
		Vec2 destPos(m_dest.x, m_dest.y);

		if (IsPointInRadius(GetCenter(), enemyCenter, m_searchPlayerRadius)) {
			//Player is in radius
			m_isSearchPointSet = false;
			if(m_velocity != physics::CalculateVelocity(destPos, enemyPos, m_speed))
				m_velocity = physics::CalculateVelocity(destPos, enemyPos, m_speed);
		}
		else if(!m_isSearchPointSet){
			std::cout << "NEW SEARCH POINT\n";
			if (destPos.x != m_wonderRadius && destPos.y != m_wonderRadius) {
				m_destination = GetRandomPoint(destPos, m_wonderRadius);
				m_velocity = physics::calculateVelocityProportional(destPos, m_destination, m_speed);
				m_isSearchPointSet = true;
			}
		}
		else if(IsPointInRadius(m_destination, destPos, 30)){
			std::cout << "SEARCH POINT REACHED\n";
			m_isSearchPointSet = false;
		}
		else
			std::cout << destPos.x << ", " << destPos.y << " : " << m_destination.x << ", " << m_destination.y << "\n";
		Move();
		Render();
	}
}
void Follower::Move() {
	ChangeDestPosFor(m_velocity);
	ChangeScreenPosFor(m_velocity);
}
bool Follower::IsPointInRadius(Vec2 centerPoint, Vec2 randomPoint, float radius) {
	if (randomPoint.x > centerPoint.x - radius && randomPoint.x < centerPoint.x + radius &&
		randomPoint.y > centerPoint.y - radius && randomPoint.y < centerPoint.y + radius) {
		return true;
	}
	return false;
}
Vec2 Follower::GetRandomPoint(Vec2 centerPoint, int radius) {
	/*int x = rand() % ((int)centerPoint.x - radius) + radius;
	int y = rand() % ((int)centerPoint.y - radius) + radius;

	return Vec2(x, y);*/
	//// Seed the random number generator with the current time
	//std::srand(static_cast<unsigned int>(std::time(0)));

	// Generate a random angle in radians
	float randomAngle = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 2.0f * M_PI;

	// Calculate the random x and y coordinates within the radius
	int x = static_cast<int>(centerPoint.x + radius * std::cos(randomAngle));
	int y = static_cast<int>(centerPoint.y + radius * std::sin(randomAngle));

	return Vec2{ static_cast<float>(x), static_cast<float>(y) };
}