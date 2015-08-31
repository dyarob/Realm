//#include <SDL2/SDL.h>
#include <SDL.h>
#include <stdio.h>

#define ERR_SDL_INIT		1	/* SDL_Init() */
#define ERR_IMG_INIT		2	/* IMG_Init() */
#define ERR_SDL_CW			3	/* SDL_CreateWindow() */
#define ERR_SDL_CR			4	/* SDL_CreateRenderer() */
#define ERR_IMG_LOAD		5	/* IMG_Load() */
#define ERR_SDL_CTFS		6	/* SDL_CreateTextureFromSurface() */
#define pr_sdl_err(msg)		fprintf(stderr, msg ": %s\n", SDL_GetError())

#define WIN_H	320
#define WIN_W	640
#define	TILES_HIGH	10
#define	TILES_WIDE	20
#define TILES_TOTAL	TILES_HIGH * TILES_WIDE

#define SPRITE_H	32
#define SPRITE_W	32
#define SPRITES_NUMBER	3

#include <map>
#include <string>

enum	Dir { TOP, RIGHT, BOTTOM, LEFT };

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
	std::map<int, SDL_Texture*>	tex;
	std::map<int, Dir>			dir;
}

int main() {
	int			ret = 0;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*bmp;
	SDL_Texture		*tex[SPRITES_NUMBER];
	SDL_Rect	r = {0, 0, 32, 32};
	int			ents[SPRITES_NUMBER];
	for (int i = 0; i < SPRITES_NUMBER; ++i) {
		ents[i] = i;
		Comp::x[i] = i % TILES_WIDE * SPRITE_W;
		Comp::y[i] = i / TILES_WIDE * SPRITE_H;
	}
	Cap::Drawable[1] = true;
	Cap::Drawable[2] = true;
	Cap::Drawable[23] = true;

	ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret != 0) {
		pr_sdl_err("Unable to initialize SDL");
		ret = -ERR_SDL_INIT;
		goto exit_init;
	}
	win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		pr_sdl_err("Could not create window");
		ret = -ERR_SDL_CW;
		goto exit_win;
	}
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		pr_sdl_err("Unable to create renderer");
		ret = -ERR_SDL_CR;
		goto exit_ren;
	}
	for (int i = 0; i<SPRITES_NUMBER; ++i) {
		bmp = SDL_LoadBMP("./img/boxes.bmp");
		if (bmp == nullptr) {
			pr_sdl_err("Unable to load BMP");
			ret = -ERR_IMG_LOAD;
			goto exit_bmp;
		}
		tex[i] = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
		if (tex[i] == nullptr) {
			pr_sdl_err("Unable to create texture");
			ret = -ERR_SDL_CTFS;
			goto exit_tex;
		}
		bmp = nullptr;
	}

	for (;;) {
		SDL_Event	e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				break;
		}
		SDL_RenderClear(ren);
		for (int &ent : ents) {
			if (Cap::Drawable[ent]) {
				r.x = Comp::x[ent];
				r.y = Comp::y[ent];
				SDL_RenderCopy(ren, tex, NULL, &r);
			}
		}
		SDL_RenderPresent(ren);
	}

	SDL_DestroyTexture(tex);
exit_tex:
	SDL_DestroyRenderer(ren);
exit_bmp:
exit_ren:
	SDL_DestroyWindow(win);
exit_win:
	SDL_Quit();
exit_init:
	return ret;
}
