#pragma once

#include <SDL.h>
#include <iostream>
#include "Timer.h"
#include "Log.h"

template<int T>
class Animation
{
private:
	bool m_finished;
	bool m_loop;
	bool m_stop;

	int m_frames;
	int m_currFrame;
	float* m_frameDuration[T] = NULL;
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
};



template<int T>
Animation<T>::Animation() : m_frameDuration(nullptr), m_srcRect(nullptr), m_startX(0), m_startY(0), m_width(0), m_height(0), m_frames(T) {
	m_loop = false;
	m_finished = false;
	m_currFrame = 0;
	m_time = 0;
	m_row = 0;
	m_stop = false;
}
template<int T>
Animation<T>::~Animation() {
	for (int i = 0; i < m_frames; i++) {
		delete m_frameDuration[i];
		m_frameDuration[i] = nullptr;
	}
}
template<int T>
void Animation<T>::Init(SDL_Rect* sourceRect, int startX, int startY, int width, int height, int frames) {
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
template<int T>
void Animation<T>::Clean() {
	if (m_frameDuration != NULL)
		delete[] m_frameDuration;
	m_frameDuration = NULL;
}
template<int T>
void Animation<T>::SetFrameDuration(int frame, float duration) {
	if (frame < m_frames)
		m_frameDuration[frame] = duration;
}
template<int T>
void Animation<T>::Animate() {
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
template<int T>
void Animation<T>::SetLooping(bool loop) {
	m_loop = loop;
}
template<int T>
bool Animation<T>::IsFinished() {
	return m_finished;
}
template<int T>
void Animation<T>::SkipToFrame(int frame) {
	m_currFrame = frame;
}
template<int T>
void Animation<T>::ChangeRow(int row) {
	m_row = row;
}
template<int T>
void Animation<T>::Stop() {
	m_stop = true;
}
template<int T>
void Animation<T>::Resume() {
	m_stop = false;
}
template<int T>
void Animation<T>::Reset() {
	m_currFrame = 0;
	m_time = 0;
}