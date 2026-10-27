#include "Player.h"
#include "TextureManager.h"
#include <iostream>
#include <chrono>
namespace HeArc::RPG {

	Player::Player(const char* _texturesheet, int _x, int _y) : GameObject(_texturesheet, _x, _y)
	{
		init();
	}

	

	void Player::init() {
		// set the source rectangle
		SDL_Rect srcRect = { 0 ,0, 16, 16 };
		setSrcRect(srcRect);

		// animations
		m_walkTexture = TextureManager::LoadTexture("Resources/Actor/boy/SeparateAnim/Walk.png");		
		setTexture(m_walkTexture);

		// define the animations posisions in the spritesheet
		m_walkDown	= { {0, 0}, {1, 0}, {2, 0}, {3, 0} };
		m_walkUp	= { {1, 0}, {1, 1}, {1, 2}, {1, 3} } ;
		m_walkLeft	= { {2, 0}, {2, 1}, {2, 2}, {2, 3} } ;
		m_walkRight	= { {3, 0}, {3, 1}, {3, 2}, {3, 3} } ;

		// set the current animation
		m_current = m_walkDown;
	}
	
	

	// movements
	void Player::moveUp()
	{
		// set the position
		setYPos(getYPos() - m_speed);
		// set the current animation
		m_current = m_walkUp;

	}
	void Player::moveDown()
	{
		// set the position
		setYPos(getYPos() + m_speed);
		// set the current animation
		m_current =	m_walkDown;
	}
	void Player::moveRight()
	{
		// set the position
		setXPos(getXPos() + m_speed);
		// set the current animation
		m_current = m_walkRight;
	}
	void Player::moveLeft()
	{
		// set the position
		setXPos(getXPos() - m_speed);
		// set the current animation
		m_current = m_walkLeft;	

	}

	/******************************* Movement management *****************************************/
	void Player::handleEvent(SDL_Event& e)
	{
		// If a key was pressed
		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
		// If escape is pressed
		if (m_canMove) {
			if (keyboardState[SDL_SCANCODE_ESCAPE]) {
				m_done = true;
			}
			// Up movement
			if (keyboardState[SDL_SCANCODE_W]) {
				// move the player
				moveUp();
				m_done = false;
			}
			// Down movement
			if (keyboardState[SDL_SCANCODE_S]) {
				// move the player
				moveDown();
				m_done = false;
			}
			// Left movement
			if (keyboardState[SDL_SCANCODE_A]) {
				// move the player
				moveLeft();
				m_done = false;
			}
			// Right movement
			if (keyboardState[SDL_SCANCODE_D] && !m_done) {
				// move the player
				moveRight();
				m_done = false;
			}
		}
		
		// If no key is pressed
		if (!keyboardState[SDL_SCANCODE_W] && !keyboardState[SDL_SCANCODE_S] && !keyboardState[SDL_SCANCODE_A] && !keyboardState[SDL_SCANCODE_D]) {
			// stop the animation
			m_done = true;
		}
		else {
			m_done = false;
		}
		
		// Limit the player to the edges of the map
		if (getXPos() < 0) { setXPos(0); }
		if (getYPos() < 0) { setYPos(0); }

		
	}
	
	bool checkPixelCollision(const SDL_Rect& rectA, const SDL_Rect& rectB, const std::vector<Uint32>& pixelsA, const std::vector<Uint32>& pixelsB, int widthA, int widthB) {
    // Vérification AABB préliminaire
    if (rectA.x + rectA.w <= rectB.x || rectA.x >= rectB.x + rectB.w || rectA.y + rectA.h <= rectB.y || rectA.y >= rectB.y + rectB.h) {
        return false; // Pas de collision
    }

    // Calculer la zone de chevauchement
    int xMin = std::max(rectA.x, rectB.x);
    int xMax = std::min(rectA.x + rectA.w, rectB.x + rectB.w);
    int yMin = std::max(rectA.y, rectB.y);
    int yMax = std::min(rectA.y + rectA.h, rectB.y + rectB.h);

    // Parcourir chaque pixel dans la zone de chevauchement
    for (int y = yMin; y < yMax; y++) {
        for (int x = xMin; x < xMax; x++) {
            Uint32 pixelA = pixelsA[(y - rectA.y) * widthA + (x - rectA.x)];
            Uint32 pixelB = pixelsB[(y - rectB.y) * widthB + (x - rectB.x)];

            // Vérifier si les deux pixels ne sont pas transparents
            if ((pixelA & 0xFF000000) && (pixelB & 0xFF000000)) {
                return true; // Collision détectée
            }
        }
    }

    return false; // Pas de collision
}


	bool Player::checkCollision(GameObject* _object) const
	{
		// check the collision
		if (getXPos() + getSrcRect().w > _object->getXPos() &&
			getXPos() < _object->getXPos() + _object->getSrcRect().w &&
			getYPos() + getSrcRect().h > _object->getYPos() &&
			getYPos() < _object->getYPos() + _object->getSrcRect().h) {
			return true;
		}
		else {
			return false;
		}
	}
	

	void Player::update()
	{
		// frame update for animation
		m_index += 1;
		if (m_index >= m_maxDuration) {
			m_CURRENT_FRAME_NUMBER = (m_CURRENT_FRAME_NUMBER + 1) % m_SPRITE_NUM_COLS;
			m_index = 0;
		}
	}

	void Player::render()
	{
		// call the animation
		animate();
	}

	void Player::animate() {
		
		// assign the column according to the current animation
		int col = (m_done) ? (0) : (m_current.front().first);

		// Set the source rectangle
		int row = (!m_done) ? ((m_CURRENT_FRAME_NUMBER % m_WALKING_ANIMATION_FRAMES)) : (0);
		SDL_Rect srcRect = { col * m_characterDim,row * m_characterDim, m_characterDim , m_characterDim };

		// Set the destination rectangle
		SDL_Rect destRect = { getXPos(), getYPos(), getSrcRect().w, getSrcRect().h };

		// Render the player
		setSrcRect(srcRect);
	}

} // namespace HeArc::RPG
