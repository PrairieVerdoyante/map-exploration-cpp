#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>
#include <memory>

namespace HeArc::RPG {
	GameObject::GameObject(const char* _texturesheet, int _x, int _y) {
		// load the texture
		m_objTexture = TextureManager::LoadTexture(_texturesheet);

		// set the position
		m_xpos = _x;
		m_ypos = _y;
		// set dest and src rectangles
		m_srcRect = {};
		m_destRect = {};

	}

	void GameObject::update()
	{
		// set the source rectangle
		m_srcRect.h = 16; // sprites de 16x16
		m_srcRect.w = 16;
		
		// set the destination rectangle
		m_destRect.x = m_xpos;
		m_destRect.y = m_ypos;
		
	}

	void GameObject::render() 
	{
		TextureManager::Draw(m_objTexture, m_srcRect, m_destRect);
	}
	
	// getters and setters
	int GameObject::getXPos() const {
		return m_xpos;
	}
	int GameObject::getYPos() const{
		return m_ypos;
	}
	void GameObject::setXPos(int newXPos)
	{
		// set the position
		m_xpos = newXPos;
	}
	void GameObject::setYPos(int newYPos)
	{
		// set the position
		m_ypos = newYPos;
	}
	void GameObject::animate()
	{
		// set the source rectangle x position
		m_srcRect.x = m_srcRect.w * static_cast<int>((SDL_GetTicks() / 200) % 4);
	}
	void GameObject::clean()
	{
		// Destroy the texture
		TextureManager::DestroyTexture(m_objTexture);

	}
	void GameObject::init()
	{
		
	}

}// namespace HeArc::RPG