#include "Collectable.h"

Collectable::Collectable(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Player* player, int ammo, float health, float score) :
	Object(dest, player->GetDest()), m_ammo(ammo), m_health(health), m_score(score), m_player(player) {
	m_ren = ren;
	m_tex = tex;
	m_isAlive = true;
	LOG("AMMO CONSTRUCTED\n");
}
Collectable::~Collectable() {
	LOG("AMMO DECONSTUCTED\n");
}
void Collectable::Update() {
	if (m_isAlive) {
		if (coll::CheckCollisionAABB(m_dest, *m_player->GetDest())) {
			if (m_player->m_gun != NULL) {
				m_isAlive = false;
				m_player->m_gun->AddAmmo(m_ammo);
				m_player->AddHealth(m_health);
				m_player->AddScore(m_score);
			}
		}
		Render();
	}
}
void Collectable::Render() {
	if (!CheckIfObjectOutOfScreen())
		SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}