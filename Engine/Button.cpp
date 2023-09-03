#include "Button.h"

Button::Button(SDL_Renderer* ren, SDL_Event* ev, Vec2 pos, TTF_Font* font, std::string text, SDL_Color color) 
	: Object({(int)pos.x, (int)pos.y, 1, 1}), m_ev(ev) {
	m_ren = ren;
	m_text = new Text(ren, pos, font, text, color);
	m_tex = NULL;
}
Button::Button(SDL_Renderer* ren, SDL_Event* ev, SDL_Rect rect, SDL_Texture* tex, Vec2 pos, TTF_Font* font, std::string text, SDL_Color color) 
	: Object(rect), m_ev(ev){
	m_ren = ren;
	m_text = new Text(ren, pos, font, text, color);
	m_tex = tex;
}
Button::Button(SDL_Renderer* ren, SDL_Event* ev, SDL_Rect rect, SDL_Texture* tex)
	: Object(rect), m_ev(ev) {
	m_ren = ren;
	m_tex = tex;
	m_text = NULL;
}
Button::~Button() {
	if (m_text == NULL)
		delete m_text;
}
SDL_Rect* Button::GetDest() {
	return &m_dest;
}
SDL_Rect* Button::GetSrc() {
	return &m_src;
}
SDL_Rect* Button::GetScreen() {
	return &m_screen;
}
void Button::Render() {
	if (m_tex != NULL)
		SDL_RenderCopy(m_ren, m_tex, NULL, &m_dest);
	if (m_text != NULL)
		m_text->Update();
}
void Button::Update() {
	Render();
}
bool Button::CheckMouseOver() {
	SDL_GetMouseState(&x, &y);
	if (m_text != NULL)
		if(coll::CheckCollisionPoint(m_text->GetDest(), Vec2(x, y)))
			return true;
	if (m_tex != NULL)
		if(coll::CheckCollisionPoint(GetDest(), Vec2(x, y)))
			return true;
	return false;
}
bool Button::CheckMouseClick() {
	if (m_ev->type == SDL_MOUSEBUTTONDOWN)
		if (m_ev->button.button == SDL_BUTTON_LEFT && CheckMouseOver())
			return true;
	return false;
}