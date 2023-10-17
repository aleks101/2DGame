#pragma once

#include <SDL.h>
#include "Timer.h"

class Animation
{
private:
	bool m_loop;
public:
	Animation(SDL_Texture* tex, SDL_Rect* sourceRect, int startX, int startY, int width, int height, int frames);
	void SetFrameDuration(int frame, unsigned int duration);
	void Animate();
	void SetLooping(bool isLooping);
	bool IsFinished();
	void SkipToFrame(int frame);
};
