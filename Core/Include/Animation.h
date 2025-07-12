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
	float* m_frameDuration = NULL;
	float m_time;

	int m_row;
	int m_startX, m_startY, m_width, m_height;
	SDL_Rect* m_srcRect;
public:
	Animation();
	virtual ~Animation();
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
	void Clean();
};
/*
Animation::Animation() : m_frameDuration(nullptr), m_srcRect(nullptr), m_startX(0), m_startY(0), m_width(0), m_height(0) {
	m_loop = false;
	m_finished = false;
	m_currFrame = 0;
	m_time = 0;
	m_row = 0;
	m_stop = false;
}
Animation::~Animation() {
	//for (int i = 0; i < m_frames; i++) {
	//	delete m_frameDuration[i];
	//	m_frameDuration[i] = nullptr;
	//}
	delete m_frameDuration;
}
void Animation::Init(SDL_Rect* sourceRect, int startX, int startY, int width, int height, int frames) {
	m_srcRect = sourceRect;
	m_startX = startX;
	m_startY = startY;
	m_width = width;
	m_height = height;
	m_frames = frames;

	m_frameDuration = new float[frames];
	for (int i = 0; i < frames; i++)
		m_frameDuration[i] = 0;
	m_loop = false;
	m_finished = false;
	m_currFrame = 0;
	m_time = 0;
	m_row = 0;
	m_stop = false;
	m_srcRect->w = m_width;
	m_srcRect->h = m_height;
}
void Animation::Clean() {
	if (m_frameDuration != NULL)
		delete[] m_frameDuration;
	m_frameDuration = NULL;
}
void Animation::SetFrameDuration(int frame, float duration) {
	if (frame < m_frames)
		m_frameDuration[frame] = duration;
}
void Animation::Animate() {
	if (!m_stop) {
		if (m_loop)
			m_finished = false;
		if (!m_finished) {
			m_srcRect->x = m_startX + m_width * m_currFrame;
			m_srcRect->y = m_startY + m_height * m_row;

			if (m_frameDuration != nullptr && m_frameDuration[m_currFrame] <= m_time) {
				m_time = 0;
				m_currFrame++;
			}
			if (m_currFrame >= m_frames) {
				m_currFrame = 0;
				m_finished = true;
			}
			m_time += Time::deltaTime;
		}
	}
}
void Animation::SetLooping(bool loop) {
	m_loop = loop;
}
bool Animation::IsFinished() {
	return m_finished;
}
void Animation::SkipToFrame(int frame) {
	m_currFrame = frame;
}
void Animation::ChangeRow(int row) {
	m_row = row;
}
void Animation::Stop() {
	m_stop = true;
}
void Animation::Resume() {
	m_stop = false;
}
void Animation::Reset() {
	m_currFrame = 0;
	m_time = 0;
}
*/