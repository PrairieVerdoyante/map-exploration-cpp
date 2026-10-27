// add if any errors appear related to SDL_main
// #define //SDL_MAIN_HANDLED

#include <SDL.h>
#include <stdio.h>

#include "Game.h"
using namespace HeArc::RPG;
Game *game = nullptr;

int main(int argc, char* args[])
{
	// Frame rate cap
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 framestart = 0;
	auto frameTime = 0;

	// Create the game object
    game = new Game();

	// Initialize the game
	game->init("MAP exploration", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
    
	// Game loop
    while (game->isRunning()) {
		game->handleEvents();
		game->update();
		game->render();

		// Frame rate cap
		frameTime = SDL_GetTicks() - framestart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	// Clean up
	game->clean();
	delete game;

    return 0;
}
