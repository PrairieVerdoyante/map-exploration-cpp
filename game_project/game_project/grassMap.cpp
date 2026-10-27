#include "grassMap.h"
#include "TextureManager.h"
#include <unordered_map>

const int GRASS_TILE_HEIGHT = 7;
const int GRASS_TILE_WIDTH = 11;

const int MAP_WIDTH = 800;
const int MAP_HEIGHT = 640;

namespace HeArc::RPG {
	
	// map for the first level
	// forest
	int grassLvl1[TABLE_HEIGHT][TABLE_WIDTH] = { // 14x22, /**/ is a repere for drawing the map
		{41,	42,	42,	42,	42,	/**/42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	41},
		{42,	42,	0,	1,	2,	/**/42,	42,	0,	1,	1,	1,	2,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42},
		{42,	42,	10,	11,	12,	/**/42,	42,	14,	11,	11,	11,	12,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42},
		{42,	42,	20,	15,	22,	/**/42,	42,	14,	21,	21,	21,	22,	42,	42,	42,	0,	1,	2,	42,	42,	42,	42},
		{42,	42,	42,	13,	42,		42,	42,	13,	42,	42,	43,	42,	0,	1,	1,	11,	11,	11,	2,	42,	42,	42},
		{42,	42,	0,	11,	1,		1,	1,	11,	1,	1,	1,	1,	11,	11,	11,	11,	11,	11,	12,	42,	42,	42},
		{42,	42,	10, 15,	21,		21,	21,	21,	21,	21,	21,	21,	11,	11,	11,	11,	11,	11,	11,	2,	42,	42},
		{31,	31,	36,	22,	42,		42,	42,	42,	42,	42,	42,	42,	20,	11,	11,	11,	11,	11,	11,	12,	42,	42},
		{42,	42,	42,	42,	42,		33,	42,	42,	42,	42,	42,	42,	43,	10,	11,	11,	11,	11,	11,	22,	42,	42},
		{42,	42,	42,	42,	42,		42,	42,	42,	42,	33,	42,	42,	42,	10,	11,	11,	11,	11,	12,	42,	42,	42},
		{42,	42,	42,	42,	42,		42,	42,	42,	42,	42,	42,	42,	0,	11,	11,	11,	11,	11,	12,	42,	42,	42},
		{42,	0,	1,	1,	1,		1,	1,	1,	1,	1,	1,	1,	11,	11,	11,	11,	11,	11,	12,	42,	42,	42},
		{42,	20,	21,	21,	21,		21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	21,	22,	42,	42,	42},
		{42,	42,	42,	42,	42,		42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	42,	41}


	};
	
	

	GrassMap::GrassMap()
	{
		// load the grass texture
		m_grass = TextureManager::LoadTexture("Resources/Backgrounds/Tilesets/Landscape_tileSetGrass.png");

		// load the grass texture
		SDL_Surface* surface = IMG_Load("Resources/Backgrounds/Tilesets/Landscape_tileSetGrass.png");
		if (m_grass == nullptr) {
			// error handling
			std::cout << "Error: " << SDL_GetError() << std::endl;
		}
		else {
			// get the width and height of the texture
			m_grass = SDL_CreateTextureFromSurface(Game::renderer, surface);
			m_frameWidth = surface->w / GRASS_TILE_WIDTH;
			m_frameHeight = surface->h / GRASS_TILE_HEIGHT;

			// set the source and destination rectangles
			m_src.h = m_dest.h = m_frameHeight * 4;
			m_src.w = m_dest.w = m_frameWidth * 4;
			
		}

		// load the map
		LoadMap(grassLvl1);
	}
	
	
	void GrassMap::LoadMap(int arr[TABLE_HEIGHT][TABLE_WIDTH]) // lignes x colonnes
	{
		// Copy the array into the map
		for (int row = 0; row < TABLE_HEIGHT; row++)
		{
			for (int column = 0; column < TABLE_WIDTH; column++)
			{
				// Copy the value
				m_map[row][column] = arr[row][column];
			}
		}
	}


	void GrassMap::DrawMap(int cameraPosX=0, int cameraPosy=0)
	{
		int type = 0;
		// level[row][column]
		for (int row = 0; row < TABLE_HEIGHT; row++) // TABLE_HEIGHT
		{ 
			for (int column = 0; column < TABLE_WIDTH; column++) // TABLE_WIDTH
			{
				type = m_map[row][column];
				
				// tiles placement
				m_dest.x = column * 80 - cameraPosX;
				m_dest.y = row * 80 - cameraPosy;

				// of needed: make the tiles 2x bigger
				// m_src.h = m_frameHeight * 4;

				// placemement correction
				m_dest.h = m_frameHeight * 5;
				m_dest.w = m_frameWidth * 5;				

				int line = 0;
				int col = 0;


				/******************************************************************************************/
				// Define a lookup table to map type values to line and col values
				const std::unordered_map<int, std::pair<int, int>> typeMap = {
					// ligne 0
					{0, {0, 0}},
					{1, {0, 1}},
					{2, {0, 2}},
					{3, {0, 3}},
					{4, {0, 4}},
					{5, {0, 5}},
					{6, {0, 6}},
					{7, {0, 7}},
					{8, {0, 8}},
					{9, {0, 9}},
					//{8, {0, 8}},
					// ligne 1
					{10, {1, 0}},
					{11, {1, 1}},
					{12, {1, 2}},
					{13, {1, 3}},
					{14, {1, 4}},
					{15, {1, 5}},
					{16, {1, 6}},
					{17, {1, 7}},
					{18, {1, 8}},
					{19, {1, 9}},
					// ligne 2
					{20,{2, 0} },
					{21,{2, 1} },
					{22,{2, 2} },
					{23,{2, 3} },
					{24,{2, 4} },
					{25,{2, 5} },
					{26,{2, 6} },
					{27,{2, 7}},
					{28,{2, 8}},
					{29,{2, 9}},
					// ligne 3
					{30, {3,0}},
					{31, {3,1}},
					{32, {3,2}},
					{33, {3,3}},
					{34, {3,4}},
					{35, {3,5}},
					{36, {3,6}},
					{37, {3,7}},
					{38, {3,8}},
					{39, {3,9}},
					// ligne 4
					{40, {4,0}},
					{41, {4,1}},
					{42, {4,2}},
					{43, {4,3}},
					{44, {4,4}},
					{45, {4,5}},
					{46, {4,6}},
					{47, {4,7}},
					{48, {4,8}},
					{49, {4,9}},
					// ligne 5
					{50, {5,0}},
					{51, {5,1}},
					{52, {5,2}},
					{53, {5,3}},
					{54, {5, 4}},
					{55, {5, 5}},
					{56, {5, 6}},
					{57, {5, 7}}

				};

				// Use the lookup table to determine line and col values
				auto it = typeMap.find(type);
				if (it != typeMap.end()) {
					line = it->second.first;
					col = it->second.second;
				}
				else {
					// Handle the default case
				}

				// drawing the tiles according to line and column values
				m_src = { col * m_frameWidth, line * m_frameHeight, m_frameWidth, m_frameHeight };

				// tiles placement
				m_dest.x = column * 80 - cameraPosX;
				m_dest.y = row * 80 - cameraPosy;
				TextureManager::Draw(m_grass, m_src, m_dest);

			}
		}
	}
} // namespace HeArc::RPG
