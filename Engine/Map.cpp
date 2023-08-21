#include "Map.h"

Map::Map(Entity* player) : m_player(player) {
	LOG("MAP CONSTRUCTED\n");
}
Map::~Map() {
	LOG("MAP DECONSTRUCTED\n");
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
	SDL_Rect* screen;
	for (auto& tile : m_tiles) {
		screen = tile.GetScreen();
		tile.Update();
	}
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
						m_tiles.push_back(Tile(ren, textures[k].tex, { static_cast<int>(startPos.x) + size * j, static_cast<int>(startPos.y) + size * i, size, size }, m_player->GetDest(), isSolid));
						break;
					}
				}
			}
		}
		LOG("LAYER ADDED\n");
	}
	else {
		LOG("MAP FILE ");
		LOG(" NOT FOUND\n");
	}
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
bool Map::CheckCollisionDest(Object* object) {
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (coll::CheckCollisionAABB(tile.GetDest(), object->GetDest())) {
				return true;
			}
		}
	}
	return false;
}
bool Map::CheckCollisionScreen(Object* object) {
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (coll::CheckCollisionAABB(tile.GetScreen(), object->GetScreen())) {
				return true;
			}
		}
	}
	return false;
}
bool Map::CheckCollision(Object* object, bool destOrScreen, bool XorY) {
	//destOrScreen : true=dest, false=screen
	//XorY : true=x, false=y
	for (auto& tile : m_tiles) {
		if (tile.m_isSolid) {
			if (destOrScreen) {
				if (coll::CheckCollisionAABB(tile.GetDest(), object->GetDest())) {
					if (XorY) {
						if (coll::CheckCollisionX(tile.GetDest(), object->GetDest()))
							return true;
					}
					else {
						if (coll::CheckCollisionY(tile.GetDest(), object->GetDest()))
							return true;
					}
				}
			}
			else {
				if (coll::CheckCollisionAABB(tile.GetScreen(), object->GetScreen())) {
					if (XorY) {
						if (coll::CheckCollisionX(tile.GetScreen(), object->GetScreen()))
							return true;
					}
					else {
						if (coll::CheckCollisionY(tile.GetScreen(), object->GetScreen()))
							return true;
					}
				}
			}
		}
	}
	return false;
}