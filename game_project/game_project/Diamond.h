#pragma once
#include "GameObject.h"
namespace HeArc::RPG {
	class Diamond : public GameObject
	{
	public:
		/// <summary>
		/// Diamond constructor.
		/// </summary>
		/// <param name="_x">The x position</param>
		/// <param name="_y">The y position</param>
		/// <param name="_diamondType">The type of diamond to display, for now only one</param>
		Diamond(int _x, int _y, int _diamondType = 0);
		/// <summary>
		/// Destructor of the diamond
		/// </summary>
		virtual ~Diamond() = default;


	private:

	};
}// namespace HeArc::RPG