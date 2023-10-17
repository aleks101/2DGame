#include "Animation.h"

Animation::Animation(SDL_Rect* sourceRect, int startX, int startY, int width, int height, int frames) : m_srcRect(sourceRect), m_startX(startX), m_startY(startY), m_width(width), m_height(height), m_frames(frames) {
	m_frameDuration = new uint32_t[frames];
	for (int i = 0; i < frames; i++)
		m_frameDuration[i] = 0;
	m_loop = false;
	m_finished = false;
	m_currFrame = 0;
}
Animation::~Animation() {
	delete[] m_frameDuration;
}
void Animation::SetFrameDuration(int frame, uint32_t duration) {
	m_frameDuration[frame] = duration;
}
void Animation::Animate() {

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