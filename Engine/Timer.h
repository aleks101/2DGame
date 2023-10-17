#pragma once

#include <SDL.h>

class Timer
{
private:
	unsigned int m_start;
	unsigned int m_stop;
	unsigned int m_pausedTime;
	bool m_isPaused;
	static float s_prevTime;
public:
	Timer();
	static void CalcDeltaTime();
	void Start();
	void Stop();
	void Resume();
	void Pause();
	unsigned int GetSec();
	unsigned int GetMili();
	unsigned int GetDurationMili();
	unsigned int GetDurationSec();

	static float deltaTime;
};

