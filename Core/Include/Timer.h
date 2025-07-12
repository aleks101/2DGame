#pragma once

#include <SDL.h>

class Timer
{
private:
	unsigned int m_start;
	unsigned int m_stop;
	unsigned int m_pausedTime;
	bool m_isPaused;
public:
	Timer();
	void Start();
	void Stop();
	void Resume();
	void Pause();
	unsigned int GetSec();
	unsigned int GetMili();
	unsigned int GetDurationMili();
	unsigned int GetDurationSec();
};
class Time {
private:
	static float s_prevTime;
public:
	static float deltaTime;
	static void CalcDeltaTime();
};