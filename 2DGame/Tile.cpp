#include "Tile.h"

Tile::Tile(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect* player) : 
	Object(dest, player) {
	m_ren = ren;
	m_tex = tex;
	m_dest = dest;
	m_screen = dest;
}
void Tile::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Tile::Update() {
	Render();
}