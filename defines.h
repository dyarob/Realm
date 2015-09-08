#ifndef DEFINES
#define DEFINES

#define ERR_SDL_INIT		1	/* SDL_Init() */
#define ERR_IMG_INIT		2	/* IMG_Init() */
#define ERR_SDL_CW			3	/* SDL_CreateWindow() */
#define ERR_SDL_CR			4	/* SDL_CreateRenderer() */
#define ERR_IMG_LOAD		5	/* IMG_Load() */
#define ERR_SDL_CTFS		6	/* SDL_CreateTextureFromSurface() */
#define pr_sdl_err(msg)		fprintf(stderr, msg ": %s\n", SDL_GetError())

#define SPRITE_H	16
#define SPRITE_W	16
#define SPRITES_NUMBER	3

#define WIN_H	32 * TILES_HIGH
#define WIN_W	32 * TILES_WIDE + 100
#define	TILES_HIGH	5
#define	TILES_WIDE	8
#define TILES_TOTAL	TILES_HIGH * TILES_WIDE

#endif
