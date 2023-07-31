#include "Map.h"

Map::Map(SDL_Rect* playerRect) : m_playerRect(playerRect) {
	std::cout << "MAP CONSTRUCTED\n";
}
Map::~Map() {
	std::cout << "MAP DESTRUCTED\n";
}
void Map::Update() {
	for (auto& tile : m_tiles)
		tile.UpdatePositionRelativeToPlayer();
	Render();
}
void Map::Render() {
	for (auto& tile : m_tiles)
		tile.Update();
}
void Map::AddLayer(SDL_Renderer* ren, std::string filePath, std::vector<TexID> textures, Vec2 startPos, int size, bool isSolid) {
	std::ifstream data;
	data.open(filePath);
	if (data.is_open()) {
		int width, height, id;
		data >> width >> height;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				data >> id;
				for (int k = 0; k < textures.size(); k++) {
					if (textures[k].id == id) {
						m_tiles.push_back(Tile(ren, textures[k].tex, { (int)startPos.x + size * j, (int)startPos.y + size * i, size, size }, m_playerRect, isSolid));
						break;
					}
				}
			}
		}
		std::cout << "LAYER ADDED\n";
	}
	else
		std::cout << "MAP FILE " << filePath << " NOT FOUND\n";
	data.close();
}
void Map::RemoveTile(int index) {
	if(m_tiles.begin()+index <= m_tiles.end())
		m_tiles.erase(m_tiles.begin() + index);
}
void Map::MoveTilesFor(Vec2 newPos) {
	for (auto& tile : m_tiles) {
		tile.ChangeDestPosFor(newPos);
		tile.ChangeScreenPosFor(newPos);
	}
}
void Map::MoveTilesTo(Vec2 newPos) {
	for (auto& tile : m_tiles) {
		tile.SetDestPos(newPos);
		tile.SetScreenPos(newPos);
	}
}