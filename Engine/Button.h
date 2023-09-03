#pragma once

#include "Object.h"
#include "Text.h"
#include "Collision.h"

class Button : public Object
{
private:
	int x, y;
	Text* m_text;
	SDL_Event* m_ev;
public:
	Button(SDL_Renderer* ren, SDL_Event* ev, Vec2 pos, TTF_Font* font, std::string text, SDL_Color color);
	Button(SDL_Renderer* ren, SDL_Event* ev, SDL_Rect rect, SDL_Texture* tex, Vec2 pos, TTF_Font* font, std::string text, SDL_Color color);
	Button(SDL_Renderer* ren, SDL_Event* ev, SDL_Rect rect, SDL_Texture* tex);
	~Button();
	SDL_Rect* GetDest();
	SDL_Rect* GetSrc();
	SDL_Rect* GetScreen();
	void Render();
	void Update();
	bool CheckMouseOver();
	bool CheckMouseClick();
};

