//#include <SDL2/SDL.h>
#include <SDL.h>
#include <stdio.h>

#define WIN_H	320
#define WIN_W	640

#define pr_sdl_err(msg)		fprintf(stderr, msg ": %s\n", SDL_GetError())

#define ERR_SDL_INIT		1	/* SDL_Init() */
#define ERR_IMG_INIT		2	/* IMG_Init() */
#define ERR_SDL_CW			3	/* SDL_CreateWindow() */
#define ERR_SDL_CR			4	/* SDL_CreateRenderer() */
#define ERR_IMG_LOAD		5	/* IMG_Load() */
#define ERR_SDL_CTFS		6	/* SDL_CreateTextureFromSurface() */

int main() {
	int		ret = 0;
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*bmp;
	SDL_Texture		*tex;
	SDL_Rect	r = {0, 0, 32, 32};

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
		fprintf(stderr, "Unable to create renderer\n");
		ret = -ERR_SDL_CR;
		goto exit_ren;
	}
	bmp = SDL_LoadBMP("./img/boxes.bmp");
	if (bmp == nullptr) {
		pr_sdl_err("Unable to load BMP");
		ret = -ERR_IMG_LOAD;
		goto exit_bmp;
	}
	tex = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		pr_sdl_err("Unable to create texture");
		ret = -ERR_SDL_CTFS;
		goto exit_tex;
	}

	for (;;) {
		SDL_Event	e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				break;
		}
		SDL_RenderClear(ren);
		for (r.x = 0; r.x < WIN_W; r.x += r.w) {
			for (r.y = 0; r.y < WIN_H; r.y += r.h)
				SDL_RenderCopy(ren, tex, NULL, &r);
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
