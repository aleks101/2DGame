#include "Player.h"

Player::Player(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest) : 
	Object(dest), m_ev(ev), m_xSpeed(6), m_ySpeed(6), m_attackRange(350), m_xClick(0), m_yClick(0) {
	m_ren = ren;
	m_tex = tex;
	for (int i = 0; i < 30; i++)
		m_bullets[i] = NULL;
	Init(&dest);
}
void Player::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Player::Update() {
	SDL_GetMouseState(&m_xMouse, &m_yMouse);
	if (CheckForAttack()) {
		m_xClick = m_xMouse;
		m_yClick = m_yMouse;
		Attack();
	}
	for (int i = 0; i < 30; i++) {
		if (m_bullets[i] != NULL && !m_bullets[i]->m_alive) {
			delete m_bullets[i];
			m_bullets[i] = NULL;
		}
		//SetCamera(GetDest());
		SetCamera();
		if (CheckForChange()) {
			Vec2 vec2 = CalculateChange();
			vec2.m_x = vec2.m_x;
			vec2.m_y = vec2.m_y;
			for (int i = 0; i < 30; i++) {
				if (m_bullets[i] != NULL)
					m_bullets[i]->ChangeDestPosFor(vec2);
					//m_bullets[i]->ChangeScreenPosFor(vec2);
			}
		}
		if (m_bullets[i] != NULL)
			m_bullets[i]->Update();
	}
	Move();
	Render();
}
void Player::Move() {
	if (m_ev->type == SDL_KEYDOWN) {
		switch (m_ev->key.keysym.sym) {
		case SDLK_w:
			m_up = true;
			m_down = false;
			break;
		case SDLK_a:
			m_left = true;
			m_right = false;
			break;
		case SDLK_s:
			m_down = true;
			m_up = false;
			break;
		case SDLK_d:
			m_right = true;
			m_left = false;
			break;
		}
	}
	else if (m_ev->type == SDL_KEYUP) {
		switch (m_ev->key.keysym.sym) {
		case SDLK_w:
			m_up = false;
			break;
		case SDLK_a:
			m_left = false;
			break;
		case SDLK_s:
			m_down = false;
			break;
		case SDLK_d:
			m_right = false;
			break;
		}
	}
	if (m_up)
		ChangeDestPosFor(Vec2(0, -m_ySpeed));
	else if (m_down)
		ChangeDestPosFor(Vec2(0, m_ySpeed));
	if (m_right)
		ChangeDestPosFor(Vec2(m_xSpeed, 0));
	else if (m_left)
		ChangeDestPosFor(Vec2(-m_xSpeed, 0));
}
bool Player::CheckForAttack() {
	int xCenter = m_screen.x + m_screen.w / 2, yCenter = m_screen.y + m_screen.h / 2;
	if (m_xMouse >= xCenter - m_attackRange && m_xMouse <= xCenter + m_attackRange && m_yMouse >= yCenter - m_attackRange && m_yMouse <= yCenter + m_attackRange) {
		if (m_ev->type == SDL_MOUSEBUTTONDOWN) {
			if (m_ev->button.button == SDL_BUTTON_LEFT) {
				return true;
			}
		}
	}
	return false;
}
void Player::Attack() {
	for (int i = 0; i < 30; i++) {
		if (m_bullets[i] == NULL) {
			m_bullets[i] = new Bullet(m_ren, m_tex, m_screen, Vec2(m_xClick, m_yClick), 9, 0, 0, 3);
			break;
		}
	}
}
std::vector<Bullet*> Player::GetBullets() {
	std::vector<Bullet*> bullets;
	for (int i = 0; i < 30; i++)
		if (m_bullets[i] != NULL)
			bullets.push_back(m_bullets[i]);
	return bullets;
}