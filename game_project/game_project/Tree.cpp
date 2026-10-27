#include "Tree.h"
#include "TextureManager.h"
#include <iostream>
#include <string>
namespace HeArc::RPG {
	Tree::Tree(const char* _texturesheet, int _x, int _y, int _treeType=0, bool _isCollidable) : GameObject(_texturesheet, _x, _y)
	{
		m_type = _treeType;
		// position
		setSrcRect({ 0, 0, 32, 32 });
		setDestRect({ 0, 0, 32, 32 });
		

		init();
	}

	void Tree::init()
	{
		// set the source rectangle
		switch (m_type) {
		case 0:
			// Tree 1
			m_srcRect.x = 0;
			m_srcRect.y = 0;
			m_srcRect.w = 32;
			m_srcRect.h = 32;
			break;
		case 1:
			// Tree 2
			m_srcRect.x = 32;
			m_srcRect.y = 0;
			m_srcRect.w = 32;
			m_srcRect.h = 32;
			setSrcRect(m_srcRect); 
			

			break;
		case 11:
			// foret de sapins
			// 0 32 64 48
			m_srcRect.x = 0;
			m_srcRect.y = 32;
			m_srcRect.w = 64;
			m_srcRect.h = 48;
			break;
		case 12:
			// foret d'arbres roses
			m_srcRect.x = 192;
			m_srcRect.y = 32;
			m_srcRect.w = 64;
			m_srcRect.h = 48;
			break;
		case 31:
			// bûche foncee
			m_srcRect.x = 0;
			m_srcRect.y = 128;
			m_srcRect.w = 32;
			m_srcRect.h = 32;
			break;
		case 32:
			// bûche claire
			m_srcRect.x = 32;
			m_srcRect.y = 128;
			m_srcRect.w = 32;
			m_srcRect.h = 32;
			break;
		case 33:
			// buche "mini"
			m_srcRect.x = 80;
			m_srcRect.y = 128;
			m_srcRect.w = 16;
			m_srcRect.h = 16;
			break;
		case 34:
			// log with foam
			m_srcRect.x = 208;
			m_srcRect.y = 224;
			m_srcRect.w = 16;
			m_srcRect.h = 32;
			break;
		case 35:
			// pretty mini log
			m_srcRect.x = 192;
			m_srcRect.y = 208;
			m_srcRect.w = 16;
			m_srcRect.h = 16;
			break;
		case 36:
			// sunflower
			m_srcRect.x = 0;
			m_srcRect.y = 176;
			m_srcRect.w = 16;
			m_srcRect.h = 16;
			break;
		case 37:
			// trefle
			m_srcRect.x = 32;
			m_srcRect.y = 176;
			m_srcRect.w = 16;
			m_srcRect.h = 16;
			break;
		case 38:
			// red flower
			m_srcRect.x = 48;
			m_srcRect.y = 176;
			m_srcRect.w = 16;
			m_srcRect.h = 16;
			break;
		}
		setSrcRect(m_srcRect);
	}

	void Tree::render() {

		// set the tree according to src rectangle chosen
		SDL_Rect destRect = getDestRect();
		SDL_RenderCopy(Game::renderer, getTexture(), &m_srcRect, &destRect);

	}

} // namespace HeArc::RPG

