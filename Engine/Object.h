#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Camera.h"

class Object : public Camera
{
public:
	Object(SDL_Rect dest) : m_dest(dest), m_screen(dest),m_isSolid(true) { 
		std::cout << "OBJECT CREATED\n";
	}
	Object(SDL_Rect dest, SDL_Rect* playerDest) : m_dest(dest), m_screen(dest), m_isSolid(true) {
		Init(playerDest);
		std::cout << "OBJECT CREATED\n";
	}
	virtual ~Object() {
		std::cout << "OBJECT DESTROYED\n";
	}
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual SDL_Rect* GetSrc() = 0;
	virtual SDL_Rect* GetDest() = 0;
	virtual SDL_Rect* GetScreen() = 0;
	virtual SDL_Texture* GetTex() {
		return m_tex;
	}
	inline virtual void UpdatePositionRelativeToPlayer() {
		SetCamera();
		if (CheckForChange()) {
			Vec2 vec2 = CalculateChange();
			ChangeDestPosFor(vec2);
			ChangeScreenPosFor(vec2);
		}
	}
	inline virtual void SetScreen(SDL_Rect newScreen) {
		m_screen = newScreen;
	}
	inline virtual void SetDest(SDL_Rect newDest) {
		m_dest = newDest;
	}
	inline virtual void ChangeScreenPosFor(Vec2 vec2) {
		m_screen.x += vec2.m_x;
		m_screen.y += vec2.m_y;
	}
	inline virtual void SetScreenPos(Vec2 vec2) {
		m_screen.x = vec2.m_x;
		m_screen.y = vec2.m_y;
	}
	inline virtual void ChangeDestPosFor(Vec2 vec2) {
		m_dest.x += vec2.m_x;
		m_dest.y += vec2.m_y;
	}
	inline virtual void SetDestPos(Vec2 vec2) {
		m_dest.x = vec2.m_x;
		m_dest.y = vec2.m_y;
	}
	inline virtual Vec2 CalculateDestScreenChange() {
		Vec2 vec2;
		vec2.m_x = m_dest.x - m_screen.x;
		vec2.m_y = m_dest.y - m_screen.y;
		return vec2;
	}
	inline virtual void SetSolid(bool isSolid) {
		m_isSolid = isSolid;
	}
protected:
	SDL_Rect m_src;
	SDL_Rect m_dest;
	SDL_Rect m_screen;
	SDL_Renderer* m_ren;
	SDL_Texture* m_tex;
	int m_angle;

	bool m_isSolid;
};

