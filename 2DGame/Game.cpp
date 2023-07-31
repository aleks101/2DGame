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
	Assets::AddTexture(m_ren, "Files/Images/blue.png", IMG_INIT_PNG);
	Assets::AddTexture(m_ren, "Files/Images/red.png", IMG_INIT_PNG);
	sceneTexture = SDL_CreateTexture(m_ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	//SDL_SetTextureBlendMode(Assets::GetTexture("Files/Images/blue.png"), SDL_BLENDMODE_BLEND);
	//SDL_SetTextureBlendMode(Assets::GetTexture("Files/Images/red.png"), SDL_BLENDMODE_BLEND);

	player = new Player(m_ren, Assets::GetTexture("Files/Images/red.png"), &ev, { 600, 350, 50, 50 }, 1000);

	objects.push_back(new Tile(m_ren, Assets::GetTexture("Files/Images/blue.png"), { 100, 100, 200, 200 }, player->GetDest(), true));
	objects.push_back(new Follower(m_ren, Assets::GetTexture("Files/Images/red.png"), { 500, 250, 50 ,50 }, player->GetDest(), 100, 2.5f, 10, 300, 100));
	powerUp = new PowerUp(m_ren, Assets::GetTexture("Files/Images/blue.png"), { 100, 500, 25, 25 }, player->GetDest(), Ability(0,0,0,5));

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
			SDL_SetRenderTarget(m_ren, sceneTexture);
			SDL_SetRenderDrawColor(m_ren, 0, 0, 0, 0);
			SDL_RenderClear(m_ren);


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


			SDL_SetRenderTarget(m_ren, NULL);
			SDL_RenderClear(m_ren);
			SDL_SetRenderDrawColor(m_ren, 0, 0, 0, 255);
			SDL_RenderCopy(m_ren, sceneTexture, NULL, NULL);

			App::ApplicationRender();
		}
	}
}