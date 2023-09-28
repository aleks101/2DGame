#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "Object.h"
#include "Log.h"

class Text : public Object
{
private:
	std::string m_permaText;
	std::string m_text;
	SDL_Color m_color;
	TTF_Font* m_font;
public:
	Text();
	Text(SDL_Renderer* ren, Vec2 pos, TTF_Font* _font, std::string _text, SDL_Color _color);
	Text(const Text& text);
	~Text();
	void Render();
	void Update();
	SDL_Rect* GetDest();
	SDL_Rect* GetSrc();
	SDL_Rect* GetScreen();

	void SetNoChangeText(int indexTo);
	void SetNoChangeText(std::string newText);
	void ChangeText(std::string _text);
	void ChangeText(int num);
	void ChangeColor(SDL_Color color);
};

