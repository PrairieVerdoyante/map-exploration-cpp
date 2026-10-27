#include "Game.h"

#include "TextureManager.h"
#include "GrassMap.h"
#include "Player.h"
#include "Tree.h"
#include "Diamond.h"
#include "Backpack.h"
// include sdl_ttf
#include <SDL_ttf.h >
//#include "SDL_ttf.h"

namespace HeArc::RPG {

	// game objects in the game
	std::unique_ptr<Player> player;
	std::unique_ptr<GameObject> character;
	std::unique_ptr<GrassMap> grassMap;
	std::unique_ptr<Backpack> backpack;

	// for the forest of trees
	std::vector<std::unique_ptr<Tree>> trees;

	// diamond
	std::shared_ptr<Diamond> diamondToCollect;

	// renderer
	SDL_Renderer* Game::renderer = nullptr;

	Game::Game() {
		m_isRunning = false;
		window = nullptr;
		renderer = nullptr;
	}


	bool Game::isRunning() {
		return m_isRunning;
	}
	// this function is used to initialize the game. It 
    void Game::init(const char* title, int _xpos, int _ypos, int _width, int _height, bool _fullscreen = false) {
        try {
            // Initialize the game
            int flags = 0;
            if (_fullscreen) {
                flags = SDL_WINDOW_FULLSCREEN;
            }
            if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
                std::cout << "Subsystems Initialized!" << std::endl;

                int flags = 0;
                if (_fullscreen) {
                    flags = SDL_WINDOW_FULLSCREEN;
                }

                // Create the window
                window = SDL_CreateWindow(title, _xpos, _ypos, _width, _height, flags);
                if (window) {
                    std::cout << "Window created!" << std::endl;
                }

                // Create the renderer
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                if (renderer) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    std::cout << "Renderer created!" << std::endl;
                }

                m_isRunning = true;
            }
            else {
                m_isRunning = false;
            }

            // Initialisation of the TTF
            if (TTF_Init() == -1) {
                throw std::runtime_error("SDL_ttf could not initialize! SDL_ttf Error: " + std::string(TTF_GetError()));
            }

            // create the backpack
            backpack = std::make_unique<Backpack>();
            // create the game objects
            character = std::make_unique<GameObject>("Resources/Actor/Characters/EggBoy/SeparateAnim/Jump.png", (250), (SCREEN_HEIGHT / 2 - 200));
            grassMap = std::make_unique<GrassMap>();

            // create the trees and the decorations (logs, ...)
            setUpForest();

            // create the diamond
            diamondToCollect = std::make_shared<Diamond>(180, 920);

            // create the player
            player = std::make_unique<Player>("Resources/Actor/Boy/SeparateAnim/Idle.png", (SCREEN_WIDTH / 7) - 100, SCREEN_HEIGHT - 70);

            // camera
            m_camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

