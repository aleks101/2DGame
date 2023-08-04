#pragma once

#include <ctime>

#include "App.h"
#include "Assets.h"
#include "Map.h"
#include "Player.h"
#include "Collision.h"
#include "PowerUp.h"
#include "Follower.h"

class Game
{
private:
	SDL_Event ev;
	SDL_Renderer* m_ren;

	Player* player;
	Map* map;

	std::vector<Object*> fixedObjects;
	std::vector<PowerUp*> powerUps;
	std::vector<Entity*> entities;

	SDL_Texture* sceneTexture;

	bool isRunning;
public:
	Game();
	~Game();
	void Setup();
	void Quit();
	void MainLoop();
	template<typename T>
	void DeleteElement(std::vector<T> container, int index) {
		delete container[index];
		container.erase(container.begin() + index);
	}
};

