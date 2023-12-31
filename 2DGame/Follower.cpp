#include "Follower.h"

Follower::Follower(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Entity* player, Map* map, float score, float health, float attackSpeed, float searchSpeed, float damage, int radius, int playerRadius) :
	Entity(dest, health, score, player, map), m_attackSpeed(attackSpeed), m_searchSpeed(searchSpeed), m_damage(damage),
	m_wonderRadius(radius), m_searchPlayerRadius(playerRadius) {
	m_ren = ren;
	m_tex = tex;
	m_isSearchPointSet = false;
	m_destination = Vec2();
	m_velocity = Vec2();
	m_isAlive = true;
	m_isPlayerInRadius = false;
	LOG("FOLLOWER CREATED\n");
}
Follower::~Follower() {
	LOG("FOLLOWER DESTROYED\n");
}
void Follower::Render() {
	if (!CheckIfObjectOutOfScreen())
		SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Follower::Update() {
	if (m_health <= 0)
		m_isAlive = false;
	else {
		Vec2 enemyCenter(m_player->GetDest()->x + m_player->GetDest()->w / 2, m_player->GetDest()->y + m_player->GetDest()->h / 2);
		Vec2 enemyPos(m_player->GetDest()->x, m_player->GetDest()->y);
		Vec2 destPos(m_dest.x, m_dest.y);

		if (IsPointInRadius(GetCenter(), enemyCenter, m_searchPlayerRadius)) {
			//Player is in radius
			m_isSearchPointSet = false;
			m_velocity = physics::CalculateVelocity(destPos, enemyPos, m_attackSpeed);
			if (coll::CheckCollisionAABB(m_dest, *m_player->GetDest()))
				m_player->RemoveHealth(m_damage);
		}
		else if (!m_isSearchPointSet) {
			LOG("NEW SEARCH POINT\n");
			if (destPos.x != m_wonderRadius && destPos.y != m_wonderRadius) {
				m_destination = GetRandomPoint(destPos, m_wonderRadius);
				m_velocity = physics::CalculateVelocity(destPos, m_destination, m_searchSpeed);
				m_isSearchPointSet = true;
			}
		}
		else if (IsPointInRadius(m_destination, destPos, 30)) {
			LOG("SEARCH POINT REACHED\n");
			m_isSearchPointSet = false;
		}
		else {
			m_velocity = physics::CalculateVelocity(destPos, m_destination, m_searchSpeed);
		}
		if (Entity::CheckCollisionDestWithMap(dynamic_cast<Object*>(this))) {
			if (Entity::CheckCollisionDirectionWithMap(dynamic_cast<Object*>(this), true, true)) {
				ChangeDestPosFor(Vec2(-m_velocity.x, 0));
				ChangeScreenPosFor(Vec2(-m_velocity.x, 0));
			}
			else if (Entity::CheckCollisionDirectionWithMap(dynamic_cast<Object*>(this), true, false)) {
				ChangeDestPosFor(Vec2(0, -m_velocity.y));
				ChangeScreenPosFor(Vec2(0, -m_velocity.y));
			}
			m_isSearchPointSet = false;
		}
		Entity::Move();
		Render();
	}
}
bool Follower::IsPointInRadius(Vec2 centerPoint, Vec2 randomPoint, float radius) {
	if (randomPoint.x > centerPoint.x - radius && randomPoint.x < centerPoint.x + radius &&
		randomPoint.y > centerPoint.y - radius && randomPoint.y < centerPoint.y + radius) {
		return true;
	}
	return false;
}
Vec2 Follower::GetRandomPoint(Vec2 centerPoint, int radius) {
	int highEndX = centerPoint.x + radius;
	int highEndY = centerPoint.y + radius;

	int lowEndX = centerPoint.x - radius;
	int lowEndY = centerPoint.y - radius;

	int x = (rand() % (highEndX - lowEndX + 1)) + lowEndX;
	int y = (rand() % (highEndY - lowEndY + 1)) + lowEndY;

	return Vec2(x, y);
}