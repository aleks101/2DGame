#include "Tile.h"

Tile::Tile(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* player, bool isSolid) : 
	Object(dest, player) {
	m_ren = ren;
	m_tex = tex;
	m_dest = dest;
	m_screen = dest;
	SetSolid(isSolid);
}
void Tile::Render() {
	if(!CheckIfObjectOutOfScreen())
		SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Tile::Update() {
	Render();
}