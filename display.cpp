//#include <SDL2/SDL.h>
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <dirent.h>
#include <iostream>
#include "defines.h"
#include "mechanics_init.h"

int main() {
	int				ret = 0;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*bmp;
	SDL_Texture		*tex[SPRITES_NUMBER];
	SDL_Rect		r = {0, 0, 32, 32};
	DIR				*dir;
	struct dirent	*dirent;
	std::stringstream	ss;

	ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret != 0) {
		pr_sdl_err("Unable to initialize SDL");
		ret = -ERR_SDL_INIT;
		goto exit_init;
	}
	win = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
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

	// TEXTURE LOADING
	if (!(dir = opendir("img"))) {
		std::cerr << "opening img folder failed.";
		goto exit_dir;
	}
	for (int i = 0; i<SPRITES_NUMBER; ++i) {
		while ((dirent = readdir(dir))) {
			if (!strncmp(dirent->d_name, "sprite_", 7))
				break;
		}
		if (!dirent)
			break;
		ss << "img/" << dirent->d_name;
		bmp = SDL_LoadBMP(ss.str().c_str());
		if (bmp == nullptr) {
			pr_sdl_err("Unable to load BMP");
			ret = -ERR_IMG_LOAD;
			goto exit_bmp;
		}
		ss.str(std::string());
		ss.clear();
		tex[i] = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
		if (tex[i] == nullptr) {
			pr_sdl_err("Unable to create texture");
			ret = -ERR_SDL_CTFS;
			goto exit_tex;
		}
		bmp = nullptr;
	}

	// STEP 1 Graphics init. COMPLETE
	// TO STEP 2: Mechanics init.
	// (Capacities & Components)
	mechanics_init(ren, tex, r);

	// Game has been terminated.
	// FREEING MEM FROM HERE
	for (int i = 0; i<SPRITES_NUMBER; ++i)
		SDL_DestroyTexture(tex[i]);
exit_tex:
exit_bmp:
exit_dir:
	SDL_DestroyRenderer(ren);
exit_ren:
	SDL_DestroyWindow(win);
exit_win:
	SDL_Quit();
exit_init:
	return ret;
}
