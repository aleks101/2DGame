#pragma once

#include <string>
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
	SDL_Texture* sceneTexture;

	bool isInit;
	bool isStartUp;
	bool isPaused;
	bool isRunning;

	int level;
	int numOfEasyEnemies;
	int numOfNormalEnemies;
	int numOfHardEnemies;
	int numOfBosses;
	unsigned int timeoutTime;
	float timePassed = 0;
	std::string playerNamestring;

	Player* player;
	Map* map;
	Weapon<15>* rifle;
	Collectable* ammo;
	FileManager* highScore;

	std::vector<Object*> fixedObjects;
	std::vector<PowerUp*> powerUps;
	std::vector<Entity*> entities;

	Text* playerName;
	Text* playerHealth;
	Text* ammoText;
	Text* levelText;
	Text* pauseText1;
	Text* score;
	Text* enterName;

	Button* resumeButton;
	Button* quitButton;
	Button* exitButton;
public:
	Game();
	~Game();
	void Setup();
	void Quit();
	void MainLoop();

	void GameLoop();
	void StartupLoop();
	void PauseLoop();
	void Clean();

	template<typename T>
	void DeleteElement(std::vector<T> container, int index) {
		delete container[index];
		container.erase(container.begin() + index);
	}
};

