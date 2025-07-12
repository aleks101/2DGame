#pragma once

#include <SDL.h>

#include "Vec2.h"
#include "Log.h"

class Camera {
private:
	//player dest
	SDL_Rect* cameraPos;
	SDL_Rect prevCamera;
	int prevXoffset, prevYoffset;
public:
	Camera();
	bool CheckForChange();
	Vec2 CalculateChange();
	void SetCamera();
	void Init(SDL_Rect* _cameraPos);
};