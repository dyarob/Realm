#ifndef CAOMPS
#define CAOMPS
#include <map>
#include <vector>

enum	Dir { TOP, RIGHT, BOTTOM, LEFT };

namespace Cap {
	extern std::vector<int>		Drawable;
	extern std::vector<int>		Walkable;
}

namespace Comp {
	extern std::map<int, int>	x;
	extern std::map<int, int>	y;
	extern std::map<int, Dir>	dir;
}
#endif
