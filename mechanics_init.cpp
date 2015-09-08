#include "Mechanics.h"
#include "defines.h"
#include "main.h"

void	// WHAT COULD POSSIBLY GO WRONG?
		mechanics_init(SDL_Renderer *ren, SDL_Texture *tex[], SDL_Rect r) {
	// init floor tiles in ents table
	for (int i = 0; i < TILES_TOTAL; ++i) {
		Comp::x[i] = i % TILES_WIDE * 32;
		Comp::y[i] = i / TILES_WIDE * 32;
		Cap::Walkable.push_back(i);
		Cap::Drawable.push_back(i);
	}

	// STEP 3: GAME LAUNCH
	mainloop(ren, tex, r);
}
