#pragma once

#include "App.h"
#include "Assets.h"
#include "Tile.h"
#include "Player.h"
#include "Collision.h"
#include "PowerUp.h"
#include "Follower.h"

class Game : public Camera
{
private:
	SDL_Event ev;
	SDL_Renderer* m_ren;

	Player* player;
	PowerUp* powerUp;
	std::vector<Object*> objects;

	SDL_Texture* sceneTexture;

	bool isRunning;
public:
	Game();
	~Game();
	void Setup();
	void Quit();
	void MainLoop();
	void DeleteObject(int index);
};

