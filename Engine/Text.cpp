#include "Text.h"

Text::Text(SDL_Renderer* ren, int xPos, int yPos, TTF_Font* _font, std::string _text, SDL_Color _color) : Object({0,0,0,0}) {
	m_ren = ren;
	m_dest.x = xPos;
	m_dest.y = yPos;
	text = _text;
	color = _color;
	font = _font;

	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!surf) {
		std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
	}
	if (!m_ren)
		std::cout << "renderer error" << std::endl;

	m_tex = SDL_CreateTextureFromSurface(m_ren, surf);
	if (!m_tex)
		std::cout << "tex error" << std::endl;

	m_dest.w = surf->w;
	m_dest.h = surf->h;
	SetDest(m_dest);

	SDL_FreeSurface(surf);
}
Text::Text(const Text& _text) : Object(_text.m_dest) {
	m_ren = _text.m_ren;
	m_dest = _text.m_dest;
	text = _text.text;
	color = _text.color;
	font = _text.font;
}
Text::Text() : Object({0,0,0,0}) {

}
Text::~Text() {

}
void Text::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_dest);
}
void Text::Update() {
	Render();
}
SDL_Rect* Text::GetDest() {
	return &m_dest;
}
SDL_Rect* Text::GetSrc() {
	return &m_src;
}
SDL_Rect* Text::GetScreen() {
	return &m_screen;
}
void Text::ChangeText(std::string _text) {
	if (text != _text) {
		text = _text;
		SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), color);
		m_tex = SDL_CreateTextureFromSurface(m_ren, surf);
		SDL_FreeSurface(surf);
		SDL_QueryTexture(m_tex, NULL, NULL, &m_dest.w, &m_dest.h);
	}
}