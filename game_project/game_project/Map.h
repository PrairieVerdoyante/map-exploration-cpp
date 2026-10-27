#pragma once
#include "Game.h"

const int TABLE_WIDTH = 22; // 25
const int TABLE_HEIGHT = 14;// 20

namespace HeArc::RPG {
	class Map {
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		Map();
		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~Map() = default;

		/// <summary>
		/// Loads the map
		/// </summary>
		/// <param name="arr">The map to load</param>
		virtual void LoadMap(int arr[TABLE_HEIGHT][TABLE_WIDTH]) = 0;
		/// <summary>
		/// Draws the map
		/// </summary>
		/// <param name="cameraPosX">The X position for the camera to adjust</param>
		/// <param name="cameraPosy">The Y position for the camera to adjust</param>
		virtual void DrawMap(int cameraPosX, int cameraPosy) = 0;
	private:

		/// <summary>
		/// Dirt texture
		/// </summary>
		SDL_Texture* m_dirt;
		/// <summary>
		/// >Grass texture
		/// </summary>
		SDL_Texture* m_grass;
		/// <summary>
		/// Water texture
		/// </summary>
		SDL_Texture* m_water;



	};
} // namespace HeArc::RPG