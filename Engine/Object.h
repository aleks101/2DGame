#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Camera.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT  720

//#ifndef DEBUG
//#define LOG(msg) std::cout << msg << std::endl;
//#endif // !DEBUG


class Object : private Camera
{
public:
	Object(SDL_Rect dest) : m_dest(dest), m_screen(dest),m_isSolid(true) { 
		std::cout << "OBJECT CREATED\n";
	}
	Object(SDL_Rect dest, SDL_Rect* playerDest) : m_dest(dest), m_screen(dest), m_isSolid(true), Camera(){
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
			ChangeScreenPosFor(CalculateChange());
		}
	}
	inline virtual void SetScreen(SDL_Rect newScreen) {
		m_screen = newScreen;
	}
	inline virtual void SetDest(SDL_Rect newDest) {
		m_dest = newDest;
	}
	inline virtual void ChangeScreenPosFor(Vec2 vec2) {
		m_screen.x += vec2.x;
		m_screen.y += vec2.y;
	}
	inline virtual void SetScreenPos(Vec2 vec2) {
		m_screen.x = vec2.x;
		m_screen.y = vec2.y;
	}
	inline virtual void ChangeDestPosFor(Vec2 vec2) {
		m_dest.x += vec2.x;
		m_dest.y += vec2.y;
	}
	inline virtual void SetDestPos(Vec2 vec2) {
		m_dest.x = vec2.x;
		m_dest.y = vec2.y;
	}
	inline virtual void SetSolid(bool isSolid) {
		m_isSolid = isSolid;
	}
	inline virtual Vec2 GetCenter() {
		return Vec2(m_dest.x + m_dest.w / 2, m_dest.y + m_dest.h / 2);
	}

	bool m_isSolid;
protected:
	SDL_Rect m_src;
	SDL_Rect m_dest;
	SDL_Rect m_screen;
	SDL_Renderer* m_ren;
	SDL_Texture* m_tex;
	int m_angle;
};

