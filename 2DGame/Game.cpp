#include "Game.h"
#include <string>

Game::Game() {
	App::ApplicationStart("Battlemania");
	m_ren = App::renderer;
}
Game::~Game() {
	highScore->WriteBinary(*player);
	Player t;
	highScore->ReadBinary(t, 0);
	LOG("PLAYER SCORE: " + std::to_string(t.m_score));
	highScore->ChangeFile("Files/Save/score.txt");
	highScore->Write(player->m_score);

	delete highScore;

	Clean();

	SDL_DestroyTexture(sceneTexture);

	Assets::CleanTextures();
	Assets::CleanFonts();
	Assets::CleanMusic();
	Assets::CleanSounds();

	App::ApplicationQuit();
}
void Game::Setup() {
	srand(time(0));

	isRunning = true;
	isInit = false;
	isPaused = false;
	isStartUp = true;

	highScore = new FileManager("Files/Save/highscore.bin");
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
	
	MainLoop();
}
void Game::Clean() {
	delete player; player = NULL;
	delete map; map = NULL;
	if (ammo != NULL) {
		delete ammo; ammo = NULL;
	}

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
	if (rifle != NULL) {
		delete rifle; rifle = NULL;
	}
	delete playerName; playerName = NULL;
	delete playerHealth; playerHealth = NULL;
	delete ammoText; ammoText = NULL;
	delete levelText; levelText = NULL;
	delete pauseText1; pauseText1 = NULL;
	delete score; score = NULL;
	//delete enterName; enterName = NULL;
	delete resumeButton; resumeButton = NULL;
	delete quitButton; quitButton = NULL;
	//delete exitButton; exitButton=NULL;
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

			if (isStartUp)
				StartupLoop();
			else {
				if (ev.type == SDL_KEYUP)
					if (ev.key.keysym.sym == SDLK_ESCAPE)
						isPaused = !isPaused;
				if(isPaused)
					PauseLoop();
				else
					GameLoop();
			}

			SDL_SetRenderTarget(m_ren, NULL);
			SDL_RenderClear(m_ren);
			SDL_SetRenderDrawColor(m_ren, 0, 0, 0, 255);
			SDL_RenderCopy(m_ren, sceneTexture, NULL, NULL);

			App::ApplicationRender();
		}
	}
}
void Game::GameLoop() {
	map->Update();
	for (int i = 0; i < player->GetBullets().size(); i++) {
		if (map->CheckCollisionScreen(player->GetBullets()[i]))
			player->GetBullets()[i]->Destroy();
	}
	//update fixed objects
	for (auto& object : fixedObjects) {
		object->Update();
		object->UpdatePositionRelativeToPlayer();
	}
	//update powerups
	for (auto& powerUp : powerUps) {
		if (powerUp != NULL) {
			powerUp->Update();
			powerUp->UpdatePositionRelativeToPlayer();
			if (powerUp->m_canBeDestroyed) {
				delete powerUp;
				powerUp = NULL;
			}
		}
	}
	//update entities
	for (auto& entity : entities) {
		if (entity != NULL) {
			if (entity->GetHealth() <= 0) {
				player->AddScore(entity->m_score);
				delete entity;
				entity = NULL;
			}
			else {
				entity->Update();
				entity->UpdatePositionRelativeToPlayer();
				for (int j = 0; j < player->GetBullets().size(); j++) {
					if (coll::CheckCollisionAABB(*entity->GetScreen(), *player->GetBullets()[j]->GetScreen())) {
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
		if (coll::CheckCollisionAABB(*player->GetDest(), *rifle->GetDest())) {
			player->m_gun = rifle;
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
	if (rifle != NULL && rifle->m_isPickedUp) {
		ammoText->Update();
		ammoText->ChangeText(player->m_gun->GetAmmo());
	}
	playerHealth->Update();
	playerHealth->ChangeText(player->GetHealth());
	playerName->Update();
	score->Update();
	score->ChangeText((int)(player->m_score));
	levelText->Update();
	levelText->ChangeText(level);

	int j = entities.size();
	for (int i = 0; i < entities.size(); i++)
		if (entities[i] == NULL)
			j--;
	if (j == 0)
		level++;
}
void Game::PauseLoop() {
	pauseText1->Update();
	resumeButton->Update();
	quitButton->Update();
	if (resumeButton->CheckMouseClick())
		isPaused = false;
	if (quitButton->CheckMouseClick()) {
		isStartUp = true;
		isInit = false;
		Clean();
	}
}
void Game::StartupLoop() {
	if (!isInit) {
		player = new Player(m_ren, Assets::GetTexture("Files/Images/player.jpg"), &ev, { 600, 350, 50, 50 }, 1000);

		map = new Map(player);
		map->AddLayer(m_ren, "Files/Maps/map.txt", { TexID(Assets::GetTexture("Files/Images/tile.jpg"), 2) }, Vec2(150, 150), 50, true);
		player->Entity::SetMap(map);

		rifle = new Weapon<15>(m_ren, Assets::GetTexture("Files/Images/Rifle.jpg"), &ev, { 500, 500, 25, 25 }, player->GetDest(), player->GetScreen(), 75, true, 7.5f, 20, 12, 6);
		rifle->AddAmmo(75);
		ammo = new Collectable(m_ren, Assets::GetTexture("Files/Images/Rifle.jpg"), { 100, 700, 10, 10 }, player, 50, 100, 0);

		entities.push_back(new Shooter(m_ren, Assets::GetTexture("Files/Images/red.png"), { 600, 300, 50 ,50 }, player, map, 5, 700, 500, 50, 1.5f, 16, 10.5f, 500, 60));		
		//entities.push_back(new Follower(m_ren, Assets::GetTexture("Files/Images/red.png"), { 500, 250, 50 ,50 }, player, map, 30, 100, 3.7f, 1.7f, 5, 500, 300));

		score = new Text(m_ren, Vec2(SCREEN_WIDTH - 180, 0), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "score", { 255, 255, 255, 255 });
		score->SetNoChangeText("Score: ");
		playerHealth = new Text(m_ren, Vec2(0, 20), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "health", { 255, 255, 255, 255 });
		playerHealth->SetNoChangeText("Health: ");
		playerName = new Text(m_ren, Vec2(0, 0), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "player", { 255, 255, 255, 255 });
		ammoText = new Text(m_ren, Vec2(0, 40), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "ammo", { 255, 255, 255, 255 });
		levelText = new Text(m_ren, Vec2(SCREEN_WIDTH - 180, 30), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "Level: ", { 255, 255, 255, 255 });
		levelText->SetNoChangeText("Level: ");

		pauseText1 = new Text(m_ren, Vec2(500, 150), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "Game is paused", { 255, 255, 255, 255 });
		resumeButton = new Button(m_ren, &ev, Vec2(100, 350), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "RESUME PLAYING", { 255, 255, 255, 255 }, { 255, 0, 0, 255 });
		quitButton = new Button(m_ren, &ev, Vec2(100, 400), Assets::GetFont("Files/Fonts/8-bit-operator/8bitOperatorPlus8-Regular.ttf"), "QUIT", { 255, 255, 255, 255 }, { 255, 0, 0, 255 });

		level = 1;
		playerNamestring = "";

		SDL_StartTextInput();
		isStartUp = true;
		isPaused = false;
		isInit = true;
	}

	playerName->Update();
	playerName->ChangeText(playerNamestring);
	if (ev.type == SDL_TEXTINPUT) {
		playerNamestring += ev.text.text;
	}
	else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && playerNamestring.size()) {
		playerNamestring.pop_back();
	}
	else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN && playerNamestring.size() >= 3) {
		isStartUp = false;
		playerName->ChangeText(playerNamestring);
		SDL_StopTextInput();
	}
}