#pragma once
#include <SDL.h>

class Animation
{
private:
	bool m_finished;
	bool m_loop;
	int m_frames;
	uint32_t* m_frameDuration;
	int m_currFrame;
	int m_startX, m_startY, m_width, m_height;
	SDL_Rect* m_srcRect;
public:
	Animation(SDL_Rect* sourceRect, int startX, int startY, int width, int height, int frames);
	~Animation();
	void SetFrameDuration(int frame, uint32_t duration);
	void Animate();
	void SetLooping(bool isLooping);
	bool IsFinished();
	void SkipToFrame(int frame);
};
