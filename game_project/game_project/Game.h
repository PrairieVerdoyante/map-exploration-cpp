#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


namespace HeArc::RPG {
	class Game {
	public:
		// Constructor and Destructor
		Game();
		~Game() = default;
		
		/// <summary>
		/// Game Initialisation
		/// </summary>
		/// <param name="_title"></param>
		/// <param name="_xpos"></param>
		/// <param name="_ypos"></param>
		/// <param name="_width"></param>
		/// <param name="_height"></param>
		/// <param name="_fullscreen"></param>
		void init(const char* _title, int _xpos, int _ypos, int _width, int _height, bool _fullscreen);

		/// <summary>
		/// Handles events
		/// </summary>
		void handleEvents();
		/// <summary>
		/// Updates the game
		/// </summary>
		void update();
		/// <summary>
		/// renders the game
		/// </summary>
		void render();
		/// <summary>
		/// Cleans the game after it's done
		/// </summary>
		void clean();
		/// <summary>
		/// Adds the map decoration elements to the game.
		/// </summary>
		void setUpForest();
		/// <summary>
		/// Handle what happens when collisions occur
		/// </summary>
		void handleCollisions();
		/// <summary>
		/// Displays a message on the screen
		/// </summary>
		/// <param name="_message">The message to display</param>
		/// <param name="_x">The y pos of the message</param>
		/// <param name="_y">The y pos of the message</param>
		void displayMessage(const char* _message, int _x, int _y);
		/// <returns>if the game is running or not</returns>
		bool isRunning();

		/// <summary>
		/// renderer
		/// </summary>
		static SDL_Renderer *renderer;

		/// <summary>
		/// Screen width and height
		/// </summary>
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 640;

		private:
			/// <summary>
			/// the game is running or not
			/// </summary>
			bool m_isRunning = false;
			/// <summary>
			/// Defines if the character can do any movement
			/// </summary>
			bool m_characterCanMove = false;
			/// <summary>
			/// Defines if the messages has already been created to not do it twice.
			/// </summary>
			bool m_hasFirstMessageDisplayed = false;
			/// <summary>
			/// Window of the game
			/// </summary>
			SDL_Window* window;

			// camera
			SDL_Rect m_camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
			
			/// <summary>
			/// SDL_Rects for the text display
			/// </summary>
			SDL_Rect m_textSrcRect { 0, 0, 0, 0 };
			SDL_Rect m_textDestRect { 0, 0, 0, 0 };
			/// <summary>
			/// Texture for the text display
			/// </summary>
			SDL_Texture* m_textTexture = nullptr;
			/// <summary>
			/// Message to display
			/// </summary>
			std::string m_textMessage = "You need to collect a diamond first!";

			/// <summary>
			/// Adjusts how much the camera moves
			/// </summary>
			const int m_camera_offset{ 200 };


	};
} // namespace HeArc::RPG