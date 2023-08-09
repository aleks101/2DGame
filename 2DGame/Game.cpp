#include "Game.h"

Game::Game() {
	App::ApplicationStart("2D game");
	m_ren = App::renderer;
}
Game::~Game() {
	delete player;
	delete map;
	delete playerHealth;
	delete ammoText;
	for (int i = 0; i < fixedObjects.size(); i++)
		if (fixedObjects[i] != NULL) {
			delete fixedObjects[i];
			fixedObjects[i] = NULL;
		}
	LOG("fixedObjects deleted\n");
	for (int i = 0; i < powerUps.size(); i++)
		if (powerUps[i] != NULL) {
			delete powerUps[i];
			powerUps[i] = NULL;
		}
	LOG("powerUps deleted\n");
	for (int i = 0; i < entities.size(); i++)
		if (entities[i] != NULL) {
			delete entities[i];
			entities[i] = NULL;
		}
	LOG("entities deleted\n");
	if (rifle != NULL)
		delete rifle;

	Assets::CleanTextures();
	Assets::CleanFonts();
	Assets::CleanMusic();
	Assets::CleanSounds();

	App::ApplicationQuit();
}
void Game::Setup() {
	srand(time(0));

	isRunning = true;
	//dodaj texture
	Assets::AddTexture(m_ren, "Files/Images/blue.png", IMG_INIT_PNG);
	Assets::AddTexture(m_ren, "Files/Images/red.png", IMG_INIT_PNG);
	Assets::AddTexture(m_ren, "Files/Images/player.jpg", IMG_INIT_JPG);
	Assets::AddTexture(m_ren, "Files/Images/tile.jpg", IMG_INIT_JPG);
	Assets::AddTexture(m_ren, "Files/Images/Rifle.jpg", IMG_INIT_JPG);

	Assets::AddFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf", 22);

	sceneTexture = SDL_CreateTexture(m_ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	//SDL_SetTextureBlendMode(Assets::GetTexture("Files/Images/blue.png"), SDL_BLENDMODE_BLEND);
	//SDL_SetTextureBlendMode(Assets::GetTexture("Files/Images/red.png"), SDL_BLENDMODE_BLEND);

	player = new Player(m_ren, Assets::GetTexture("Files/Images/player.jpg"), &ev, { 600, 350, 50, 50 }, 1000);

	map = new Map(player);
	map->AddLayer(m_ren, "Files/Maps/map.txt", { TexID(Assets::GetTexture("Files/Images/tile.jpg"), 2) }, Vec2(150, 150), 50, true);

	entities.push_back(new Follower(m_ren, Assets::GetTexture("Files/Images/red.png"), { 500, 250, 50 ,50 }, player, 100, 3.7f, 1.7f, 1, 500, 300));
	powerUps.push_back(new PowerUp(m_ren, Assets::GetTexture("Files/Images/blue.png"), { 100, 500, 25, 25 }, player->GetDest(), Ability(0,0,0,5)));

	playerHealth = new Text(m_ren, Vec2(0, 0), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "health", { 255, 255, 255, 255 });
	playerHealth->SetNoChangeText("Health: ");

	ammoText = new Text(m_ren, Vec2(0, 20), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "ammo", { 255, 255, 255, 255 });

	SDL_Rect pos = { 500, 500, 25, 25 };
	rifle = new Weapon<15>(m_ren, Assets::GetTexture("Files/Images/Rifle.jpg"), &ev, pos, player->GetDest(), player->GetScreen(), 75, true, 7.5f, 20, 12, 6);
	rifle->AddAmmo(75);

	ammo = new Ammo(m_ren, Assets::GetTexture("Files/Images/Rifle.jpg"), { 100, 700, 10, 10 }, player, 50);

	MainLoop();
}
void Game::Quit() {
	isRunning = false;
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

			map->Update();
			for (int i = 0; i < player->GetBullets().size(); i++) {
				if(map->CheckCollisionScreen(player->GetBullets()[i]))
					player->GetBullets()[i]->Destroy();
			}
			//update fixed objects
			for (auto& object : fixedObjects) {
				object->Update();
				object->UpdatePositionRelativeToPlayer();
				for (int j = 0; j < player->GetBullets().size(); j++) {
					if (coll::CheckCollisionAABB(object->GetScreen(), player->GetBullets()[j]->GetScreen())) {
						player->GetBullets()[j]->Destroy();
					}
				}
			}
			//update powerups
			for (auto& powerUp : powerUps) {
				if (powerUp != NULL) {
					powerUp->Update();
					powerUp->UpdatePositionRelativeToPlayer();
					if (coll::CheckCollisionAABB(powerUp->GetDest(), player->GetDest()))
						powerUp->Destroy();
					if (powerUp->m_canBeDestroyed) {
						delete powerUp;
						powerUp = NULL;
					}
				}
			}
			//update entities
			for (auto& entity : entities) {
				if(entity!=NULL){
					if (entity->GetHealth() <= 0) {
						delete entity;
						entity = NULL;
					}
					else {
						entity->Update();
						entity->UpdatePositionRelativeToPlayer();
						for (int j = 0; j < player->GetBullets().size(); j++) {
							if (coll::CheckCollisionAABB(entity->GetScreen(), player->GetBullets()[j]->GetScreen())) {
								entity->RemoveHealth(player->GetBullets()[j]->m_damage);
								player->GetBullets()[j]->Destroy();
							}
						}
					}
				}
			}
			if (rifle != NULL) {
				rifle->Update();
				rifle->UpdatePositionRelativeToPlayer();
				if (coll::CheckCollisionAABB(player->GetDest(), rifle->GetDest())) {
					player->m_gun = &rifle;
					rifle->m_isPickedUp = true;
				}
			}
			if (ammo != NULL) {
				ammo->Update();
				ammo->UpdatePositionRelativeToPlayer();
				if (!ammo->m_isAlive) {
					delete ammo;
					ammo = NULL;
				}
			}

			//update player
			player->Update();
			if (!player->IsAlive())
				isRunning = false;
			//update text
			if (rifle!=NULL && rifle->m_isPickedUp) {
				ammoText->Update();
				ammoText->ChangeText((*player->m_gun)->GetAmmo());
			}
			playerHealth->Update();
			playerHealth->ChangeText(player->GetHealth());

			SDL_SetRenderTarget(m_ren, NULL);
			SDL_RenderClear(m_ren);
			SDL_SetRenderDrawColor(m_ren, 0, 0, 0, 255);
			SDL_RenderCopy(m_ren, sceneTexture, NULL, NULL);

			App::ApplicationRender();
		}
	}
}