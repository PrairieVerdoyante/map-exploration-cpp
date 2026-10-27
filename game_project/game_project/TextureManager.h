#pragma once
#include "Game.h"

namespace HeArc::RPG {
	class TextureManager {
	public:
		/// <summary>
		/// Load a texture from a file
		/// </summary>
		/// <param name="_filename">Name of the file</param>
		/// <returns>The loaded texture.</returns>
		static SDL_Texture* LoadTexture(const char* _filename);
		/// <summary>
		/// Draw a texture on the renderer
		/// </summary>
		/// <param name="_tex">Texture</param>
		/// <param name="_src">Source path</param>
		/// <param name="_dest">Destination path</param>
		static void Draw(SDL_Texture* _tex, SDL_Rect _src, SDL_Rect _dest);
		/// <summary>
		/// Renders the elements on the screen
		/// </summary>
		static void Render();
		/// <summary>
		/// Clear the renderer
		/// </summary>
		static void Clear();
		/// <summary>
		/// Creates a texture from a surface
		/// </summary>
		static SDL_Texture* CreateTextureFromSurface(SDL_Surface* _surface);
		/// <summary>
		/// Destroy window anad  renderer
		/// </summary>
		static void Destroy(SDL_Window* _window);
		/// <summary>
		/// Destroy a texture
		/// </summary>
		/// <param name="_texture"></param>
		static void DestroyTexture(SDL_Texture* _texture);


	};
} // namespace HeArc::RPG