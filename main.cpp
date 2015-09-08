#include <SDL.h>
#include "Mechanics.h"
#include <vector>

void	mainloop(SDL_Renderer *ren, SDL_Texture *tex[], SDL_Rect r) {
	for (;;) {
		SDL_Event	e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				break;
		}

		// RENDERING
		SDL_RenderClear(ren);
		for (std::vector<int>::iterator it =Cap::Drawable.begin(); it !=Cap::Drawable.end(); ++it) {
			r.x = Comp::x[*it];
			r.y = Comp::y[*it];
			SDL_RenderCopy(ren, tex[2], NULL, &r);
		}
		SDL_RenderPresent(ren);
	}
}
