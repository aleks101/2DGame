#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Camera.h"
#include "Log.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT  720

class Object : private Camera
{
public:
	Object(SDL_Rect dest) : m_dest(dest), m_screen(dest),m_isSolid(true) { 
		m_playerRect = NULL;
		LOG("OBJECT CREATED\n");
	}
	Object(SDL_Rect dest, SDL_Rect* playerDest) : m_dest(dest), m_screen(dest), m_isSolid(true), Camera(){
		m_playerRect = playerDest;
		Init(playerDest);
		LOG("OBJECT CREATED\n");
	}
	virtual ~Object() {
		LOG("OBJECT DESTROYED\n");
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
	inline virtual Vec2 GetPos() {
		return Vec2(m_dest.x, m_dest.y);
	}

	bool m_isSolid;
	SDL_Rect* m_playerRect;
protected:
	SDL_Rect m_src;
	SDL_Rect m_dest;
	SDL_Rect m_screen;
	SDL_Renderer* m_ren;
	SDL_Texture* m_tex;
	int m_angle;
};

