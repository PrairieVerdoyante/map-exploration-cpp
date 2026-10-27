#pragma once
#include "Map.h"
namespace HeArc::RPG {
	class GrassMap : public Map {
	public:
		/// <summary>
		/// Constructor of the grass map
		/// </summary>
		GrassMap();
		
		/// <summary>
		/// load map: overriden method from the map class
		/// </summary>
		/// <param name="arr">The array containing the size of the map</param>
		void LoadMap(int arr[TABLE_HEIGHT][TABLE_WIDTH]);
		/// <summary>
		/// draw map: overriden method from the map class
		/// </summary>
		/// <param name="cameraPosX">pos X of the camera</param>
		/// <param name="cameraPosy">pos Y of the camera</param>
		void DrawMap(int cameraPosX, int cameraPosy) override;

	private:
		/// <summary>
		/// Src and dest rectangles of the grass map
		/// </summary>
		SDL_Rect m_src, m_dest;

		/// <summary>
		/// Texture of the grass map
		/// </summary>
		SDL_Texture* m_grass;
		/// <summary>
		/// The map of the grass
		/// </summary>
		int m_map[TABLE_HEIGHT][TABLE_WIDTH];

		/// <summary>
		/// Width and height of the frames
		/// </summary>
		int m_frameWidth = 0;
		int m_frameHeight = 0;	
	};
} // namespace HeArc::RPG