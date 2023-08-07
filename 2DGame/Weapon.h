#pragma once

#include "Object.h"
#include "Timer.h"
#include "Bullet.h"
#include "Text.h"

#include "Log.h"

template<int T>
class Weapon : public Object, protected Timer
{
private:
	Uint32 m_fireDelay;
	Bullet* m_magazine[T];
	SDL_Event* m_ev;

	float m_bulletSpeed;
	int m_currMagPos;
	float m_damage;
	int m_ammo;
	int m_bulletSize;
	unsigned int m_bulletLifeTime;
	bool m_holdFire;
	bool m_released;
	bool m_isPickedUp;
public:
	Weapon(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest, SDL_Rect* playerDest, Vec2 screenPos, Uint32 fireDelay, bool holdFire, float bulletSpeed, float damage, int size, unsigned int lifeTime);
	~Weapon();
	void Update();
	void Render();
	SDL_Rect* GetDest() { return &m_dest; }
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetScreen() { return &m_screen; }

	void Shoot(int X, int Y);
	void Reload();
	void AddAmmo(int amount);
	void Drop();
	void PickUp();
	std::vector<Bullet*> GetBullets();

	int GetMagSize();
	const int m_magSize = T;
};
template<int T>
Weapon<T>::Weapon(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest, SDL_Rect* playerDest, Vec2 screenPos, Uint32 fireDelay, bool holdFire, float bulletSpeed, float damage, int size, unsigned int lifetime) :
	Object(dest, playerDest), m_ev(ev), m_holdFire(holdFire), m_bulletSpeed(bulletSpeed), m_currMagPos(0),
	m_damage(damage), m_ammo(0), m_bulletSize(size), m_bulletLifeTime(lifetime), m_isPickedUp(false), m_fireDelay(fireDelay) {
	m_ren = ren;
	m_tex = tex;
	m_released = false;
	SetScreenPos(screenPos);
	for (int i = 0; i < m_magSize; i++)
		m_magazine[i] = NULL;
	Start();
	LOG("WEAPON CONSTRUCTED\n");
}
template<int T>
Weapon<T>::~Weapon() {
	for (int i = 0; i < m_magSize; i++)
		delete m_magazine[i];
	LOG("WEAPON DECONSTRUCTED\n");
}
template<int T>
void Weapon<T>::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_dest);
}
template<int T>
void Weapon<T>::Update() {
	if (!m_isPickedUp)
		Render();
	for (int i = 0; i < m_magSize; i++) {
		if (m_magazine[i] != NULL && !m_magazine[i]->m_alive) {
			delete m_magazine[i];
			m_magazine[i] = NULL;
		}
		if (m_magazine[i] != NULL) {
			m_magazine[i]->Update();
			m_magazine[i]->UpdatePositionRelativeToPlayer();
		}
	}
}
template<int T>
void Weapon<T>::Reload() {
	if (m_ammo >= m_magSize) {
		m_currMagPos = 0;
		LOG("RELOAD\n");
	}
}
template<int T>
void Weapon<T>::Shoot(int X, int Y) {
	if (GetMili() > m_fireDelay) {
		Start();
		
		if (m_holdFire)
			m_released = true;
		if (m_ev->type == SDL_MOUSEBUTTONDOWN) {
			if (m_ev->button.button == SDL_BUTTON_LEFT && m_released) {
				m_released = false;
				if (m_ammo > 0 && m_currMagPos < 30) {
					LOG("SHOT\n");
					m_magazine[m_currMagPos] = new Bullet(m_ren, m_tex, { m_dest.x + m_dest.w / 2 - m_bulletSize / 2, m_dest.y + m_dest.h / 2 - m_bulletSize / 2, m_bulletSize, m_bulletSize },
						m_playerRect, Vec2(m_screen.x + m_screen.w / 2 - m_bulletSize / 2, m_screen.y + m_screen.h / 2 - m_bulletSize / 2),
						Vec2(X, Y), m_bulletSpeed, m_damage, 0, m_bulletLifeTime);
					m_ammo--;
					m_currMagPos++;
				}
			}
		}
	}
	if (m_ev->type == SDL_MOUSEBUTTONDOWN)
		if (m_ev->button.button == SDL_BUTTON_LEFT)
			m_released = true;
}
template<int T>
void Weapon<T>::AddAmmo(int amount) {
	m_ammo = amount;
}
template<int T>
void Weapon<T>::Drop() {
	m_isPickedUp = false;
}
template<int T>
void Weapon<T>::PickUp() {
	m_isPickedUp = true;
}
template<int T>
std::vector<Bullet*> Weapon<T>::GetBullets() {
	std::vector<Bullet*> bullets;
	for (int i = 0; i < 30; i++)
		if (m_magazine[i] != NULL)
			bullets.push_back(m_magazine[i]);
	return bullets;
}
template<int T>
int Weapon<T>::GetMagSize() {
	return m_magSize - m_currMagPos;
}