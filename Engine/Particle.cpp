#include "Particle.h"

Particle::Particle(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect dest, SDL_Rect screen, SDL_Rect* player, Vec2 velocity, float lifeTime) :
	Object(dest, player) {
	m_ren = ren;
	m_tex = tex;
	m_screen = screen;
	m_lifetime = lifeTime;
	m_velocity = velocity;
	m_isDead = false;
	m_opacity = 255;
	m_timer.Start();
}
Particle::~Particle() {
	m_timer.Stop();
}
void Particle::Render() {
	SDL_SetTextureAlphaMod(m_tex, m_opacity); 
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Particle::Update() {
	if (m_lifetime > ((float)m_timer.GetMili())/1000) {
		m_opacity -= rand()%8;
		Move();
		Render();
	}
	else {
		m_isDead = true;
	}
}
void Particle::Move() {
	ChangeDestPosFor(m_velocity);
	ChangeScreenPosFor(m_velocity);
}