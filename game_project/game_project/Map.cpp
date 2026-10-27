#include "Map.h"
#include "TextureManager.h"
#include <vector>
// #include "SDL_gpu.h"


namespace HeArc::RPG {
	Map::Map()
	{
		// load the textures
		m_water = TextureManager::LoadTexture("Resources/Tileset/water.png");
		m_grass = TextureManager::LoadTexture("Resources/Tileset/grass.png");
		m_dirt = TextureManager::LoadTexture("Resources/Tileset/dirt.png");
	}
	
} // namespace HeArc::RPG