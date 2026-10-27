#pragma once
#pragma once
#include "GameObject.h"
namespace HeArc::RPG {
	class Tree : public GameObject {
	public:		
		/// <summary>
		/// Constructor of all the decor elements
		/// </summary>
		/// <param name="_texturesheet">Path of the texture sheed</param>
		/// <param name="_x">X position</param>
		/// <param name="_y">Y position</param>
		/// <param name="_treeType">Type of sprite chosen. Can be a tree, a log or other decor</param>
		/// <param name="_isCollidable">true by default. Defines if the player can go through the tree or not.</param>
		Tree(const char* _texturesheet, int _x, int _y, int _treeType, bool _isCollidable=true);
		virtual ~Tree() = default;

		/// <summary>
		/// Init void of the tree
		/// </summary>
		void init() override;
		/// <summary>
		/// render void of the tree
		/// </summary>
		void render() override;

	private:
		/// <summary>
		/// Defines if the player can go through the tree or not
		/// </summary>
		bool m_isCollidable{ true };
		/// <summary>
		/// Type chosen of the decor element. Can be a tree, a log or other decor
		/// </summary>
		int m_type{ 0 };
		/// <summary>
		/// Source rectangle of the tree
		/// </summary>
		SDL_Rect m_srcRect;

	};
} // namespace HeArc::RPG