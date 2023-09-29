#include "EnemyTurret.h"
#include "Physics.h"

EnemyTurret::EnemyTurret(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Entity* player, float health, Map* map, float attackRadius, float shootDelay, float shootCycleDelay, float bulletDamage, float bulletSpeed, float score) :
	Entity(dest, health, score, player, map), m_attackRadius(attackRadius), m_shootDelay(shootDelay), m_shootCycle(shootCycleDelay), m_bulletDamage(bulletDamage), m_bulletSpeed(bulletSpeed), m_timer() {
	m_ren = ren;
	m_tex = tex;
	m_hasTimerStarted = false;
	m_hasTimerStopped = false;
	m_attackCycleReady = false;
}
EnemyTurret::~EnemyTurret() {

}
SDL_Rect* EnemyTurret::GetDest() {
	return &m_dest;
}
SDL_Rect* EnemyTurret::GetSrc() {
	return &m_src;
}
SDL_Rect* EnemyTurret::GetScreen() {
	return &m_screen;
}
void EnemyTurret::Render() {
	if (!CheckIfObjectOutOfScreen())
		SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void EnemyTurret::Update() {
	if (m_isAlive) {
		if (IsPointInRadius(GetCenter(), m_player->GetCenter(), m_attackRadius) && !IsPathBlocked()) {
			if (!m_hasTimerStarted) {
				m_timer.Start();
				m_hasTimerStarted = true;
			}
			if (m_hasTimerStopped) {
				m_hasTimerStopped = false;
				m_timer.Resume();
			}
			Attack();
		}
		else if(!m_hasTimerStopped) {
			m_timer.Stop();
			m_hasTimerStopped = true;
		}
		Render();
	}
}
bool EnemyTurret::IsPointInRadius(Vec2 centerPoint, Vec2 randomPoint, float radius) {
	if (randomPoint.x > centerPoint.x - radius && randomPoint.x < centerPoint.x + radius &&
		randomPoint.y > centerPoint.y - radius && randomPoint.y < centerPoint.y + radius) {
		return true;
	}
	return false;
}
bool EnemyTurret::IsPathBlocked() {
	Ray raycast(GetCenter(), m_player->GetCenter(), m_map);
	return !raycast.HasReachPoint();
}
void EnemyTurret::Attack() {
	m_timer.Stop();
	if (!m_attackCycleReady) {
		if (m_timer.GetDurationMili() >= m_shootCycle) {
			m_hasTimerStarted = false;
			m_attackCycleReady = true;
		}
		else
			m_timer.Resume();
	}
	else {
		//koncas streljanje
	}
}