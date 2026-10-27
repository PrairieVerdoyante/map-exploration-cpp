#include "TextureManager.h"

namespace HeArc::RPG {
	// texture loading
	SDL_Texture* TextureManager::LoadTexture(const char* _texture) {
		SDL_Surface* tmpSurface = IMG_Load(_texture);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);

		return tex;
	}
	// draw the texture
	void TextureManager::Draw(SDL_Texture* _tex, SDL_Rect _src, SDL_Rect _dest)
	{
		SDL_RenderCopy(Game::renderer, _tex, &_src, &_dest);
	}
	// draw the texture
	void TextureManager::Render() {
		SDL_RenderPresent(Game::renderer);

	}
	void TextureManager::Clear() {
		SDL_RenderClear(Game::renderer);
	}
	SDL_Texture* TextureManager::CreateTextureFromSurface(SDL_Surface* _surface) {
		SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, _surface);
		SDL_FreeSurface(_surface);
		return tex;
	}
	void TextureManager::Destroy(SDL_Window* _window)
	{
		SDL_DestroyRenderer(Game::renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}
	void TextureManager::DestroyTexture(SDL_Texture* _texture)
	{
		SDL_DestroyTexture(_texture);
	}

	
} // namespace HeArc::RPG