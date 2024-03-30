#include "Player.h"

Player::Player(SDL_Renderer* ren, SDL_Texture* tex, SDL_Event* ev, SDL_Rect dest, float health) : 
	Entity(dest, health), m_ev(ev), m_attackRange(550), m_xClick(0), m_yClick(0){
	m_ren = ren;
	m_tex = tex;
	m_velocity = Vec2(0, 0);

	m_light = Light(ren, GetCenter(), m_dest.w-16, 190, { 255, 255, 255, 255 }, SDL_BLENDMODE_ADD);
	animation.Init(GetSrc(), 0, 0, 50, 50, 4);
	animation.SetLooping(true);
	for (int i = 0; i < 4; i++) {
		animation.SetFrameDuration(i, 0.3);
	}

	m_gun = NULL;
}
Player::~Player() {
	animation.Clean();
	LOG("PLAYER DECONSTRUCTED\n");
}
void Player::Render() {
	animation.Animate();

	SDL_RenderCopy(m_ren, m_tex, &m_src, &m_screen);
	//m_light.DrawLight();
}
void Player::Update() {
	SDL_GetMouseState(&m_xMouse, &m_yMouse);
	if (m_health <= 0)
		m_isAlive = false;
	if (CheckForAttack() && m_gun != NULL) {
		m_xClick = m_xMouse;
		m_yClick = m_yMouse;
		m_gun->Shoot(m_xClick, m_yClick);
	}
	if (m_ev->type == SDL_KEYDOWN) {
		if (m_ev->key.keysym.sym == SDLK_r && m_gun != NULL)
				m_gun->Reload();
		if (m_ev->key.keysym.sym == SDLK_q && m_gun != NULL) {
			m_gun->m_isPickedUp = false;
			m_gun->SetDestPos(Vec2(m_dest.x - m_dest.w, m_dest.y - m_dest.h));
			m_gun->SetScreenPos(Vec2(m_screen.x - m_screen.w, m_screen.y - m_screen.h));
			m_gun = NULL;
		}
	}
	if (m_gun != NULL) {
		for (int j = 0; j < GetBullets().size(); j++) {
			if (Entity::CheckCollisionScreenWithMap(dynamic_cast<Object*>(GetBullets()[j]))) {
				GetBullets()[j]->Destroy();
			}
		}
		m_gun->Update();
	}
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
		return true;
	}
	return false;
}
void Player::Attack() {
	
}
std::vector<Bullet*> Player::GetBullets() {
	std::vector<Bullet*> bullets;
	if (m_gun != NULL)
		bullets = m_gun->GetBullets();
	return bullets;
}
void Player::AddScore(float score) {
	m_score += score;
}