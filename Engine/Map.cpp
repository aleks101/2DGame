#include "Map.h"

Map::Map(Entity* player) : m_player(player) {
	std::cout << "MAP CONSTRUCTED\n";
}
Map::~Map() {
	std::cout << "MAP DESTRUCTED\n";
}
void Map::Update() {
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (coll::CheckCollisionAABB(tile.GetDest(), m_player->GetDest())) {
				if (coll::CheckCollisionX(tile.GetDest(), m_player->GetDest())) {
					m_player->ChangeDestPosFor(Vec2(-m_player->m_velocity.x, 0));
				}
				if (coll::CheckCollisionY(tile.GetDest(), m_player->GetDest())) {
					m_player->ChangeDestPosFor(Vec2(0, -m_player->m_velocity.y));
				}
			}
		}
	}
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
						m_tiles.push_back(Tile(ren, textures[k].tex, { (int)startPos.x + size * j, (int)startPos.y + size * i, size, size }, m_player->GetDest(), isSolid));
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
void Map::CheckCollision(Entity* entity) {
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (coll::CheckCollisionAABB(tile.GetDest(), entity->GetDest())) {
				if (coll::CheckCollisionX(tile.GetDest(), entity->GetDest())) {
					entity->ChangeDestPosFor(Vec2(-entity->m_velocity.x, 0));
					entity->ChangeScreenPosFor(Vec2(-entity->m_velocity.x, 0));
				}
				if (coll::CheckCollisionY(tile.GetDest(), entity->GetDest())) {
					entity->ChangeDestPosFor(Vec2(0, -entity->m_velocity.y));
					entity->ChangeScreenPosFor(Vec2(0, -entity->m_velocity.y));
				}
			}
		}
	}
}