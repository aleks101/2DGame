#pragma once

#include <SDL.h>
#include <iostream>
#include "Timer.h"
#include "Log.h"

class Animation
{
private:
	bool m_finished;
	bool m_loop;
	bool m_stop;

	int m_frames;
	int m_currFrame;
	float* m_frameDuration;
	float m_time;

	int m_row;
	int m_startX, m_startY, m_width, m_height;
	SDL_Rect* m_srcRect;
public:
	Animation();
	~Animation();
	void Init(SDL_Rect* sourceRect, int startX, int startY, int width, int height, int frames);

	void SetFrameDuration(int frame, float duration);
	void Animate();
	void SetLooping(bool isLooping);
	bool IsFinished();
	void SkipToFrame(int frame);
	void ChangeRow(int row);

	void Stop();
	void Resume();
	void Reset();
};
