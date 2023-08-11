#include "Shooter.h"

Shooter::Shooter(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Entity* player, Map* map, const int magazine, float searchAreaRadius, float searchPlayerRadius, Uint32 shootDelay, float speed, float bulletSpeed, float bulletDamage, float health) :
	Entity(dest, health, player, map), m_searchAreaRadius(searchAreaRadius), m_searchPlayerRadius(searchPlayerRadius), m_shootDelay(shootDelay), m_speed(speed), m_bulletSpeed(bulletSpeed), m_bulletDamage(bulletDamage), m_magazine(magazine) {
	m_bullets = new Bullet*[magazine];
	for (int i = 0; i < magazine; i++)
		m_bullets[i] = NULL;
	m_ren = ren;
	m_tex = tex;
	m_currMagPos = 0;
	m_isSearchPointSet = false;
	m_destination = Vec2();
	m_velocity = Vec2();
	Start();
	LOG("SHOOTER CONSTRUCTED\n");
}
Shooter::~Shooter() {
	for(int i=0;i<m_magazine;i++)
		if(m_bullets[i]!=NULL)
			delete m_bullets[i];
	LOG("SHOOTER DECONSTRUCTED\n");
}
void Shooter::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Shooter::Update() {
	if (m_health <= 0)
		m_isAlive = false;
	else {
		Vec2 enemyCenter(m_player->GetDest()->x + m_player->GetDest()->w / 2, m_player->GetDest()->y + m_player->GetDest()->h / 2);
		Vec2 enemyPos(m_player->GetDest()->x, m_player->GetDest()->y);
		Vec2 destPos(m_dest.x, m_dest.y);

		if (IsPointInRadius(GetCenter(), enemyCenter, m_searchPlayerRadius)) {
			//Player is in radius
			m_velocity = physics::CalculateVelocity(destPos, enemyPos, 2);
			m_isSearchPointSet = false;
			Attack();
		}
		else if (!m_isSearchPointSet) {
			if (destPos.x != m_searchAreaRadius && destPos.y != m_searchAreaRadius) {
				m_destination = GetRandomPoint(destPos, m_searchAreaRadius);
				m_velocity = physics::CalculateVelocity(destPos, m_destination, m_speed);
				m_isSearchPointSet = true;
			}
		}
		else if (IsPointInRadius(m_destination, destPos, 30) || Entity::CheckCollisionWithMap())
			m_isSearchPointSet = false;
		else
			m_velocity = physics::CalculateVelocity(destPos, m_destination, m_speed);
		Entity::Move();
		for (int i = 0; i < m_magazine; i++) {
			if (m_bullets[i] != NULL) {
				m_bullets[i]->Update();
				m_bullets[i]->UpdatePositionRelativeToPlayer();
				if (coll::CheckCollisionAABB(m_player->GetScreen(), m_bullets[i]->GetScreen())) {
					m_player->RemoveHealth(m_bulletDamage);
					delete m_bullets[i];
					m_bullets[i] = NULL;
				}
			}
		}
		Render();
	}
}
void Shooter::Attack() {
	if (m_currMagPos < m_magazine && GetMili() > m_shootDelay) {
		Start();
		Vec2 point = m_player->GetScreenPos();
		point.x += m_playerRect->w / 2;
		point.y += m_playerRect->h / 2;
		m_bullets[m_currMagPos] = new Bullet(m_ren, m_tex, { m_dest.x, m_dest.y, m_dest.w / 2, m_dest.h / 2 }, m_playerRect, GetScreenPos(), point, m_bulletSpeed, m_bulletDamage, 0, 5);
		m_currMagPos++;
	}
	else if(m_currMagPos >= m_magazine && GetMili() > 2500)
		m_currMagPos = 0;
}
bool Shooter::IsPointInRadius(Vec2 centerPoint, Vec2 randomPoint, float radius) {
	if (randomPoint.x > centerPoint.x - radius && randomPoint.x < centerPoint.x + radius &&
		randomPoint.y > centerPoint.y - radius && randomPoint.y < centerPoint.y + radius) {
		return true;
	}
	return false;
}
Vec2 Shooter::GetRandomPoint(Vec2 centerPoint, int radius) {
	int highEndX = centerPoint.x + radius;
	int highEndY = centerPoint.y + radius;

	int lowEndX = centerPoint.x - radius;
	int lowEndY = centerPoint.y - radius;

	int x = (rand() % (highEndX - lowEndX + 1)) + lowEndX;
	int y = (rand() % (highEndY - lowEndY + 1)) + lowEndY;

	return Vec2(x, y);
}