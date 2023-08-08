#pragma once

#include "Object.h"
#include "Timer.h"
#include "Bullet.h"
#include <string>

#include "Log.h"

template<int T>
class Weapon : public Object, protected Timer
{
private:
	Uint32 m_fireDelay;
	Bullet* m_magazine[T];
	SDL_Event* m_ev;
	SDL_Rect* m_playerScreen;

	float m_bulletSpeed;
	int m_currMagPos;
	float m_damage;
	int m_bulletSize;
	unsigned int m_bulletLifeTime;
	bool m_holdFire;
	bool m_released;
public:
	Weapon(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest, SDL_Rect* playerDest, SDL_Rect* playerScreen, Uint32 fireDelay, bool holdFire, float bulletSpeed, float damage, int size, unsigned int lifeTime);
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
	std::string GetAmmo();

	int GetMagSize();
	const int m_magSize = T;
	int m_ammo;
	bool m_isPickedUp;
};
template<int T>
Weapon<T>::Weapon(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest, SDL_Rect* playerDest, SDL_Rect* playerScreen, Uint32 fireDelay, bool holdFire, float bulletSpeed, float damage, int size, unsigned int lifetime) :
	Object(dest, playerDest), m_ev(ev), m_holdFire(holdFire), m_bulletSpeed(bulletSpeed), m_currMagPos(0),
	m_damage(damage), m_ammo(0), m_bulletSize(size), m_bulletLifeTime(lifetime), m_isPickedUp(false), m_fireDelay(fireDelay), m_playerScreen(playerScreen) {
	m_ren = ren;
	m_tex = tex;
	m_released = true;
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
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
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
	if (m_isPickedUp) {
		if (m_ammo < m_magSize && m_ammo > 0) {
			m_released = true;
			m_currMagPos = m_magSize - m_ammo;
			LOG("RELOAD\n");
		}
		else if (m_ammo > 0) {
			m_currMagPos = 0;
			m_released = true;
			LOG("RELOAD\n");

		}
	}
}
template<int T>
void Weapon<T>::Shoot(int X, int Y) {
	if (m_isPickedUp) {
		if (m_ev->type == SDL_MOUSEBUTTONDOWN)
			if (m_ev->button.button == SDL_BUTTON_LEFT)
				m_released = false;
		if (m_ev->type == SDL_MOUSEBUTTONUP)
			if (m_ev->button.button == SDL_BUTTON_LEFT)
				m_released = true;

		if (GetMili() > m_fireDelay) {
			Start();
			if (m_holdFire && !m_released) {
				if (m_ammo > 0 && m_currMagPos < m_magSize) {
					LOG("SHOT\n");
					m_magazine[m_currMagPos] = new Bullet(m_ren, m_tex, { m_dest.x + m_dest.w / 2 - m_bulletSize / 2, m_dest.y + m_dest.h / 2 - m_bulletSize / 2, m_bulletSize, m_bulletSize },
						m_playerRect, Vec2(m_playerScreen->x + m_dest.w / 2 - m_bulletSize / 2, m_playerScreen->y + m_dest.h / 2 - m_bulletSize / 2),
						Vec2(X, Y), m_bulletSpeed, m_damage, 0, m_bulletLifeTime);
					m_ammo--;
					m_currMagPos++;
				}
			}
			else if (!m_released) {
				m_released = true;
				if (m_ammo > 0 && m_currMagPos < m_magSize) {
					LOG("SHOT\n");
					m_magazine[m_currMagPos] = new Bullet(m_ren, m_tex, { m_playerRect->x + m_dest.w / 2 - m_bulletSize / 2, m_playerRect->y + m_dest.h / 2 - m_bulletSize / 2, m_bulletSize, m_bulletSize },
						m_playerRect, Vec2(m_screen.x + m_screen.w / 2 - m_bulletSize / 2, m_screen.y + m_screen.h / 2 - m_bulletSize / 2),
						Vec2(X, Y), m_bulletSpeed, m_damage, 0, m_bulletLifeTime);
					m_ammo--;
					m_currMagPos++;
				}
			}
		}
	}
}
template<int T>
void Weapon<T>::AddAmmo(int amount) {
	m_ammo += amount;
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
	for (int i = 0; i < m_magSize; i++)
		if (m_magazine[i] != NULL)
			bullets.push_back(m_magazine[i]);
	return bullets;
}
template<int T>
int Weapon<T>::GetMagSize() {
	return m_magSize - m_currMagPos;
}
template<int T>
std::string Weapon<T>::GetAmmo() {
	std::string magSize = std::to_string(GetMagSize());
	std::string ammo = magSize + "/" + std::to_string(m_ammo);
	return ammo;
}