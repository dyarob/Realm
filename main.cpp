#include <SDL.h>
#include "rendering.h"

void	mainloop(SDL_Renderer *ren, SDL_Texture *tex[], SDL_Rect r) {
	for (;;) {
		SDL_Event	e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				break;
		}

		// RENDERING
		render(ren, tex, r);
	}
}
