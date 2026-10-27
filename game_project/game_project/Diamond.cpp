#include "Diamond.h"
namespace HeArc::RPG {
	Diamond::Diamond(int _x, int _y, int _diamondType) : GameObject("Resources/Backgrounds/Tilesets/TilesetNature.png", _x, _y)
	{
		// set up the sprite according to the type
		switch (_diamondType) {
		case 0:
			// Diamond type 1 : orange
			setSrcRect({ 112, 224, 32, 32 });
			setSrcRect({ 0, 256, 16, 16 });
			break;
		default:
			break;
		}

		// set the position
		setDestRect({ _x, _y, 32, 32 });
	}


} // namespace HeArc::RPG