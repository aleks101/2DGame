#include "Player.h"

Player::Player(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest, float health) : 
	Object(dest), Entity(health), m_ev(ev), m_attackRange(550), m_xClick(0), m_yClick(0) {
	m_ren = ren;
	m_tex = tex;
	m_velocity = Vec2(5.0f, 5.0f);
	for (int i = 0; i < 30; i++)
		m_bullets[i] = NULL;

	//Init(&dest);
}
void Player::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Player::Update() {
	SDL_GetMouseState(&m_xMouse, &m_yMouse);
	if (m_health <= 0)
		m_isAlive = false;
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
		for (int i = 0; i < 30; i++) {
			if (m_bullets[i] != NULL)
				m_bullets[i]->UpdatePositionRelativeToPlayer();
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
		ChangeDestPosFor(Vec2(0, -m_velocity.y));
	else if (m_down)
		ChangeDestPosFor(Vec2(0, m_velocity.y));
	if (m_right)
		ChangeDestPosFor(Vec2(m_velocity.x, 0));
	else if (m_left)
		ChangeDestPosFor(Vec2(-m_velocity.x, 0));

	if (m_dest.x < 20)
		ChangeDestPosFor(Vec2(m_velocity.x, 0));
	if(m_dest.y < 20)
		ChangeDestPosFor(Vec2(0, m_velocity.y));
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
	int size=20;
	for (int i = 0; i < 30; i++) {
		if (m_bullets[i] == NULL) {
			m_bullets[i] = new Bullet(m_ren, m_tex, {m_dest.x+m_dest.w/2 - size/2, m_dest.y+m_dest.h/2 - size/2, size, size}, 
				GetDest(), Vec2(m_screen.x + m_screen.w / 2 - size / 2, m_screen.y + m_screen.h / 2 - size / 2), 
				Vec2(m_xClick, m_yClick), 9, 0, 0, 3);
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