#pragma once

#include <fstream>

#include "Entity.h"
#include "Tile.h"
#include "Collision.h"
#include "Log.h"

struct TexID {
	TexID(SDL_Texture* _tex, int _id) : tex(_tex), id(_id) {}
	TexID(const TexID& texID) : tex(texID.tex), id(texID.id) {}
	SDL_Texture* tex;
	int id;
};
class Map
{
private:
	std::vector<Tile> m_tiles;
	Entity* m_player;
public:
	Map(Entity* player);
	~Map();
	void Update();
	void Render();
	void AddLayer(SDL_Renderer* ren, std::string filePath, std::vector<TexID> textures, Vec2 startPos, int size, bool isSolid);
	void RemoveTile(int index);
	void MoveTilesFor(Vec2 newPos);
	void MoveTilesTo(Vec2 newPos);
	bool CheckCollision(Object* entity);
};