            handleCollisions();
        }
        catch (const std::exception& e) {
            std::cerr << "An error occurred during game initialization: " << e.what() << std::endl;
            m_isRunning = false;
        }
    }

	void Game::handleEvents() {
		SDL_Event event;
		SDL_PollEvent(&event);
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				m_isRunning = false;
			}
		}
		player->handleEvent(event);
	}


	// Loop function
	void Game::update() {
		player->update();
		character->update();

		// camera
		m_camera.x = (player->getXPos() + player->getSrcRect().w / 2) - m_camera.w / 2;
		m_camera.y = (player->getYPos() + player->getSrcRect().h / 2) - m_camera.h / 2;

		// Limit the camera to the edges of the map
		if (m_camera.x < 0) { m_camera.x = 0; }
		if (m_camera.y < 0) { m_camera.y = 0; }
		if (m_camera.x > m_camera.w) { m_camera.x = m_camera.w; }
		// offset for the camera height
		if (m_camera.y > m_camera.h - m_camera_offset) { m_camera.y = m_camera.h - m_camera_offset; }

		// Limit the player to the edges of the map
		if (player->getXPos() > ((2 * m_camera.w) - m_camera_offset) - player->getDestRect().w) {
			player->setXPos(((2 * m_camera.w) - m_camera_offset) - player->getDestRect().w);
		}
		if (player->getYPos() > (2 * m_camera.h - m_camera_offset) - player->getDestRect().h) {
			player->setYPos((2 * m_camera.h - m_camera_offset) - player->getDestRect().h);
		}
		
		// handle the collisions
		handleCollisions();		

	}


	void Game::handleCollisions()
	{
		// if the player is on the diamond, put the diamond in the backpack and un display it
		if (player->checkCollision(diamondToCollect.get())) {
			backpack.get()->pack(diamondToCollect);

			// un-render the diamond 
			diamondToCollect = std::make_shared<Diamond>(-100, -100);
		}


		if (player->checkCollision(character.get()) && backpack->isNotEmpty()) {

			// conversion from GameObject to Diamond and unpacking the backpack.
			diamondToCollect = std::dynamic_pointer_cast<Diamond>(backpack->unpack());
			diamondToCollect = std::make_shared<Diamond>(player->getXPos() + 50, player->getYPos());

			// if the backpack is empty or not
			if (!backpack->isNotEmpty()) {
				std::cout << "The backpack has been emptied" << std::endl;
				m_characterCanMove = true;

				// do message after the diamond is given
				m_textMessage = "";
			}
			else {
				std::cout << "The backpack still contains items" << std::endl;
			}
			
		}
		// To display the message only when the player collides with the character and the backpack is empty
		else if (player->checkCollision(character.get()) && !backpack->isNotEmpty()) {
			if (!m_hasFirstMessageDisplayed) {
				m_hasFirstMessageDisplayed = true;
			}
		}

	}

	void Game::render() {
		// Clear the renderer
		TextureManager::Clear();
		
		// Render the grass map, offset by the camera's position
		grassMap->DrawMap(m_camera.x, m_camera.y);	

		// Render other game objects, also offset by the camera's position
		if (m_characterCanMove) {
			character->animate();
		}
		SDL_Rect srcRect = character->getSrcRect();

		// render the character
		SDL_Rect renderQuad = { character->getXPos() - m_camera.x, character->getYPos() - m_camera.y, character->getSrcRect().w * 3, character->getSrcRect().h * 3 };
		TextureManager::Draw(character->getTexture(), srcRect, renderQuad);

		// Render the trees
        for (const auto& tree : trees) {
            SDL_Rect srcRect = tree->getSrcRect();
            SDL_Rect renderQuad = { tree->getXPos() - m_camera.x, tree->getYPos() - m_camera.y, tree->getSrcRect().w * 3, tree->getSrcRect().h * 3 };
			TextureManager::Draw(tree->getTexture(), srcRect, renderQuad);
        }


		// Render the diamond with the camera
		srcRect = diamondToCollect->getSrcRect();
		renderQuad = { diamondToCollect->getXPos() - m_camera.x, diamondToCollect->getYPos() - m_camera.y, diamondToCollect->getSrcRect().w * 3, diamondToCollect->getSrcRect().h * 3 };
		TextureManager::Draw(diamondToCollect->getTexture(), srcRect, renderQuad);

		// Render the player, offset by the camera's position
		renderQuad = { player->getXPos() - m_camera.x, player->getYPos() - m_camera.y, player->getSrcRect().w * 3, player->getSrcRect().h * 3 };


		// Render the player, also offset by the camera's position
		player->render();
		srcRect = (player->getSrcRect());
		TextureManager::Draw(player->getTexture(), srcRect, renderQuad);

		// The messages stops displaying once the player has collected the diamond
		if (m_hasFirstMessageDisplayed) {
			displayMessage(m_textMessage.c_str(), 0, 0);
			TextureManager::Draw(m_textTexture, m_textSrcRect, m_textDestRect);

			m_hasFirstMessageDisplayed = false;
		}

		// End of rendering
		TextureManager::Render();
		


	}
	void Game::displayMessage(const char* _message, int _x, int _y)
	{

		// Exemple de dessin d'un rectangle de test
		SDL_Rect testRect = { player->getXPos() - 50, player->getYPos() - 70, 500, 20 }; // Ajustez selon la position du joueur
		
		// texte
		TTF_Font* font = TTF_OpenFont("Resources/Fonts/ChrustyRock-ORLA.ttf", 30);
		SDL_Color color = { 255, 255, 255 };
		SDL_Surface* surface = TTF_RenderText_Solid(font, _message, color);

		// texture
		m_textTexture = TextureManager::CreateTextureFromSurface(surface);
		m_textSrcRect = { 0,0,500,500};
		m_textDestRect = { player->getXPos()-150, player->getYPos() - 70, 400, 40 };



	}

	void Game::setUpForest()
	{
		// path of the nature tileset to avoid rewriting it
		const char* naturePath = "Resources/Backgrounds/Tilesets/TilesetNature.png";

		// add trees to the vector
        trees.push_back(std::make_unique<Tree>(naturePath, -30, 0, 1));
        trees.push_back(std::make_unique<Tree>(naturePath, 120, 0, 1));

        // top of the map
        trees.push_back(std::make_unique<Tree>(naturePath, 270, -10, 1));
        trees.push_back(std::make_unique<Tree>(naturePath, 200, -10, 1)); // pos x, pos y, tree number
        trees.push_back(std::make_unique<Tree>(naturePath, -30, 0, 11));

        // line of trees
        for (auto i = 320; i <= 1500; i += 80) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, -50, 11));
        }

        trees.push_back(std::make_unique<Tree>(naturePath, 350, 0, 11));
        trees.push_back(std::make_unique<Tree>(naturePath, 420, 0, 11));

        // line number 2
        trees.push_back(std::make_unique<Tree>(naturePath, -30, 80, 11));
        trees.push_back(std::make_unique<Tree>(naturePath, 380, 80, 11));

        // line number 3
        trees.push_back(std::make_unique<Tree>(naturePath, -30, 160, 11));
        trees.push_back(std::make_unique<Tree>(naturePath, 380, 160, 11));


        // line number 4
        trees.push_back(std::make_unique<Tree>(naturePath, -30, 240, 11));
        trees.push_back(std::make_unique<Tree>(naturePath, 60, 240, 11)); // peut créer des problemes de collisions
        trees.push_back(std::make_unique<Tree>(naturePath, 300, 240, 11)); // peut créer des problemes de collisions
        trees.push_back(std::make_unique<Tree>(naturePath, 380, 240, 11));

        // line number 5
        trees.push_back(std::make_unique<Tree>(naturePath, 110, 340, 1));

        for (auto i = 330; i <= 430; i += 50) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 320, 1));
        }

        // trees around second area

        for (auto i = 910; i <= 1500; i += 80) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 0, 11)); // 
        }

        for (auto i = 980; i <= 1500; i += 80) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 95, 11)); // 
        }


        // one line of trees
        for (auto i = 930; i <= 1010; i += 80) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 150, 11));
        }
        trees.push_back(std::make_unique<Tree>(naturePath, 1400, 200, 1));
        trees.push_back(std::make_unique<Tree>(naturePath, 1480, 160, 11));

        // log
        trees.push_back(std::make_unique<Tree>(naturePath, 1480, 300, 32));



        // single trees to fill the gaps
        // line of trees
        for (auto i = 880; i < 1000; i += 80) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 200, 11));
        }

        trees.push_back(std::make_unique<Tree>(naturePath, 910, 280, 1));

        trees.push_back(std::make_unique<Tree>(naturePath, 620, 280, 11));
        trees.push_back(std::make_unique<Tree>(naturePath, 700, 280, 11));
        trees.push_back(std::make_unique<Tree>(naturePath, 780, 280, 11));


        trees.push_back(std::make_unique<Tree>(naturePath, -30, 320, 11));


        // line number 6
        trees.push_back(std::make_unique<Tree>(naturePath, -30, 400, 11));

        // adding a line of trees (sets of three and one) under the main path
        for (auto i = 280; i < 820; i += 90) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 490, 11));
        }


        // adding a forest underneath
        for (auto i = 180; i < 900; i += 80) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 590, 11));
        }
        for (auto i = -50; i < 900; i += 80) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 690, 11));
        }
        for (auto i = 80; i < 900; i += 80) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 790, 1));
        }
        trees.push_back(std::make_unique<Tree>(naturePath, -50, 790, 11));


        // buche
        trees.push_back(std::make_unique<Tree>(naturePath, 40, 620, 32));


        trees.push_back(std::make_unique<Tree>(naturePath, 0, 860, 1));
        trees.push_back(std::make_unique<Tree>(naturePath, -50, 900, 1));
        trees.push_back(std::make_unique<Tree>(naturePath, 50, 900, 1));
        trees.push_back(std::make_unique<Tree>(naturePath, 0, 940, 1));


        // adding a line of single trees at the bottom of the map
        for (auto i = 0; i < 3400; i += 70) {
        trees.push_back(std::make_unique<Tree>(naturePath, i, 1000, 1));
        }

		// decoration with "mini logs"
		trees.push_back(std::make_unique<Tree>(naturePath, 1300, 300, 33));
		// decoration with foam and logs
		trees.push_back(std::make_unique<Tree>(naturePath, 1500, 550, 34));
		trees.push_back(std::make_unique<Tree>(naturePath, 1400, 900, 35));
		// decoration with flowers
		trees.push_back(std::make_unique<Tree>(naturePath, 1200, 500, 36));
		trees.push_back(std::make_unique<Tree>(naturePath, 1000, 320, 36));
		trees.push_back(std::make_unique<Tree>(naturePath, 1300, 700, 36));
		trees.push_back(std::make_unique<Tree>(naturePath, 1300, 900, 36));
		trees.push_back(std::make_unique<Tree>(naturePath, 150, 520, 36));
		// trefles
		trees.push_back(std::make_unique<Tree>(naturePath, 1500, 470, 37));
		trees.push_back(std::make_unique<Tree>(naturePath, 1400, 450, 37));
		trees.push_back(std::make_unique<Tree>(naturePath, 1050, 400, 37));
		trees.push_back(std::make_unique<Tree>(naturePath, 1000, 900, 37));
		// red flowers
		trees.push_back(std::make_unique<Tree>(naturePath, 1200, 800, 38));
		trees.push_back(std::make_unique<Tree>(naturePath, 1350, 400, 38));
		trees.push_back(std::make_unique<Tree>(naturePath, 1400, 750, 38));

		// trefles on the way
		trees.push_back(std::make_unique<Tree>(naturePath, 650, 100, 37));
		trees.push_back(std::make_unique<Tree>(naturePath, 800, 200, 37));

	}

	void Game::clean() {
        player.reset();
        character.reset();
		grassMap.reset();
		diamondToCollect.reset();

		for (auto& tree : trees) {
			tree.reset();
		}

		// destroys the window and the renderer.
		TextureManager::Destroy(window);
		TTF_Quit();
		SDL_Quit();

		std::cout << "Game cleaned!" << std::endl;
	}

}; // namespace HeArc::RPG