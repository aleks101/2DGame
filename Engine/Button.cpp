#include "Button.h"

Button::Button(SDL_Renderer* ren, SDL_Event* ev, Vec2 pos, TTF_Font* font, std::string text, SDL_Color color1, SDL_Color color2) 
	: Text(ren, pos, font, text, color1), m_ev(ev) {
	normalColor = color1;
	highlightColor = color2;
}
Button::~Button() {

}
bool Button::CheckMouseOver() {
	SDL_GetMouseState(&x, &y);
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
void Button::Update() {
	if (CheckMouseOver() && !isMouseOver) {
		isMouseOver = true;
		ChangeColor(highlightColor);
	}
	else if (!CheckMouseOver() && isMouseOver) {
		isMouseOver = false;
		ChangeColor(normalColor);
	}
	Text::Update();
}