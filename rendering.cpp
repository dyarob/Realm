#include <SDL.h>
#include "Mechanics.h"
#include <vector>

void	render(SDL_Renderer *ren, SDL_Texture *tex[], SDL_Rect r) {
	SDL_RenderClear(ren);
	for (std::vector<int>::iterator it =Cap::Drawable.begin(); it !=Cap::Drawable.end(); ++it) {
		r.x = Comp::x[*it];
		r.y = Comp::y[*it];
		SDL_RenderCopy(ren, tex[2], NULL, &r);
	}
	SDL_RenderPresent(ren);
}
