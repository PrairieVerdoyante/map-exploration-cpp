#pragma once
#include "Game.h"
#include <iostream>
#include <ostream>

namespace HeArc::RPG {
	class GameObject {
	public:
		/// <summary>
		/// Constructor of the GameObject
		/// </summary>
		/// <param name="_texturesheet"> Texture to load with the GameObject </param>
		/// <param name="m_x">X position</param>
		/// <param name="m_y">Y position</param>
		GameObject(const char* _texturesheet, int m_x, int m_y);
		/// <summary>
		/// Destructor of the GameObject
		/// </summary>
		virtual ~GameObject() = default;

		/// <summary>
		/// Virtual methods to be implemented by the children
		/// </summary>
		virtual void init();
		virtual void update();
		virtual void render();
		virtual void clean();	
		virtual void animate();

		// getters and setters
		int getXPos() const; 
		int getYPos() const;

		/// <summary>
		/// Get the texture of the GameObject
		/// </summary>
		/// <returns>The texture of the GameObject</returns>
		inline virtual SDL_Texture* getTexture() const {return m_objTexture;}
		/// <summary>
		/// Set the texture of the GameObject
		/// </summary>
		/// <param name="_texture">The texture to set with the GameObject</param>
		void setTexture(SDL_Texture* _texture) { m_objTexture = _texture; }

		/// <summary>
		/// Set the X position of the GameObject
		///	</summary>
		void setXPos(int newXpos);
		/// <summary>
		/// Set the Y position of the GameObject
		/// </summary>
		/// <param name="nexYpos">The Y pos to set</param>
		void setYPos(int nexYpos);

		/// <summary>
		/// Get the source and destination rectangles of the GameObject
		/// </summary>
		/// <returns>The source or destination rectangles</returns>
		SDL_Rect getSrcRect() const { return m_srcRect; };
		SDL_Rect getDestRect() const { return m_destRect; };

		/// <summary>
		/// Set the source and destination rectangles of the GameObject
		/// </summary>
		/// <param name="rect">The source or destination rectangle to set</param>
		void setSrcRect(SDL_Rect rect) { m_srcRect = rect; };
		void setDestRect(SDL_Rect rect) { m_destRect = rect; };


	private:
		/// <summary>
		/// X position of the GameObject
		/// </summary>
		int m_xpos{ 0 };
		/// <summary>
		/// Y position of the GameObject
		/// </summary>
		int m_ypos{ 0 };

		/// <summary>
		/// Texture of the GameObject
		/// </summary>
		SDL_Texture* m_objTexture;
		/// <summary>
		/// The source and destination rectangles of the GameObject
		/// </summary>
		SDL_Rect m_srcRect, m_destRect;
	
	};
	

} // namespace HeArc::RPG