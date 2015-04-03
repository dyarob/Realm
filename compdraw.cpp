#include <SDL.h>
#include <map>

enum	Facing { TOP, RIGHT, BOTTOM, LEFT };

namespace Cap {
	std::map<int, bool>		Drawable;
	std::map<int, bool>		Walkable;
}

namespace Comp {
	std::map<int, int>			x;
	std::map<int, int>			y;
	std::map<int, int>			w;
	std::map<int, int>			h;
	std::map<int, std::string>	fname;
	std::map<int, *SDL_Texture	tex;
	std::map<int, Facing>		facing;
}
