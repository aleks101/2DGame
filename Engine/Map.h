#pragma once

#include "Tile.h"
#include <fstream>

struct TexID {
	SDL_Texture* tex;
	int id;
};
class Map
{
private:
	std::vector<Tile> m_tiles;
	SDL_Rect* m_playerRect;
public:
	Map(SDL_Rect* playerRect);
	~Map();
	void Update();
	void Render();
	void AddLayer(SDL_Renderer* ren, std::string filePath, std::vector<TexID> textures, Vec2 startPos, int size, bool isSolid);
	void RemoveTile(int index);
	void MoveTilesFor(Vec2 newPos);
	void MoveTilesTo(Vec2 newPos);
};

