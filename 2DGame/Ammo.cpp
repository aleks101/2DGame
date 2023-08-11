#include "Ammo.h"

Ammo::Ammo(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, Player* player, int ammo) :
	Object(dest, player->GetDest()), m_ammo(ammo), m_player(player) {
	m_ren = ren;
	m_tex = tex;
	m_isAlive = true;
	LOG("AMMO CONSTRUCTED\n");
}
Ammo::~Ammo() {
	LOG("AMMO DECONSTUCTED\n");
}
void Ammo::Update() {
	if (m_isAlive) {
		if (coll::CheckCollisionAABB(&m_dest, m_player->GetDest())) {
			if (m_player->m_gun != NULL) {
				m_isAlive = false;
				m_player->m_gun->AddAmmo(m_ammo);
			}
		}
		Render();
	}
}
void Ammo::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}