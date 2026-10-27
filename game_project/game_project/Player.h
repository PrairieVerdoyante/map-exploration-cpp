#pragma once
#include "GameObject.h"
#include "Tree.h"
#include <vector>
namespace HeArc::RPG 
{
	class Player : public GameObject
	{
	public:
		/// <summary>
		/// Player constructor 
		/// </summary>
		/// <param name="_texturesheet">Texture sheet of the player</param>
		/// <param name="_x">X position of the player</param>
		/// <param name="_y">Y position of the player</param>
		Player(const char* _texturesheet, int _x, int _y);
		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~Player() = default;
		/// <summary>
		/// Upside movement
		/// </summary>
		void moveUp();
		/// <summary>
		/// Downside movement
		/// </summary>
		void moveDown();
		/// <summary>
		/// Left movement
		/// </summary>
		void moveLeft();
		/// <summary>
		/// Right movement
		/// </summary>
		void moveRight();
		/// <summary>
		/// Determines if the player can move or not
		/// </summary>
		/// <param name="_canMove">If the player can move or not</param>
		void setCanMove(bool _canMove) { m_canMove = _canMove; }

		/// <summary>
		/// Reimplementations of the GameObject methods
		/// </summary>
		void update() override;
		void render() override;
		void init() override;
		void animate() override;

		//Takes key presses and adjusts the dot's velocity
		void handleEvent(SDL_Event& e);
		/// <summary>
		/// Checks collisions
		/// </summary>
		bool checkCollision(GameObject* _object) const;


	private:
		// const int SCREEN_WIDTH = 800;
		// const int SCREEN_HEIGHT = 640;

		/// <summary>
		/// Speed of the player
		/// </summary>
		int m_speed{ 4 };

		/// <summary>
		/// Dimension of the character
		/// </summary>
		int m_characterDim{ 16 };

		/// <summary>
		/// Animation management
		/// </summary>
		const int m_WALKING_ANIMATION_FRAMES{ 4 };
		
		/// <summary>
		/// The current frame number
		/// </summary>
		int m_CURRENT_FRAME_NUMBER{ 0 };
		
		/// <summary>
		/// The dimensions of the sprite
		/// </summary>
		const size_t m_SPRITE_NUM_COLS = 4;
		const size_t m_SPRITE_NUM_ROWS = 4;

		/// <summary>
		/// Walking texture. Others can later be added like jumping etc.
		/// </summary>
		SDL_Texture* m_walkTexture;

		/// <summary>
		/// The animations
		/// </summary>
		std::vector<std::pair<int, int>> m_current;
		std::vector<std::pair<int, int>> m_walkDown;
		std::vector<std::pair<int, int>> m_walkUp;
		std::vector<std::pair<int, int>> m_walkLeft;
		std::vector<std::pair<int, int>> m_walkRight;

		/// <summary>
		/// The index for the incrementation of the animation
		/// </summary>
		int m_index = 0;
		
		/// <summary>
		/// The maximum duration of each frame for the animation
		/// </summary>
		double m_maxDuration{ 15 };

		/// <summary>
		/// The boolean to stop the animation
		/// </summary>
		bool m_done{ 0 };
		/// <summary>
		/// Determines if the player can move or not
		/// </summary>
		bool m_canMove{ true };

		// total width and height of the sprite sheet
		// const size_t widthSpr = 64;
		// const size_t heightSpr = 64;
		// const size_t TABLE_WIDTH  = 22;
		// const size_t TABLE_HEIGHT = 14;
		



	};
} // namespace HeArc::RPG