#pragma once

#include "Object.h"
#include "Text.h"
#include "Collision.h"

class Button : public Text
{
private:
	int x, y;
	bool isMouseOver;
	SDL_Event* m_ev;

	SDL_Color normalColor;
	SDL_Color highlightColor;
public:
	Button(SDL_Renderer* ren, SDL_Event* ev, Vec2 pos, TTF_Font* font, std::string text, SDL_Color color1, SDL_Color color2);
	~Button();
	bool CheckMouseOver();
	bool CheckMouseClick();
	void Update();
};

