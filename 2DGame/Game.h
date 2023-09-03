#pragma once

#include <ctime>

#include "App.h"
#include "Assets.h"
#include "Map.h"
#include "Text.h"
#include "Light.h"
#include "Log.h"
#include "FileManager.h"
#include "Button.h"

#include "Player.h"
#include "PowerUp.h"
#include "Follower.h"
#include "Shooter.h"
#include "Weapon.h"
#include "Collectable.h"

class Game
{
private:
	SDL_Event ev;
	SDL_Renderer* m_ren;

	Text* score;

	Player* player;
	Map* map;
	Text* playerHealth;
	Text* ammoText;
	Weapon<15>* rifle;
	Collectable* ammo;

	FileManager* highScore;

	std::vector<Object*> fixedObjects;
	std::vector<PowerUp*> powerUps;
	std::vector<Entity*> entities;

	SDL_Texture* sceneTexture;

	Text* pauseText1;
	Button* resumeButton;

	bool isStartUp;
	bool isPaused;
	bool isRunning;
public:
	Game();
	~Game();
	void Setup();
	void Quit();
	void MainLoop();

	void GameLoop();
	void StartupLoop();
	void PauseLoop();

	template<typename T>
	void DeleteElement(std::vector<T> container, int index) {
		delete container[index];
		container.erase(container.begin() + index);
	}
};

