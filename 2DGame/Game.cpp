#include "Game.h"

Game::Game() {
	App::ApplicationStart("2D game");
	m_ren = App::renderer;
}
Game::~Game() {
	delete player;
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	Assets::CleanTextures();
	App::ApplicationQuit();
}
void Game::Setup() {
	srand(time(NULL));

	isRunning = true;
	//dodaj texture
	Assets::AddTexture(m_ren, "Files/Images/blue.png", 0);
	Assets::AddTexture(m_ren, "Files/Images/red.png", 0);

	player = new Player(m_ren, Assets::GetTexture("Files/Images/red.png"), &ev, { 600, 350, 50, 50 });

	objects.push_back(new Tile(m_ren, Assets::GetTexture("Files/Images/blue.png"), { 100, 100, 200, 200 }, player->GetDest()));
	//objects.push_back(new PowerUp(m_ren, Assets::GetTexture("Files/Images/red.png"), { 100, 500, 30, 30 }, Ability(0, 0, 0, 5)));
	//objects.push_back(new Particle(m_ren, Assets::GetTexture("Files/Images/blue.png"), { 100, 500, 30, 30 }, player->GetDest(), 1.5f, Vec2(-2, 2), 8));
	//tile = new Tile(m_ren, Assets::GetTexture("Files/Images/blue.png"), { 100, 100, 200, 200
	powerUp = new PowerUp(m_ren, Assets::GetTexture("Files/Images/blue.png"), { 100, 500, 30, 30 }, player->GetDest(), Ability(0,0,0,5));
	Init(player->GetDest());

	MainLoop();
}
void Game::Quit() {
	isRunning = false;
}
void Game::DeleteObject(int index) {
	delete objects[index];
	objects.erase(objects.begin() + index);
}
void Game::MainLoop() {
	while (isRunning) {
		SDL_PollEvent(&ev);
		if (App::ApplicationCheckQuit(ev)) {
			Quit();
		}
		else {
			//posodobi objekte
			for (int i = 0; i < objects.size(); i++) {
				objects[i]->Update();
				objects[i]->UpdatePositionRelativeToPlayer();
			}
			if (powerUp != NULL) {
				powerUp->Update();
				powerUp->UpdatePositionRelativeToPlayer();
				if(coll::CheckCollisionAABB(*powerUp->GetDest(), *player->GetDest()))
					powerUp->Destroy();
				if (powerUp->m_canBeDestroyed) {
					delete powerUp;
					powerUp = NULL;
				}
			}
			player->Update();

			for (int i = 0; i < objects.size(); i++) {
				for (int j = 0; j < player->GetBullets().size(); j++) {
					if (coll::CheckCollisionAABB(*objects[i]->GetScreen(), *player->GetBullets()[j]->GetScreen())) {
						player->GetBullets()[j]->Destroy();
					}
				}
			}

			App::ApplicationRender();
		}
	}
}