#include "Player.h"

Player::Player(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest, float health) : 
	Entity(dest, health), m_ev(ev), m_attackRange(550), m_xClick(0), m_yClick(0) {
	m_ren = ren;
	m_tex = tex;
	m_velocity = Vec2(0, 0);

	m_gun = new Weapon<30>(m_ren, m_tex, m_ev, m_dest, GetDest(), Vec2(m_screen.x, m_screen.y), 25, true, 2.5f, 30, 15, 4);
	m_gun->PickUp();
	m_gun->AddAmmo(300);

	for (int i = 0; i < 30; i++)
		m_bullets[i] = NULL;
}
Player::~Player() {
	for (int i = 0; i < 30; i++) {
		if (m_bullets[i] != NULL) {
			delete m_bullets[i];
			m_bullets[i] = NULL;
		}
	}
	delete m_gun;
}
void Player::Render() {
	SDL_RenderCopy(m_ren, m_tex, NULL, &m_screen);
}
void Player::Update() {
	SDL_GetMouseState(&m_xMouse, &m_yMouse);
	if (m_health <= 0)
		m_isAlive = false;
	//if (CheckForAttack()) {
	//	m_xClick = m_xMouse;
	//	
	//	Attack();
	//}
	//for (int i = 0; i < 30; i++) {
	//	if (m_bullets[i] != NULL && !m_bullets[i]->m_alive) {
	//		delete m_bullets[i];
	//		m_bullets[i] = NULL;
	//	}
	//	for (int i = 0; i < 30; i++) {
	//		if (m_bullets[i] != NULL)
	//			m_bullets[i]->UpdatePositionRelativeToPlayer();
	//	}
	//	if (m_bullets[i] != NULL)
	//		m_bullets[i]->Update();
	//}
	if (CheckForAttack()) {
		m_xClick = m_xMouse;
		m_yClick = m_yMouse;
		m_gun->Shoot(m_xClick, m_yClick);
	}
	if (m_ev->type == SDL_KEYDOWN) {
		if (m_ev->key.keysym.sym == SDLK_r)
			m_gun->Reload();
	}
	m_gun->Update();
	Move();
	Render();
}
void Player::Move() {
	if (m_ev->type == SDL_KEYDOWN) {
		switch (m_ev->key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			m_up = true;
			m_down = false;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			m_left = true;
			m_right = false;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			m_down = true;
			m_up = false;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			m_right = true;
			m_left = false;
			break;
		}
	}
	else if (m_ev->type == SDL_KEYUP) {
		switch (m_ev->key.keysym.sym) {
		case SDLK_UP:
		case SDLK_w:
			m_up = false;
			break;
		case SDLK_LEFT:
		case SDLK_a:
			m_left = false;
			break;
		case SDLK_DOWN:
		case SDLK_s:
			m_down = false;
			break;
		case SDLK_RIGHT:
		case SDLK_d:
			m_right = false;
			break;
		}
	}
	if (m_up)
		m_velocity.y = -m_speed;
	else if (m_down)
		m_velocity.y = m_speed;
	else
		m_velocity.y = 0;

	if (m_right)
		m_velocity.x = m_speed;
	else if (m_left)
		m_velocity.x = -m_speed;
	else
		m_velocity.x = 0;

	ChangeDestPosFor(m_velocity);
	if (m_dest.x < 20)
		ChangeDestPosFor(Vec2(m_speed, 0));
	if(m_dest.y < 20)
		ChangeDestPosFor(Vec2(0, m_speed));
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
	int size = 15;
	for (int i = 0; i < 30; i++) {
		if (m_bullets[i] == NULL) {
			m_bullets[i] = new Bullet(m_ren, m_tex, {m_dest.x+m_dest.w/2 - size/2, m_dest.y+m_dest.h/2 - size/2, size, size}, 
				GetDest(), Vec2(m_screen.x + m_screen.w / 2 - size / 2, m_screen.y + m_screen.h / 2 - size / 2), 
				Vec2(m_xClick, m_yClick), 9, 30, 0, 3);
			break;
		}
	}
}
std::vector<Bullet*> Player::GetBullets() {
	std::vector<Bullet*> bullets;
	//for (int i = 0; i < 30; i++)
	//	if (m_bullets[i] != NULL)
	//		bullets.push_back(m_bullets[i]);
	//return bullets;
	if (m_gun != NULL) {
		bullets = m_gun->GetBullets();
	}
	return bullets;
}