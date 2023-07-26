#include "Timer.h"

Timer::Timer() {
	m_start = 0;
	m_stop = 0;
	m_pausedTime = 0;
	m_isPaused = false;
}
void Timer::Start() {
	m_start = SDL_GetTicks();
	m_stop = 0;
	m_pausedTime = 0;
	m_isPaused = false;
}
void Timer::Pause() {
	m_isPaused = true;
	m_pausedTime = SDL_GetTicks();
}
void Timer::Resume() {
	m_isPaused = false;
}
void Timer::Stop() {
	if(!m_isPaused && m_pausedTime==0)
		m_stop = SDL_GetTicks();
	else if (!m_isPaused && m_pausedTime != 0) {
		m_stop -= m_pausedTime;
	}
}
unsigned int Timer::GetDurationMili() {
	if(!m_isPaused)
		return m_stop - m_start;
	return 0;
}
unsigned int Timer::GetDurationSec() {
	if(!m_isPaused)
		return (m_stop - m_start) / 1000;
	return 0;
}
unsigned int Timer::GetSec() {
	if (!m_isPaused)
		return (SDL_GetTicks() - m_start) / 1000;
	return 0;
}
unsigned int Timer::GetMili() {
	if (!m_isPaused)
		return (SDL_GetTicks() - m_start);
	return 0;
}